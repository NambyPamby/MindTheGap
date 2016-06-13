#!/bin/sh

declare -a CHROME_ARRAY=(1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 X Y)

TOTAL=${#CHROME_ARRAY[@]}

COUNTER=0
while [ $COUNTER -lt $TOTAL ]; do

	CHROME=${CHROME_ARRAY[$COUNTER]}
	FASTA_FILE="query-${CHROME}.fa"
	RESULT_FILE="result-${CHROME}.csv"
	
	# How many As, Cs, Gs and Ts are in the query file?
	QUERY_TOTAL_BP=`grep -v "^>" ${FASTA_FILE} | egrep -o '[ACGT]' | wc -l`

	# How many sequences?	
	QUERY_SEQUENCES=`grep ">" ${FASTA_FILE} | wc -l`

	# How many results did we get?
	RESULT_HSPS=`cat ${RESULT_FILE} | wc -l`

	# How many identical nucleotides?
	NIDENT_TOTAL_BP=`awk -F "," '{ sum += $9; } END { print sum }' $RESULT_FILE`

	echo ${CHROME},${QUERY_TOTAL_BP},${NIDENT_TOTAL_BP},${RESULT_HSPS},${QUERY_SEQUENCES}

	# iterate
	let COUNTER=$COUNTER+1
done
