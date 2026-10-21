#!/usr/bin/env python3
"""Audit every template, syntax-check C++ sources, run smoke checks, and build the PDF."""

from __future__ import annotations

import argparse
import collections
import os
from pathlib import Path
import re
import shutil
import subprocess
import sys
import tempfile


ROOT = Path(__file__).resolve().parent
TEMPLATE_DIR = ROOT / "cpp_templates"

CPP_PRELUDE = """#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
"""

# These three files document shell/compiler commands despite their .cpp suffix.
NON_CPP_TEMPLATES = {
    "cpp_templates/杂项/(win)批处理文件编译.cpp": "Windows batch command example",
    "cpp_templates/杂项/.sh (linux)文件编译.cpp": "Linux shell command example",
    "cpp_templates/杂项/编译指令.cpp": "compiler command example",
}

# Some legacy snippets deliberately rely on globals or types described in main.tex.
CPP_CONTEXTS = {
    "cpp_templates/Other Trick/栈递归版dfs.cpp": "const ll INF = 4'000'000'000'000'000'000LL;\n",
    "cpp_templates/图论/SPFA.cpp": "constexpr int N = 1'000'005;\n",
    "cpp_templates/数学/matrix-qpow-base.cpp": "ll mod = 998244353;\n",
    "cpp_templates/数据结构/Seg-basic.cpp": "ll a[1'000'005]{};\n",
}

CPP_SMOKE = r"""
int main() {
    assert((prefix_function("ababaca") == vector<int>{0, 0, 1, 2, 3, 0, 1}));
    assert((kmp_search("aaaaa", "aaa") == vector<int>{0, 1, 2}));
    assert((z_function("aaaa") == vector<int>{4, 3, 2, 1}));

    Manacher manacher("abacaba");
    assert(manacher.longest_length() == 7);
    assert(manacher.is_palindrome(1, 6));
    assert(!manacher.is_palindrome(0, 4));

    RollingHash hash("abcabc");
    assert(hash.get(0, 3) == hash.get(3, 6));

    AhoCorasick ac;
    ac.add_pattern("he");
    ac.add_pattern("she");
    ac.add_pattern("hers");
    ac.add_pattern("his");
    ac.build();
    assert((ac.count_matches("ushers") == vector<i64>{1, 1, 1, 0}));

    PalindromicTree pam;
    int suffix_count = 0;
    for (char c : string("ababa")) {
        suffix_count = pam.add(c);
    }
    assert(suffix_count == 3);
    assert(pam.distinct_count() == 5);
    auto pal_occurrences = pam.occurrence_counts();
    assert(accumulate(pal_occurrences.begin() + 2, pal_occurrences.end(), 0LL) == 9);

    vector<int> sa = suffix_array("banana");
    assert((sa == vector<int>{5, 3, 1, 0, 4, 2}));
    assert((lcp_array("banana", sa) == vector<int>{0, 1, 3, 0, 0, 2}));

    SuffixAutomaton sam;
    sam.build("ababa");
    assert(sam.contains("bab"));
    assert(!sam.contains("baa"));
    assert(sam.distinct_substrings() == 9);
    assert(sam.occurrence_counts()[0] == 5);

    Fenwick<long long> fw(5);
    fw.add(1, 2);
    fw.add(2, 3);
    assert(fw.range_sum(0, 5) == 5);
    assert(fw.range_sum(2, 3) == 3);

    FenwickRangeSum<long long> range_fw(5);
    range_fw.range_add(1, 4, 2);
    range_fw.range_add(2, 3, 3);
    assert(range_fw.range_sum(0, 5) == 9);
    assert(range_fw.range_sum(2, 4) == 7);

    Fenwick2D<long long> fw2d(3, 3);
    fw2d.add(0, 0, 2);
    fw2d.add(1, 2, 3);
    fw2d.add(2, 2, -1);
    assert(fw2d.rectangle_sum(0, 0, 2, 3) == 5);
    assert(fw2d.rectangle_sum(2, 2, 3, 3) == -1);

    vector<vector<int>> dag{{1, 2}, {2}, {}};
    auto [is_dag, order] = topological_sort(dag);
    assert(is_dag && order.size() == 3);
    vector<int> position(3);
    for (int i = 0; i < 3; ++i) position[order[i]] = i;
    assert(position[0] < position[1] && position[1] < position[2]);
    vector<vector<int>> cyclic{{1}, {0}};
    assert(!topological_sort(cyclic).first);

    vector<vector<pair<int, int>>> zero_one_graph(4);
    zero_one_graph[0] = {{1, 1}, {2, 0}};
    zero_one_graph[2] = {{1, 0}};
    zero_one_graph[1] = {{3, 1}};
    assert((zero_one_bfs(zero_one_graph, 0) == vector<int>{0, 0, 0, 1}));

    Dinic dinic(4);
    dinic.add_edge(0, 1, 3);
    dinic.add_edge(0, 2, 2);
    dinic.add_edge(1, 2, 1);
    dinic.add_edge(1, 3, 2);
    dinic.add_edge(2, 3, 3);
    assert(dinic.max_flow(0, 3) == 5);

    MinCostMaxFlow mcmf(4);
    mcmf.add_edge(0, 1, 1, 1);
    mcmf.add_edge(0, 1, 1, 2);
    mcmf.add_edge(1, 3, 2, 3);
    assert((mcmf.min_cost_max_flow(0, 3) == pair<i64, i64>{2, 9}));

    vector<Point> points{{0, 0}, {1, 0}, {1, 1}, {0, 1}, {0, 0}, {0, 0}};
    assert(convex_hull(points).size() == 4);
    assert(convex_hull_diameter(points).squared_distance == 2);
}
"""


