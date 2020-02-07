#!/bin/bash


for i in $(seq ${1} 1 ${2})
do
	echo "Executing method 14"
	echo "./MTSP.exe -dir=GrupoE -method=14 -counter=${i} -iter=200"

	./MTSP.exe -dir=GrupoE -method=14 -counter=${i} -iter=200
done
