#!/bin/bash
merge_file=""
for i in `seq 31 40`;
  do
    echo $i
    merge_file="$i/sum_sum.root $merge_file"
done
echo $merge_file
hadd sum_all_runs3.root $merge_file
