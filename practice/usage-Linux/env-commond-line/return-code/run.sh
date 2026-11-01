#!/usr/bin/env bin
count=0
while true; do
				./target.sh > stdout.log 2>stderr.log
				if [ $? -ne 0 ]; then
								echo "error after $count"
								break
				fi
				count=$((count + 1))
done

