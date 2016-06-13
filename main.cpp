#include <iostream>
#include <algorithm>
#include <map>
#include <cstdio>

#include "GTF.h"
#include "FASTA.h"

const char* HUMAN_TEMPLATE = "/Users/glenn/Data/Ensembl/GRCh37/Homo_sapiens.GRCh37.75.dna.chromosome.%s.fa";
const char* CHIMP_TEMPLATE = "/Users/glenn/Data/Ensembl/CHIMP2.1.4/Pan_troglodytes.CHIMP2.1.4.dna.chromosome.%s.fa";

int main(int argc, char *argv[])
{
	if (argc < 1)
	{
		std::cerr << "Usage: " << argv[0] << " <gtf_file>" << std::endl;
		return 1;
	}

	// Load the GTF file
	std::string gtfFile = std::string(argv[1]);
	GTF gtf(gtfFile);

	// Now sort each line of the GTF file into its own chromosome
	std::map<std::string, GTF> gtfMap;

	for (const gtfLine& gLine : gtf)
	{
		// Chromosome is the first field
		std::string chrome = gLine[0];

		// Does the map have this key?
		if (gtfMap.count(chrome) == 0)
			gtfMap[chrome] = GTF();

		// Now add the line to it
		gtfMap[chrome].push_back(gLine);
	}

	// How many nucleotides in total are we BLASTing?
	int totalNucleotideCount = 0;

	// So the gtfMap has 24 elements (one per chromosome: 1-22,X,Y)
	// The job now is to create a FASTA file per chromosome
	for (const std::pair<std::string, GTF>& pair : gtfMap)
	{
		std::string chrome = pair.first;
		chrome.erase(0, 3); // Get rid of the "chr" at the beginning

		// Open the FASTA file and get a reference to the sequence
		std::string fastaFileName(HUMAN_TEMPLATE);
		fastaFileName.replace(fastaFileName.find("%s"), 2, chrome);

		std::cout << "Looking for " << fastaFileName << std::endl;

		FASTA fasta(fastaFileName);

		std::cout << "File loaded; " << fasta.size() << " sequence[s]" << std::endl;
		std::pair<std::string, std::string> fastaPair = *(fasta.begin());
		std::string chromeSequence = fastaPair.second;

		std::cout << "Primary sequence is " << chromeSequence.length() << " base pairs" << std::endl;

		std::string queryFileName = "query-" + chrome + ".fa";
		std::ofstream query(queryFileName);

		int qSeqNum = 0;

		// Now for each gtfLine, pull out the sequence
		for (const gtfLine& line : pair.second)
		{
			int beginSequence = std::atoi(line[3].c_str());
			int endSequence = std::atoi(line[4].c_str());
			int length = (endSequence - beginSequence) - 1;
			std::string description = line[8];

			// Ignore any short queries
			const int MINIMUM_QUERY = 30;
			if (length < MINIMUM_QUERY) continue;

			// Sum the number of nucleotides
			totalNucleotideCount += length;

			query << ">"  << ++qSeqNum << " " << chrome << ":" << beginSequence << "-" << endSequence
				<< " " << description << std::endl;

			// Now print out the sequence in 60 byte chunks
			while (beginSequence <= endSequence)
			{
				const int WIDTH = 60;
				query << chromeSequence.substr(beginSequence, std::min(endSequence - beginSequence, WIDTH)) << std::endl;
				beginSequence += WIDTH;
			}
		}

		query.close();
	}

	// How big is our query?
	std::cout << std::endl << "In total, we are BLASTing " << totalNucleotideCount << " nucleotides" << std::endl;
}