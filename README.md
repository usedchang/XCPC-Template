# LaTeX CP 模板合集 🚀

个人 LaTeX 竞赛编程模板仓库：**101 个代码模板**，TeX Live + VS Code（用 XeLaTeX 编译）。

## 📁 仓库结构

```
main.tex                 # 主模板：宏包、代码高亮、目录，以及全部模板的引入与说明
cpp_templates/           # 101 个 .cpp 模板，按专题分目录
  ├── 杂项/ (15)      数据结构/ (14)  树/ (6)
  ├── 图论/ (16)      字符串/ (6)     动态规划/ (10)
  └── 数学/ (19)      计算几何/ (10)  Other Trick/ (5)
build.sh                 # 一键编译（latexmk -xelatex）
avatar-usedchang.png     # 封面头像
```

`main.tex` 用 `\lstinputlisting` **直接引入** `cpp_templates/` 下的 `.cpp` 文件，所以两者
必须一起下载：只拿 `main.tex` 会因找不到文件而编译失败。

每个算法的**用法、推导与复杂度都写在 `main.tex` 正文里**，`.cpp` 文件头部只留一行提示；
另外有一部分文件是**代码片段**（依赖外部的 `ll`、`N`、`a[]` 等定义），使用时按正文说明
补全上下文即可。

编译产生的中间文件（`*.aux`、`*.log`、`*.fls`、`*.fdb_latexmk`、`*.xdv` 等）已在
`.gitignore` 里忽略；注意 `main.pdf` 目前仍在版本库中（改动模板后重编译即可更新）。

## 🚀 使用方法

1. 克隆整个仓库（不要只下载 `main.tex`）
2. 用 VS Code + LaTeX Workshop 打开 `main.tex`
3. `Ctrl+Alt+B` 一键编译；或在仓库根目录执行 `./build.sh`（等价于
   `latexmk -xelatex -interaction=nonstopmode main.tex`）
4. `./build.sh foo` 可以编译 `foo.tex`

## ➕ 新增一个模板

1. 把代码放到 `cpp_templates/<专题>/<名字>.cpp`
2. 在 `main.tex` 对应大节里加一行（`breakatwhitespace=false` 等选项按需加）：

   ```latex
   \lstinputlisting[caption={说明}, breakatwhitespace=false]{cpp_templates/<专题>/<名字>.cpp}
   ```

3. 在该小节正文里补上用法说明（讲用法的地方是正文，`.cpp` 头部只写一句）
4. 重新编译，确认 `main.log` 里没有以 `!` 开头的报错

## 📖 收录内容

完整清单看 `main.pdf` 的目录，这里只列概况：

- **数据结构**（14）：ST 表、并查集（普通 / 带权 / 可撤销 / 可持久化）、线段树（区间加 + 区间和 /
  可持久化主席树）、笛卡尔树、Trie / 01-Trie、FHQ-Treap、莫队、根号分治（含无向图三元环计数）
- **图论**（16）：SPFA、Dijkstra（堆 / 邻接矩阵）、Kruskal / Prim / Kruskal 重构树、欧拉回路、
  二分图（染色 / 匈牙利 / Dinic / KM 最大权匹配）、差分约束、SCC、DECC、2-SAT
- **字符串**（6）：字符串哈希、KMP、Z 函数、Manacher、PAM
- **动态规划**（10）：01 / 完全 / 多重背包、树上背包、换根 dp、区间 dp、SOS dp、数位 dp、双向搜索
- **数学**（19）：线性筛（因数 / 欧拉 / 莫比乌斯）、整除分块、莫比乌斯反演、排列组合（含 Lucas）、
  卡特兰数、斯特林数、矩阵快速幂、高斯消元、FFT / NTT、Berlekamp-Massey、Pollard-Rho、
  异或线性基、exgcd / exBSGS、分治求幂级数和、博弈论 SG 打表
- **计算几何**（10）：基础定义、点 / 向量、直线、线段、三角形、圆（含最小覆盖圆）、多边形、球、
  极角排序
- **树**（6）：LCA（倍增 / O(1)）、树的直径、树链剖分、树上启发式合并
- **杂项**（15）：快读、`__int128`、对拍（win / linux）、随机数、编译指令、扩栈、
  pbds 平衡树 / 哈希表 / 堆、rope 块状链表、字典树（pbds trie 与 map 版）
- **Other Trick**（5）：多路归并（堆 / 二分）、栈模拟递归防溢出、LogTrick、异或前缀规律、
  高阶差分、曼哈顿↔切比雪夫、可重集合哈希判等

## 📝 后续计划

- 树状数组（1D / 2D / 权值）
- AC 自动机、后缀数组、后缀自动机
- 费用流 / 上下界网络流、一般图最大匹配
- 凸包 + 旋转卡壳、半平面交

**欢迎 Star & Fork！** 有问题直接 Issue～

---
作者：yan-hongchang | 更新于 2026
