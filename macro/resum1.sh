#!/bin/bash
for i in `cat remerge_list2.txt`;
  do
    echo $i
    ./resum_hadd.sh $i 1
done
