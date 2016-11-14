#!/bin/bash
for i in `seq 0 16`;
  do echo $i
    root -l -q -b fit_hl_switch.C'('$i')' 
done
