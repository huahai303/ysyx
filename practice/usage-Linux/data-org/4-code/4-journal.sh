#!/usr/bin/env bash
sudo journalctl -b -$1 --no-page | grep -E "Logs begin at|Startup finished in"\
		| grep "system\[1\]:" | sed -E 's/.* = (.*)s./\1/' > record.txt
		record=$(cat record.txt)
echo "$record"
