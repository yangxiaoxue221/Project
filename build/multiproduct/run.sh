#! /bin/bash

log=../../log.log

count_cla=$(cat $log | grep "class" | awk '{print $1}' | wc -l)

count_stu=$(cat $log | grep "student" | awk '{print $1}' | wc -l)

echo "change class times : $count_cla"
echo
echo "change student times : $count_stu"
echo

echo -n "input a student number:"
read stu_num

k=$(cat $log | grep "$stu_num" | awk '{print $3}' | wc -l)

if [ $k -gt 0 ]
then
    echo "find $stu_num"
else
    echo "not find $stu_num"
fi

echo
echo -n "input a class number:"
read cla_num

k=$(cat $log | grep "$cla_num" | awk '{print $3}' | wc -l)

if [ $k -gt 0 ]
then
    echo "find $cla_num"
else
    echo "not find $cla_num"
fi
