#!/usr/bin/env bash

if [ $# -eq 0 ]; then
				echo "用法：$(basename "$0") <文件名> " >&2
				exit 1
fi
file=$1
if [ -f "$file" ]; then
				echo "文件存在：$file"
				exit 0;
else
				echo "文件不存在或者不是普通文件：$file" >&2
				exit 1
fi