def fail(message: str) -> None:
    raise RuntimeError(message)


def read_utf8(path: Path) -> str:
    return path.read_text(encoding="utf-8-sig")


def relative(path: Path) -> str:
    return path.relative_to(ROOT).as_posix()


def audit_catalog() -> tuple[list[Path], list[str]]:
    if not TEMPLATE_DIR.is_dir():
        fail("cpp_templates directory is missing")
    sources = sorted(TEMPLATE_DIR.rglob("*.cpp"))
    if not sources:
        fail("no .cpp templates found")

    tex = read_utf8(ROOT / "main.tex")
    references = re.findall(r"\\lstinputlisting(?:\[[^\]]*\])?\{([^{}]+)\}", tex)
    if not references:
        fail("main.tex has no \\lstinputlisting entries")
    duplicates = sorted(name for name, count in collections.Counter(references).items() if count > 1)
    if duplicates:
        fail("templates listed more than once: " + ", ".join(duplicates))
    missing = [name for name in references if not (ROOT / Path(name)).is_file()]
    if missing:
        fail("main.tex references missing files: " + ", ".join(missing))

    source_names = {relative(path) for path in sources}
    reference_names = set(references)
    unlisted = sorted(source_names - reference_names)
    unknown = sorted(reference_names - source_names)
    if unlisted or unknown:
        details = []
        if unlisted:
            details.append("unlisted .cpp files: " + ", ".join(unlisted))
        if unknown:
            details.append("references outside cpp_templates: " + ", ".join(unknown))
        fail("; ".join(details))

    readme = read_utf8(ROOT / "README.md")
    total_match = re.search(r"\*\*(\d+) 个代码模板\*\*", readme)
    if not total_match or int(total_match.group(1)) != len(sources):
        fail(f"README total does not match actual template count ({len(sources)})")
    folder_counts = collections.Counter(path.parent.name for path in sources)
    for folder, count in folder_counts.items():
        pattern = re.escape(f"{folder}/ ({count})")
        if not re.search(pattern, readme):
            fail(f"README folder count is missing or stale: {folder}/ ({count})")

    return sources, references


def compiler_source(path: Path) -> str:
    rel = relative(path)
    source = read_utf8(path)
    if rel == "cpp_templates/杂项/扩栈指令.cpp":
        # This GNU/Linux-specific assembly snippet belongs inside main().
        return "#include <bits/stdc++.h>\nint main() {\n" + source + "\n}\n"

    prelude = CPP_PRELUDE
    if rel == "cpp_templates/数学/Stirling 数.cpp":
        # This template intentionally defines ll as unsigned long long.
        prelude = "#include <bits/stdc++.h>\nusing namespace std;\n"

    context = CPP_CONTEXTS.get(rel, "")
    if rel.startswith("cpp_templates/计算几何/"):
        geometry = TEMPLATE_DIR / "计算几何"
        base = read_utf8(geometry / "基础计算几何.cpp")
        point2d = read_utf8(geometry / "2D-point.cpp")
        point3d = read_utf8(geometry / "3D-point.cpp")
        dependencies = {
            "2D-point.cpp": base,
            "3D-point.cpp": base,
            "Line.cpp": base + point2d,
            "Segment.cpp": base + point2d + read_utf8(geometry / "Line.cpp"),
            "Triangle.cpp": base + point2d + read_utf8(geometry / "Line.cpp")
                             + read_utf8(geometry / "Segment.cpp"),
            "Polygon.cpp": base + point2d + read_utf8(geometry / "Line.cpp")
                           + read_utf8(geometry / "Segment.cpp"),
            "Circle.cpp": base + point2d + read_utf8(geometry / "Line.cpp")
                          + read_utf8(geometry / "Segment.cpp")
                          + read_utf8(geometry / "Triangle.cpp"),
            "Sphere.cpp": base + point3d,
        }
        context = dependencies.get(path.name, context)
        if path.name == "基础计算几何.cpp":
            context = ""
        if path.name == "基础计算几何.cpp":
            prelude = ""
    return prelude + context + source


