#!/bin/bash

db=/tmp/db.sqlite3
bin=/tmp/create_db

gcc create_db.cc -std=c++17 -lstdc++ -lsqlite3 -o $bin
[ $? -ne 0 ] && echo $BASH_SOURCE - gcc error && exit 1

rm -f $db
$bin
[ $? -ne 0 ] && echo $BASH_SOURCE - run error && exit 2

sqlite3 $db


exit 0




