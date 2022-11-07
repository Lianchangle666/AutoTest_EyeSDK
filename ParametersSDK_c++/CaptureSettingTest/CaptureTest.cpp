#include <iostream>
#include "MechEyeApi.h"
#include "CaptureFunction.h"
int main()
{


	int n = 0;
	while (n < 2000)
	{
		std::string ip = "192.168.20.214";
		std::string path = R"(../PROM_AntiFlickerMode.csv)";
		CapturePackage cp(path, ip);
		//cp.FunctionMain();  // Send parameters
		cp.FunctionCaptureColorMap(std::to_string(n));
		cp.FunctionCaptureDepthMap(std::to_string(n));
		n++;
	}
	//fp.FunctionMain();
    return 0;
}
