#! /bin/bash
#Wen Xi Zhang && Hiu Hong Yu

#check if it has enough argument
if [ $# -lt 1 ]
then
	echo "Executable name required."
	echo "usage: $0 executable_name"
exit 1
fi
#set the name of the out put file
output_file=$1
shift
option=""
while [ $# -ge 1 ]
do
	option="${option}${1} "
	shift
done
#seacrch for all .cpp file change it into .o and print in Makefile
echo -n "$output_file : " > Makefile
for fn in *.cpp
do
	echo -n ${fn%cpp}o" " >> Makefile
done
echo -n -e "\n\tg++ -ansi -Wall -g -c " >> Makefile
echo -n "$output_file " >> Makefile
echo -n "$option" >> Makefile
for fn in *.cpp
do
	echo -n ${fn%cpp}o" " >> Makefile
done
echo -n -e "\n\n" >> Makefile

#seach to see if there is header file contain in the .cpp, if there is
#list in its dependencies
for cpp in *.cpp
do
	h_file=""
	echo -n ${cpp%cpp}o :" " >> Makefile
	echo -n $cpp" " >> Makefile
	for h in *.h
	do
		grep "$h" -q $cpp
		a=$?
		if [ $a -eq 0 ]
		then
			h_file="${h_file}${h} "
		fi
	done
	echo -n "$h_file" >> Makefile
	echo -n -e "\n\tg++ -ansi -Wall -g -c " >> Makefile
	echo -n "$option" >> Makefile
	echo -n -e "$cpp\n\n" >> Makefile
done

#makeclean
echo -n -e "clean : \n\trm -f " >> Makefile
echo -n "$output_file " >> Makefile
for fn in *.cpp
do
	echo -n ${fn%cpp}o" " >> Makefile
done
echo -n -e "\n" >> Makefile
