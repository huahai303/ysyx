#!/usr/bin/env bash

make clean
make ex17-g
./ex17-g db.dat c 10 64
./ex17-g db.dat s 1 zed zed@com 156
./ex17-g db.dat s 2 john john@com 134
./ex17-g db.dat s 3 jack jack@com 178
echo "list"
./ex17-g db.dat l
echo "find"
./ex17-g db.dat f zed
./ex17-g db.dat f john@com
./ex17-g db.dat f 178
./ex17-g db.dat d 3
echo "list"
./ex17-g db.dat l

