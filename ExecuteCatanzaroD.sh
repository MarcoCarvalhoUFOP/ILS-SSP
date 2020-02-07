#!/bin/bash



for i in $(seq ${1} 1 ${2})
do
	echo "Executing method 14"
	echo "./MTSP.exe -dir=A1 -method=14 -counter=${i} -iter=200"

	./MTSP.exe -dir=D1 -method=14 -counter=${i} -iter=200
	./MTSP.exe -dir=D2 -method=14 -counter=${i} -iter=200
	./MTSP.exe -dir=D3 -method=14 -counter=${i} -iter=200
	./MTSP.exe -dir=D4 -method=14 -counter=${i} -iter=200
done
