#!/usr/bin/env bash
# 编译本模板。
#   ./build.sh          # 编译 main.tex -> main.pdf
#   ./build.sh foo      # 编译 foo.tex  -> foo.pdf
set -o pipefail
cd "$(dirname "$0")" || exit 1
latexmk -xelatex -interaction=nonstopmode -file-line-error -synctex=0 "${1:-main}.tex"
