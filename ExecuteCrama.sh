#!/bin/bash



for i in $(seq ${1} 1 ${2})
do
	echo "Executing method 14"
	echo "./MTSP.exe -dir=GrupoA -method=14 -counter=${i} -iter=200"
	./MTSP.exe -dir=C-1 -method=14 -counter=${i} -iter=200

	#echo "Executing method 14"
	./MTSP.exe -dir=C-2 -method=14 -counter=${i} -iter=200

	#echo "Executing method 14"
	./MTSP.exe -dir=C-3 -method=14 -counter=${i} -iter=200
done