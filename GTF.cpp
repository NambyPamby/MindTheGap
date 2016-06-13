#include "GTF.h"

gtfLine::gtfLine(std::string line)
{
	// Now parse each tab-delimited line
	std::istringstream lineStream(line);

	std::string token;
	while (std::getline(lineStream, token, '\t'))
	{
		push_back(token);
	}
}

gtfLine::~gtfLine()
{
}

GTF::GTF(std::string fileName)
{

	std::string line;
	std::ifstream gtfStream(fileName);

	if (gtfStream.is_open())
	{
		while (std::getline(gtfStream, line))
		{
			gtfLine l(line);
			push_back(gtfLine(line));
		}

		gtfStream.close();
	}

}

GTF::GTF()
{
}

GTF::~GTF()
{
}
