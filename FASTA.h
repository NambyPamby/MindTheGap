#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <string>
#include <map>

class FASTA : public std::map<std::string, std::string>
{
public:
	FASTA(std::string fileName);
	~FASTA();
};

