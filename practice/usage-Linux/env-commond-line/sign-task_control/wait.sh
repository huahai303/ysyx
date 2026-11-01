#!/usr/bin/env bash

# 启动后台进程 sleep 60
sleep 60 &
pid=$!

echo "等待后台进程 $pid 结束..."

# wait 会阻塞当前脚本，直到该进程结束
wait $pid

echo "后台进程已结束，现在执行 ls:"
ls
