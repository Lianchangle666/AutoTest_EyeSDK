#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

class readCsv
{
public:
	/**
	* Constructor.
	*/
	readCsv();
	
	/**
	* Constructor.
	*/
	readCsv(std::string&);

	/**
	* No Copy.
	*/
	readCsv(readCsv&) = delete;

	/**
	* @brief Setting the CSV Path.
	* @param [in] CSV path.
	* @return Specify a vector of test cases.
	*/
	void setCsvPath(std::string&);
	
	/**
	* @brief Store the test cases specified in the CSV in a vector
	* @return CSV path.
	*/
	std::string getCsvPath();

	/**
	 * @brief Store the test cases specified in the CSV in a vector
	 * @param [in] Test cases in CSV.
	 * @return Specify a vector of test cases.
	 */
	std::vector<std::vector<std::string>> readCsvTestCase(const std::string&);

	/**
	* Destructor.
	*/
	~readCsv();

private:
	std::string csvPath;

};

class writeCsv
{
public:
	/**
	* Constructor.
	*/
	writeCsv();

	/**
	* No Copy.
	*/
	writeCsv(writeCsv&) = delete;

	/**
	* @brief Write result messages to CSV file.
	* @return None.
	*/
	void writeResultToCsv(const std::string, const std::string, const std::string, const std::string, const std::string);

	/**
	* Destructor.
	*/
	~writeCsv();


private:
	std::string csvCreatePath;
};


readCsv::readCsv() {
	std::string csvfile = "../data.csv";
	std::ifstream fin(csvfile);
	if (!fin) {
		std::cout << "No CSV file exists in the project path! " << std::endl;
		return;
	}
	csvPath = csvfile;
	fin.close();
}

readCsv::readCsv(std::string& csvPath) :csvPath(csvPath) { };

void readCsv::setCsvPath(std::string& csvPath) {
	this->csvPath = csvPath;
}

std::string readCsv::getCsvPath() { 
	return csvPath; 
}

std::vector<std::vector<std::string>> readCsv::readCsvTestCase(const std::string& testCase) {
	std::string lineStr;
	std::ifstream inFile(csvPath, std::ios::in);
	std::vector<std::vector<std::string>> words; 

	while (std::getline(inFile, lineStr)) {
		std::stringstream sin(lineStr);
		std::string str;
		std::vector<std::string> lineArray;
		while (std::getline(sin, str, ','))
			lineArray.push_back(str);
		words.push_back(lineArray);
	}
	inFile.close();

	std::vector<std::vector<std::string>> testCan;
	for (size_t i = 0; i < words.size(); i++) {
		if (words[i][0] == testCase) {
			testCan.push_back(words[i]);
		}
	}
	if (testCan.size() == 0) {
		std::cout << "The entered test case does not exist, please check and re-enter"
			<< std::endl;
		return testCan;
	}
	return testCan;
}

readCsv::~readCsv(){ }



writeCsv::writeCsv() {
	std::ofstream outfile;
	this->csvCreatePath = "result.csv";
	outfile.open(csvCreatePath, std::ios::_Noreplace);
	outfile << "TestCase" << "," << "Set" << "," << "Get" << "," <<"Result" << "," <<"ReturnMsgs" << std::endl;
	outfile.close();
}

void writeCsv::writeResultToCsv(const std::string TestCase, const std::string SetValue,
								const std::string GetValue, const std::string Result, const std::string ErrorMessage) {
	std::ofstream outfile;
	outfile.open(csvCreatePath, std::ios::app);
	outfile << TestCase << "," << SetValue << "," << GetValue << "," << Result<< "," << ErrorMessage <<std::endl;
	outfile.close();
}

writeCsv::~writeCsv() { };