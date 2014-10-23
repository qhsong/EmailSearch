#!/bin/sh

. ./bloom.conf

echo "参数配置如下:"
echo "bloom数组长度vector_size=$vector_size."
echo "输入邮箱集合文件inputfile=$inputfile"
echo "待检测有相集合文件checkedfile=$checkedfile"
echo "结果文件resultfile=$resultfile"

time ./strfind $vector_size $inputfile $checkedfile $resultfile
