#! /bin/bash

if [[ $# -lt 2 ]] || [[ $# -gt 2 ]]
then
  echo "Usage: $0 [reference program] [your program]"
exit 1
fi #check if it have enough arg

for i in *.txt
do
echo $i
  $1 < $i > reference
  $2 < $i > own
  diff reference own > result
  if [ -s result ] 
  then
echo "failed"
    cat result
else
echo "succeeded"
  fi #end if
done

rm -f reference own