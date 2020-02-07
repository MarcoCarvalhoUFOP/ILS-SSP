#!/bin/bash
FIRST=1
for var in "$@"
do
	if [ $FIRST -eq 2 ] 
	then
		echo "Executing method $1"
		./MTSP.exe -dir=$var -method=$1
	fi

	if [ $FIRST -eq 1 ] 
	then
		FIRST=2
		echo "$FIRST"
	fi
done


