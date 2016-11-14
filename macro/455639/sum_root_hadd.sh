#!/bin/bash
merge_list=""
run_number=${1}
#for i in `seq 0 38`;
#  do
#   echo $i
#   list=`ls Run16Ana_MinBias_NoCMN_Sub-455639-$i-*.root`
#   merge_list="$merge_list Run16Ana_MinBias_NoCMN_Sub_-455639-$i-0.root"
#   echo $list
#   hadd sum$i.root $list
#done

#echo $merge_list
#hadd ${run_number}/sum.root ${merge_list}

list=`ls sum_?.root`
echo $list
hadd sum.root $list
