#!/usr/bin/env bash
pidwait(){
	local pid=$1
	if [ -z $pid ]; then
					echo 'empty'
					return 1
	fi
	echo 'begin'
	while kill -0 "$pid" 2>/dev/null; do
					sleep 1
	done
}
sleep 20 &
bg_pid=$!
echo "test begin, pid of sleep is $bg_pid"
pidwait $bg_pid
echo 'now is next order: ls'
ls
# kill -0 :检查是否存在该任务，-0实际不执行任何操作
