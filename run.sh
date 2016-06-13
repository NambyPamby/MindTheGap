#!/bin/sh

BASEDIR="/Users/glenn/Data/Ensembl"
BLAST="./blast_chrome.sh"

SUBJECT="$BASEDIR/CHIMP2.1.4/Pan_troglodytes.CHIMP2.1.4.dna.chromosome.%s.fa"

# All chromosomes
declare -a CHROME=(1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 X Y)

while [ ${#CHROME[@]} -gt 0 ]
do
	echo ${#CHROME[@]} 'chromosomes left : ' ${CHROME[@]}

	# Start another process - choose a chromosome
	index=$(( $RANDOM % ${#CHROME[@]} ))
	chrome_name=${CHROME[$index]}

	echo 'Chosen' $chrome_name 'at position' $index
	unset CHROME[$index] # unsets, but does not remove
	CHROME=( ${CHROME[*]} ) # copy the array, exclude empty elements

	QUERY_FILE=$(printf "query-%s.fa" $chrome_name)
	SUBJECT_FILE=$(printf $SUBJECT $chrome_name)
	OUTFILE=$(printf "result-%s.csv" $chrome_name)

	echo 'Launching chromosome' $chrome_name
	$BLAST $QUERY_FILE $SUBJECT_FILE $OUTFILE
	
done

wait

exit
