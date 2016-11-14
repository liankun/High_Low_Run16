#!/bin/bash
merge=""
for i in `ls $1/sum_*.root`;
  do 
#  echo $i
  merge="$merge $i"
done
echo $merge
mv $1/sum.root $1/sum_bk.root 
hadd $1/sum.root $merge
