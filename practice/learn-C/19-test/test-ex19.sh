#!/bin/bash

set -e

GAME="./ex19"
PASS=0
FAIL=0

check_output(){
				local test_name="$1"
				local action="$2"
				local expect="$3"

				output=$(printf "$action" | $GAME)
				if echo "$output" | grep -q "$expect"; then
								echo "pass $test_name"
								PASS=$((PASS + 1))
				else
								echo "fail $test_name"
								echo "expect: $expect"
								echo "actual : $output"
								FAIL=$((FAIL + 1))
				fi
}
check_output "查看房间(l)" "l\n" "You can go:"

check_output "合法移动(向北)" "n\n" "You go north, into:"

check_output "非法移动(撞墙)" "s\n" "You can't go that direction."

check_output "攻击空气" "a\n" "You flail in the air at nothing."

check_output "走到竞技场并攻击怪物" "n\nw\na\n" "You attack The evil minotaur"

check_output "无效输入" "z\n" "What?: 122"

check_output "退出游戏" "" "Giving up? You suck."
echo "============================="
echo "result: pass;$PASS fail:$FAIL"
echo "============================="

