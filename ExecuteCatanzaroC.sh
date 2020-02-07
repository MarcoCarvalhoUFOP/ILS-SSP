#!/bin/bash



for i in $(seq ${1} 1 ${2})
do
	echo "Executing method 14"
	echo "./MTSP.exe -dir=A1 -method=14 -counter=${i} -iter=200"

	./MTSP.exe -dir=C1 -method=14 -counter=${i} -iter=200
	./MTSP.exe -dir=C2 -method=14 -counter=${i} -iter=200
	./MTSP.exe -dir=C3 -method=14 -counter=${i} -iter=200
	./MTSP.exe -dir=C4 -method=14 -counter=${i} -iter=200

done
