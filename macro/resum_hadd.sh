#!/bin/bash
merge_list=""
for i in `ls $1/Run16Ana_MinBias_NoCMN_Sub-$1-*-$2.root`;
  do
#  echo $i
  merge_list="$merge_list $i"
done
echo $merge_list
hadd $1/sum_$2.root ${merge_list}
