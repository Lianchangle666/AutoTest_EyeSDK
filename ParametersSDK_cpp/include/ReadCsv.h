#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using CaseValue = std::pair<std::string, std::string>;


class ReadFile
{
public:
	ReadFile() = delete;
	ReadFile(ReadFile&) = delete;
	ReadFile(const std::string);
	std::vector<CaseValue> ReadTestCase();
	~ReadFile();

private:
	std::string path;

};

ReadFile::ReadFile(const std::string path) : path(path) { }

// 
std::vector<CaseValue> ReadFile::ReadTestCase()
{
	int row = 0;
	std::string linestring;
	std::ifstream infile(path, std::ios::in);
	std::vector<CaseValue> allnameparameter;

	while (std::getline(infile, linestring))
	{
		int col = 0;
		std::stringstream sin(linestring);
		std::string split;
		CaseValue nameparameter;
		
		row++;
		
		while (std::getline(sin, split, ','))
		{
			if (row != 1)
			{
				if (col == 0)
				{
					nameparameter.first = split;
					col++;
				}
				else
				{
					nameparameter.second = split;
					col = 0;
				}
				//std::cout << split << std::endl;
			}
		}
		allnameparameter.emplace_back(nameparameter);
	}
	infile.close();

	//std::cout << allnameparameter.size() << std::endl;
	return allnameparameter;
}

ReadFile::~ReadFile() { };

