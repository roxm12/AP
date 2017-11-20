#! /bin/sh

#자료 받아오는 부분

echo $1>~/AP/test3_c/com/test.json

killall -SIGUSR1 main_exe
