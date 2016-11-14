#!/bin/bash
num=16
for i in `cat remerge_list.txt`;
  do 
  echo $i 
  cp $i/sum.root sum_sum_runs/${num}/sum_sum.root
  num=$((num + 1))
done
