#!/usr/bin/env bash
boot_id=${1:-0}
journalctl -b -"$boot_id" --no-page | grep -E "Logs begin at|Startup finished in"\
		| grep "systemd\[1\]:" | sed -E 's/.* = (.*)s./\1/' > record.txt
		record=$(cat record.txt)
echo "$record"
