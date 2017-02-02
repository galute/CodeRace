#!/bin/bash

for i in {1..500000};
   do for j in {1..16};
      do r=$(( $RANDOM % 10 )); echo -n $r >> temp.txt;
   done
   echo >> temp.txt;
done


