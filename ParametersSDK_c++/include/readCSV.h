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

//std::vector<std::vector<std::string>> readCsv::readCsvTestCase(const std::string& testCase) {
//	std::string lineStr;
//	std::ifstream inFile(csvPath, std::ios::in);
//	std::vector<std::vector<std::string>> words; 
//
//	while (std::getline(inFile, lineStr)) {
//		std::stringstream sin(lineStr);
//		std::string str;
//		std::vector<std::string> lineArray;
//		while (std::getline(sin, str, ','))
//			lineArray.push_back(str);
//		words.push_back(lineArray);
//	}
//	inFile.close();
//
//	std::vector<std::vector<std::string>> testCan;
//	for (size_t i = 0; i < words.size(); i++) {
//		if (words[i][0] == testCase) {
//			testCan.push_back(words[i]);
//		}
//	}
//	if (testCan.size() == 0) {
//		std::cout << "The entered test case does not exist, please check and re-enter"
//			<< std::endl;
//		return testCan;
//	}
//	return testCan;
//}
//// 
//std::vector<std::vector<std::pair<std::string, std::string>>> readCsv::readCsvCameraCaptureParametersTestCase() {
//	std::ifstream inFile(csvPath, std::ios::in);
//	std::string lineStr;
//	int row = 0, col = 0;
//	std::vector<std::vector<std::string>> dateSet;
//
//	while (std::getline(inFile, lineStr)) {
//		std::stringstream sin(lineStr);
//		std::string text;
//		++row;
//		int tmp = 0;
//		std::vector<std::string> date;
//		while (std::getline(sin, text, ','))
//		{
//			date.emplace_back(text);
//			++tmp;	
//		}
//		if (tmp > col) { col = tmp; }
//
//		dateSet.emplace_back(date);
//	}
//	std::cout << "row = " << row << " ,col = " << col << std::endl;
//
//	std::vector<std::vector<std::pair<std::string, std::string>>> all;
//	if (col > 1) {
//		for (int i = 1; i < col; i++) {
//			std::vector<std::pair<std::string, std::string>> transSetVector;
//			
//			for (size_t j = 0; j < dateSet.size(); j++) {
//				std::pair<std::string, std::string>tmpPair(dateSet[j][0], dateSet[j][i]);
//				//std::stringstream sin2(dateSet[j][i]);
//				//std::string text2;
//				//std::vector<double> a;
//				//std::cout << dateSet[j][i] << std::endl;
//				//while (std::getline(sin2, text2, ',') 
//				//{
//				//	a.empalce_back(atof(text2.c_str()));
//				//}
//
//				transSetVector.emplace_back(tmpPair); // [ [] [] []...]
//			}
//			all.emplace_back(transSetVector);  // {[ [][] ... ],[ [][] ... ]}
//
//		}
//	}
//	std::cout << "size = " << all.size()<< std::endl;
//	return all;
//};





ReadFile::~ReadFile() { };