def check_cpp_sources(compiler: str, standard: str, sources: list[Path]) -> int:
    non_cpp_found = set()
    checked = 0
    total = len(sources) - len(NON_CPP_TEMPLATES)
    print(f"[RUN] C++ syntax checks: {total} sources", flush=True)
    for path in sources:
        rel = relative(path)
        if rel in NON_CPP_TEMPLATES:
            non_cpp_found.add(rel)
            continue
        command = [compiler, f"-std={standard}", "-fsyntax-only", "-w", "-x", "c++", "-"]
        result = subprocess.run(
            command,
            input=compiler_source(path),
            text=True,
            encoding="utf-8",
            errors="replace",
            capture_output=True,
        )
        if result.returncode != 0:
            fail(f"C++ syntax check failed for {rel}:\n{result.stderr.strip()}")
        checked += 1
        if checked % 20 == 0:
            print(f"[RUN] C++ syntax checks: {checked}/{total}", flush=True)
    missing_non_cpp = set(NON_CPP_TEMPLATES) - non_cpp_found
    if missing_non_cpp:
        fail("non-C++ manifest entries were not found: " + ", ".join(sorted(missing_non_cpp)))
    print(f"[PASS] C++ syntax: {checked} files ({len(non_cpp_found)} documented command snippets excluded)", flush=True)
    return checked


def run_smoke_checks(compiler: str, standard: str) -> None:
    names = [
        "cpp_templates/数据结构/Fenwick.cpp",
        "cpp_templates/图论/拓扑排序与01最短路.cpp",
        "cpp_templates/图论/Dinic最大流.cpp",
        "cpp_templates/图论/最小费用最大流.cpp",
        "cpp_templates/字符串/字符串哈希.cpp",
        "cpp_templates/字符串/AC自动机.cpp",
        "cpp_templates/字符串/KMP1.cpp",
        "cpp_templates/字符串/KMP2.cpp",
        "cpp_templates/字符串/Z函数.cpp",
        "cpp_templates/字符串/最长回文子串.cpp",
        "cpp_templates/字符串/PAM.cpp",
        "cpp_templates/字符串/后缀数组.cpp",
        "cpp_templates/字符串/后缀自动机.cpp",
        "cpp_templates/计算几何/凸包与旋转卡壳.cpp",
    ]
    sources = [read_utf8(ROOT / name) for name in names]
    combined = CPP_PRELUDE + "\n".join(sources) + CPP_SMOKE
    with tempfile.TemporaryDirectory(prefix="xcpc-template-check-") as temp:
        temp_dir = Path(temp)
        executable = temp_dir / ("smoke.exe" if os.name == "nt" else "smoke")
        command = [compiler, f"-std={standard}", "-O2", "-Wall", "-Wextra", "-x", "c++", "-o", str(executable), "-"]
        result = subprocess.run(
            command,
            input=combined,
            text=True,
            encoding="utf-8",
            errors="replace",
            capture_output=True,
        )
        if result.returncode != 0:
            fail("smoke test compilation failed:\n" + result.stderr.strip())
        run = subprocess.run([str(executable)], text=True, capture_output=True)
        if run.returncode != 0:
            fail(f"algorithm smoke tests failed (exit {run.returncode}):\n{run.stdout}{run.stderr}")
    print("[PASS] Algorithm smoke checks: strings, Fenwick, graph flow, and convex hull", flush=True)


def build_pdf() -> None:
    latexmk = shutil.which("latexmk")
    if not latexmk:
        fail("latexmk was not found; install TeX Live or rerun with --skip-pdf")
    command = [
        latexmk,
        "-xelatex",
        "-interaction=nonstopmode",
        "-file-line-error",
        "-synctex=0",
        "main.tex",
    ]
    result = subprocess.run(
        command,
        cwd=ROOT,
        text=True,
        encoding="utf-8",
        errors="replace",
        capture_output=True,
    )
    if result.returncode != 0:
        output = (result.stdout + "\n" + result.stderr).strip()
        fail("LaTeX build failed:\n" + output[-12000:])
    if not (ROOT / "main.pdf").is_file():
        fail("latexmk returned success but main.pdf was not produced")
    print("[PASS] LaTeX build: main.pdf", flush=True)


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--compiler", default="g++", help="C++ compiler executable (default: g++)")
    parser.add_argument("--std", default="c++17", help="C++ language standard (default: c++17)")
    parser.add_argument("--skip-pdf", action="store_true", help="skip rebuilding main.pdf")
    args = parser.parse_args()

    compiler = shutil.which(args.compiler)
    if not compiler:
        print(f"[FAIL] C++ compiler not found: {args.compiler}", file=sys.stderr)
        return 1
    try:
        sources, references = audit_catalog()
        print(f"[PASS] Template catalog: {len(sources)} files, {len(references)} LaTeX references, README counts match", flush=True)
        checked = check_cpp_sources(compiler, args.std, sources)
        run_smoke_checks(compiler, args.std)
        if not args.skip_pdf:
            build_pdf()
        print(f"[PASS] Full check complete: {checked} syntax checks and smoke checks passed", flush=True)
        return 0
    except (OSError, RuntimeError, subprocess.SubprocessError) as error:
        print(f"[FAIL] {error}", file=sys.stderr)
        return 1


if __name__ == "__main__":
    raise SystemExit(main())
