#pragma once
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

class gtfLine : public std::vector<std::string>
{
public:
	gtfLine(std::string line);
	~gtfLine();
};

class GTF : public std::vector<gtfLine>
{
public:
	GTF(std::string fileName);
	GTF();
	~GTF();
};

