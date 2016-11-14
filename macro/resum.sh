#!/bin/bash
for i in `cat remerge_list2.txt`;
  do
    echo $i
    ./resum_sum_hadd.sh $i
done
