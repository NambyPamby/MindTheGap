#include "FASTA.h"

FASTA::FASTA(std::string fileName)
{
	std::string line;
	std::ifstream fastaStream(fileName);

	if (fastaStream.is_open())
	{
		std::string header;
		std::string sequence;

		while (std::getline(fastaStream, line))
		{
			// Is it a header or part of the sequence?
			if (line.compare(0, 1, ">") == 0)
			{
				// If we already have a sequence, then save it
				if (sequence.length() > 0)
				{
					//std::cout << "Inserting" << std::endl;
					insert(std::pair<std::string, std::string>(header, sequence));
					header = line;
					sequence.clear();
				}
				else
				{
					//std::cout << "Header: " << line << std::endl;
					header = line;
				}
			}
			else
			{
				// Append it to the sequence
				sequence.append(line);
			}
		}

		// Add the final sequence
		insert(std::pair<std::string, std::string>(header, sequence));

		fastaStream.close();
	}

	// Debug print
	for (const std::pair<std::string, std::string>& pair : *this)
		std::cout << pair.first << " (" << pair.second.length() << " base pairs)" << std::endl;
}

FASTA::~FASTA()
{
}
