#!/bin/bash
merge_file=""
for i in `seq 41 43`;
  do
    echo $i
    merge_file="$i/sum_sum.root $merge_file"
done
echo $merge_file
hadd sum_all_runs4.root $merge_file
