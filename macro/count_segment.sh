#!/bin/bash
count=0
flag=0
group=0
group_num=0
group_sum=""
for i in `ls -d 45*`;
  do
  Num=`ls $i/Run16Ana_MinBias_NoCMN_Sub-* | wc -l`
  
  if [ $flag -eq 4 ];
    then
    echo "Group : $group"
    flag=0
    group=0
    echo "The Group: $group_num"
    echo $group_sum
    echo "will merge them"
    mkdir -p sum_sum_runs/$group_num
    hadd sum_sum_runs/$group_num/sum_sum.root $group_sum 
    group_num=$((group_num + 1))
    group_sum=""
  fi
  
  echo "$i $Num"
  

  if [ $i -lt 455362 ];
    then
      count=$((count + 1))
      group_sum="$group_sum $i/sum.root"
      flag=$((flag + 1))
      group=$((Num + group))
    else
      echo "The Group: $group_num"
      mkdir -p sum_sum_runs/$group_num
      cp $i/sum.root sum_sum_runs/$group_num/sum_sum.root
      group_num=$((group_num + 1))
  fi
done

echo "Number of runs for small segment: $count"


