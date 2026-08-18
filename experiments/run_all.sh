#!/usr/bin/env bash
# Re-run every experiment and print its output.
# All numbers quoted in lessons/ come from these programs -- if you change a
# number in a lesson, re-run this first and use the real output.
#
# Usage:  bash experiments/run_all.sh
set -u
cd "$(dirname "$0")"
CXX=${CXX:-c++}
STD=-std=c++17

hdr(){ printf '\n\033[1m=== %s ===\033[0m\n' "$1"; }
build(){ $CXX $STD "$2" "$1" -o /tmp/_oi_exp 2>&1; }

hdr "环境"
uname -srm
$CXX --version | head -1
echo "栈上限: $(ulimit -s) KB"

hdr "01 · int 溢出：确定的负数，不是随机值"
build 01-overflow/overflow_basic.cpp -O0 && /tmp/_oi_exp

hdr "01 · UB：同一份源码，-O0 与 -O2 结论相反"
build 01-overflow/ub_optimized_away.cpp -O0 && echo "[-O0]" && /tmp/_oi_exp
build 01-overflow/ub_optimized_away.cpp -O2 && echo "[-O2]" && /tmp/_oi_exp

hdr "01 · 同一个 y 自相矛盾（-O2）"
build 01-overflow/two_faces.cpp -O2 && /tmp/_oi_exp

hdr "02 · 大数组在栈上 vs 全局区"
build 02-memory/stack_overflow.cpp -O0 && (/tmp/_oi_exp; echo "退出码 $? (139=段错误，预期如此)")
build 02-memory/global_array.cpp  -O0 && (/tmp/_oi_exp; echo "退出码 $?")

hdr "02 · 内存布局对遍历速度的影响（约 963x）"
build 02-memory/layout_traversal.cpp -O2 && /tmp/_oi_exp

hdr "02 · vector 扩容代价（约 3.4x）"
build 02-memory/vector_growth.cpp -O2 && /tmp/_oi_exp

hdr "02 · 最大递归深度"
build 02-memory/recursion_depth_empty.cpp -O0 && \
  echo "空函数，崩在第 $(/tmp/_oi_exp 2>/dev/null | tail -1) 层"
build 02-memory/recursion_depth_dfs.cpp -O0 && \
  echo "带局部变量，崩在第 $(/tmp/_oi_exp 2>/dev/null | tail -1) 层"

rm -f /tmp/_oi_exp
printf '\n\033[1m全部实验结束\033[0m\n'
