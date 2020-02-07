#!/bin/bash



for i in $(seq ${1} 1 ${2})
do
	echo "Executing method 14"
	echo "./MTSP.exe -dir=A1 -method=14 -counter=${i} -iter=200"

	./MTSP.exe -dir=A1 -method=14 -counter=${i} -iter=200
	./MTSP.exe -dir=A2 -method=14 -counter=${i} -iter=200
	./MTSP.exe -dir=A3 -method=14 -counter=${i} -iter=200
	./MTSP.exe -dir=A4 -method=14 -counter=${i} -iter=200

	./MTSP.exe -dir=B1 -method=14 -counter=${i} -iter=200
	./MTSP.exe -dir=B2 -method=14 -counter=${i} -iter=200
	./MTSP.exe -dir=B3 -method=14 -counter=${i} -iter=200
	./MTSP.exe -dir=B4 -method=14 -counter=${i} -iter=200


done
