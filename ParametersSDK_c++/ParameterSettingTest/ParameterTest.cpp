#include <iostream>
#include "MechEyeApi.h"
#include "MainFunction.h"


int main()
{
	std::string ip = "192.168.20.46";
	std::string path = R"(../log_data_drive.csv)";
	FunctionPackage fp(path, ip);
	fp.FunctionMain();
	return 0;
}
