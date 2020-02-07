#!/bin/bash


for i in $(seq ${1} 1 ${2})
do
	echo "Executing method 14"
	echo "./MTSP.exe -dir=GrupoA -method=14 -counter=${i} -iter=200"

	./MTSP.exe -dir=GrupoA -method=14 -counter=${i} -iter=200

	echo "./MTSP.exe -dir=GrupoC -method=14 -counter=${i} -iter=200"

	./MTSP.exe -dir=GrupoB -method=14 -counter=${i} -iter=200

	echo "./MTSP.exe -dir=GrupoB -method=14 -counter=${i} -iter=200"

	./MTSP.exe -dir=GrupoC -method=14 -counter=${i} -iter=200
done
