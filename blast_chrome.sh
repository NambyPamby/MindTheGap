#!/bin/sh

QUERY=$1
SUBJECT=$2
RESULT=$3

blastn -query $QUERY -subject $SUBJECT -out $RESULT \
	-dust no -soft_masking false -max_hsps 1 -word_size 7 \
        -outfmt '10 qseqid qstart qend sseqid sstart send qstart qend qlen length nident pident evalue'
