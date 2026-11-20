#!/usr/bin/env bash
# replace.sh - 当前目录（不含子目录）内精确替换字符串，含文件内容和文件名
# 用法: ./replace.sh <旧字符串> <新字符串>
set -euo pipefail

if [ $# -ne 2 ]; then
    echo "用法: $0 <旧字符串> <新字符串>" >&2
    exit 1
fi

OLD=$1
NEW=$2
SELF=$(basename -- "$0")

# 空目录时 * 不展开成字面量
shopt -s nullglob

for f in *; do
    # 只处理普通文件，跳过目录
    [ -f "$f" ] || continue

    # 跳过脚本自身
    if [ "$f" = "$SELF" ]; then
        continue
    fi

    # ---- 1) 替换文件内容（字面量匹配）----
    OLD="$OLD" NEW="$NEW" \
        perl -pi -e 's/\Q$ENV{OLD}\E/$ENV{NEW}/g' -- "$f"

    # ---- 2) 重命名文件（文件名含旧字符串时）----
    if [[ $f == *"$OLD"* ]]; then
        nf=${f//"$OLD"/"$NEW"}          # 加引号 => 字面量替换
        if [ -e "$nf" ]; then
            echo "跳过重命名（目标已存在）: $f -> $nf" >&2
        else
            mv -- "$f" "$nf"
        fi
    fi
done
