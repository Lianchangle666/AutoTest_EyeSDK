#pragma once
#include "readCSV.h"
#include "MechEyeApi.h"
#include "SampleUtil.h"
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>

const std::string PASS = "pass";
const std::string FAIL = "fail";

inline std::string newshowError(const mmind::api::ErrorStatus& status)
{
	if (status.isOK())
		return " ";
	std::string errorMessage = 
		"Error Code: " + std::to_string(status.errorCode) + ", Error Description: "+ status.errorDescription;
	std::cout << errorMessage << std::endl;
	return errorMessage;
}

template<typename T>
inline std::string tostring(const std::vector<T>& param) {
	std::string p = "";
	for (auto x : param) {
		p = p + std::to_string(x) + " ";
	}
	return p;
}



class LinkCamera
{
public:
	LinkCamera() {
		showError(device.connect("192.168.23.67"));
		mmind::api::MechEyeDeviceInfo deviceInfo;
		showError(device.getDeviceInfo(deviceInfo));
		std::string mymodel = deviceInfo.model;
		std::transform(mymodel.begin(), mymodel.end(), mymodel.begin(), std::tolower);
		std::cout << mymodel << std::endl;
	}

	LinkCamera(std::string& CameraIp) {
		this->CamIp = CameraIp;
		showError(device.connect(CamIp));
		mmind::api::MechEyeDeviceInfo deviceInfo;
		showError(device.getDeviceInfo(deviceInfo));
		std::string mymodel = deviceInfo.model;
		std::transform(mymodel.begin(), mymodel.end(), mymodel.begin(), std::tolower);
		std::cout << mymodel << std::endl;
		this->CamName = mymodel;
		
		std::string::size_type findlsr = mymodel.find("lsr");
		std::string::size_type findlaser = mymodel.find("laser");
		std::string::size_type finduhp = mymodel.find("uhp");


		if (findlsr != std::string::npos) { isLSR = true; }
		else if (findlaser != std::string::npos) { isLaser = true; }
		else if (finduhp != std::string::npos) { isUHP = true; }
		else {
			other = true;
		}

	}

	~LinkCamera() {

	}

protected:
	mmind::api::MechEyeDevice device;
	std::string CamIp;
	std::string CamName;
	bool isLSR = false, isLaser = false, isUHP = false, other = false;
};



class TestFunc : public LinkCamera
{
public:

	TestFunc(std::string& testCase, std::string& CameraIp) : LinkCamera(CameraIp) {
		std::cout << testCase << std::endl;
		this->testCase = testCase;
		caseCan = readMyCsv.readCsvTestCase(testCase);
	}
	TestFunc(std::string& CameraIp) : LinkCamera(CameraIp) {}

	
	void setTestCase(std::string testCase) {
		this->testCase = testCase;
		caseCan = readMyCsv.readCsvTestCase(testCase);
	}

	inline void TestsetScan2DExposureMode() {
		std::vector<mmind::api::Scanning2DSettings::Scan2DExposureMode> modelCan;
		modelCan.emplace_back(mmind::api::Scanning2DSettings::Scan2DExposureMode::Timed);
		modelCan.emplace_back(mmind::api::Scanning2DSettings::Scan2DExposureMode::Auto);
		modelCan.emplace_back(mmind::api::Scanning2DSettings::Scan2DExposureMode::HDR);
		modelCan.emplace_back(mmind::api::Scanning2DSettings::Scan2DExposureMode::Flash);

		for (size_t i = 0; i < modelCan.size(); i++) {
			for (size_t j = 0; j < caseCan.size(); j++) {
				mmind::api::Scanning2DSettings::Scan2DExposureMode getvalue;
				if (static_cast<int>(modelCan[i]) == atoi(caseCan[j][1].c_str())) {
					auto errorMsg = newshowError(device.setScan2DExposureMode(modelCan[i]));
					newshowError(device.getScan2DExposureMode(getvalue));
					if (static_cast<int>(getvalue) == atoi(caseCan[j][2].c_str())) {
						std::cout << "TestsetScan2DExposureMode test successfully： " << static_cast<int>(getvalue) << std::endl;
						writeMyCsv.writeResultToCsv(testCase, std::to_string(modelCan[i]), std::to_string(getvalue), "pass", errorMsg);
						continue;
					}
					writeMyCsv.writeResultToCsv(testCase, std::to_string(modelCan[i]), std::to_string(getvalue), "fail", errorMsg);
					std::cout << "TestsetScan2DExposureMode test failure： " << static_cast<int>(modelCan[i]) << std::endl;
				}
			}
		}
	}

	inline void TestsetScan2DExposureMode_LSR() {
		std::vector<mmind::api::Scanning2DSettings::Scan2DExposureMode> modelCan;
		modelCan.emplace_back(mmind::api::Scanning2DSettings::Scan2DExposureMode::Timed);
		modelCan.emplace_back(mmind::api::Scanning2DSettings::Scan2DExposureMode::Auto);
		modelCan.emplace_back(mmind::api::Scanning2DSettings::Scan2DExposureMode::HDR);

		for (size_t i = 0; i < modelCan.size(); i++) {
			for (size_t j = 0; j < caseCan.size(); j++) {
				mmind::api::Scanning2DSettings::Scan2DExposureMode getvalue;
				if (static_cast<int>(modelCan[i]) == atoi(caseCan[j][1].c_str())) {
					auto errorMsg = newshowError(device.setScan2DExposureMode(modelCan[i]));
					newshowError(device.getScan2DExposureMode(getvalue));
					if (static_cast<int>(getvalue) == atoi(caseCan[j][2].c_str())) {
						std::cout << "TestsetScan2DExposureModeLSR test successfully： " << static_cast<int>(getvalue) << std::endl;
						writeMyCsv.writeResultToCsv(testCase, std::to_string(modelCan[i]), std::to_string(getvalue), PASS, errorMsg);
						continue;
					}
					writeMyCsv.writeResultToCsv(testCase, std::to_string(modelCan[i]), std::to_string(getvalue), FAIL, errorMsg);
					std::cout << "TestsetScan2DExposureModeLSR test failure： " << static_cast<int>(modelCan[i]) << std::endl;
				}
			}
		}
	}

	inline void setScan2DExposureTime() {
		for (size_t j = 0; j < caseCan.size(); j++) {
			double setValue = atof(caseCan[j][1].c_str());
			double getValue;
			auto errorMsg = newshowError(device.setScan2DExposureTime(setValue));
			newshowError(device.getScan2DExposureTime(getValue));
			if (std::to_string(atof(caseCan[j][2].c_str())) == std::to_string(getValue)) {
				std::cout << "TestsetScan2DExposureTime test successful" << std::endl;
				writeMyCsv.writeResultToCsv(testCase, std::to_string(setValue), std::to_string(getValue), PASS, errorMsg);
				continue;
			}
			std::cout << "TestsetScan2DExposureTime test failure" << std::endl;
			writeMyCsv.writeResultToCsv(testCase, std::to_string(setValue), std::to_string(getValue), FAIL, errorMsg);
		}
	}

	inline void setScan2DExposureTime_LSR() {
		for (size_t j = 0; j < caseCan.size(); j++) {
			double setValue = atof(caseCan[j][1].c_str());
			double getValue;
			auto errorMsg = newshowError(device.setScan2DExposureTime(setValue));
			newshowError(device.getScan2DExposureTime(getValue));
			if (std::to_string(atof(caseCan[j][2].c_str())) == std::to_string(getValue)) {
				std::cout << "TestsetScan2DExposureTime test successful" << std::endl;
				writeMyCsv.writeResultToCsv(testCase, std::to_string(setValue), std::to_string(getValue), PASS, errorMsg);
				continue;
			}
			std::cout << "TestsetScan2DExposureTime test failure" << std::endl;
			writeMyCsv.writeResultToCsv(testCase, std::to_string(setValue), std::to_string(getValue), FAIL, errorMsg);
		}
		
	}

	inline void setScan2DExposureTime_Laser() {
		for (size_t j = 0; j < caseCan.size(); j++) {
			double setValue = atof(caseCan[j][1].c_str());
			double getValue;
			auto errorMsg = newshowError(device.setScan2DExposureTime(setValue));
			newshowError(device.getScan2DExposureTime(getValue));
			if (std::to_string(atof(caseCan[j][2].c_str())) == std::to_string(getValue)) {
				std::cout << "TestsetScan2DExposureTime test successful" << std::endl;
				writeMyCsv.writeResultToCsv(testCase, std::to_string(setValue), std::to_string(getValue), PASS, errorMsg);
				continue;
			}
			std::cout << "TestsetScan2DExposureTime test failure" << std::endl;
			writeMyCsv.writeResultToCsv(testCase, std::to_string(setValue), std::to_string(getValue), FAIL, errorMsg);
		}

	}

	inline void TestsetScan2DHDRExposureSequence() {
		for (size_t i = 0; i < caseCan.size(); i++) {
			std::string setresult, getidelresult;
			std::istringstream setsequence(caseCan[i][1]), getidealsequence(caseCan[i][2]);
			std::vector<double>setvalue, getidealvalues, getvalue;
			while (setsequence >> setresult) {
				setvalue.push_back(atof(setresult.c_str()));
			}
			//for (auto x : setvalue) { std::cout << "[" << x << "]" << std::endl; }

			while (getidealsequence >> getidelresult) {
				getidealvalues.push_back(atof(getidelresult.c_str()));
			}

			auto errorMsg = newshowError(device.setScan2DHDRExposureSequence(setvalue));
			newshowError(device.getScan2DHDRExposureSequence(getvalue));
			if (tostring(getidealvalues) != tostring(getvalue)) {
				writeMyCsv.writeResultToCsv(testCase, tostring(setvalue), tostring(getvalue), FAIL, errorMsg);
				std::cout << "TestsetScan2DHDRExposureSequence test failure " << std::endl;
				continue;
			}
			writeMyCsv.writeResultToCsv(testCase, tostring(setvalue), tostring(getvalue), PASS, errorMsg);
			std::cout << "TestsetScan2DHDRExposureSequence test successfully " << std::endl;
		}

	}

	inline void TestsetScan2DExpectedGrayValue() {
		for (size_t i = 0; i < caseCan.size(); i++) {
			int getvalue;
			auto errorMsg = newshowError(device.setScan2DExpectedGrayValue(atoi(caseCan[i][1].c_str())));
			newshowError(device.getScan2DExpectedGrayValue(getvalue));
			if (getvalue != atoi(caseCan[i][1].c_str())) {
				std::cout << "TestsetScan2DToneMappingEnable test failure." << std::endl;
				writeMyCsv.writeResultToCsv(testCase, std::to_string(atoi(caseCan[i][1].c_str())), std::to_string(getvalue), "fail", errorMsg);

				continue;
			}
			std::cout << "TestsetScan2DToneMappingEnable test successful." << std::endl;
			writeMyCsv.writeResultToCsv(testCase, std::to_string(atoi(caseCan[i][1].c_str())), std::to_string(getvalue), "pass", errorMsg);
		}

	}

	inline void TestsetScan2DToneMappingEnable() {
		for (size_t i = 0; i < caseCan.size(); i++) {
			bool getvalue;
			auto errorMsg = newshowError(device.setScan2DToneMappingEnable(atoi(caseCan[i][1].c_str())));
			newshowError(device.getScan2DToneMappingEnable(getvalue));
			if (getvalue != atoi(caseCan[i][1].c_str())) {
				std::cout << "TestsetScan2DToneMappingEnable test failure." << std::endl;
				writeMyCsv.writeResultToCsv(testCase, std::to_string(atoi(caseCan[i][1].c_str())), std::to_string(getvalue), "fail", errorMsg);

				continue;
			}
			std::cout << "TestsetScan2DToneMappingEnable test successful." << std::endl;
			writeMyCsv.writeResultToCsv(testCase, std::to_string(atoi(caseCan[i][1].c_str())), std::to_string(getvalue), "pass", errorMsg);
		}

	}

	inline void TestsetScan2DSharpenFactor() {
		for (size_t i = 0; i < caseCan.size(); i++) {
			double getparameter;
			auto errorMsg = newshowError(device.setScan2DSharpenFactor(atof(caseCan[i][1].c_str())));
			newshowError(device.getScan2DSharpenFactor(getparameter));
			if (std::to_string(getparameter) != std::to_string(atof(caseCan[i][2].c_str()))) {
				std::cout << "TestsetScan2DSharpenFactor test failure." << std::endl;
				writeMyCsv.writeResultToCsv(testCase, std::to_string(atof(caseCan[i][1].c_str())), std::to_string(getparameter), FAIL, errorMsg);
				continue;
			}
			std::cout << "TestsetScan2DSharpenFactor test successful." << std::endl;
			writeMyCsv.writeResultToCsv(testCase, std::to_string(atof(caseCan[i][1].c_str())), std::to_string(getparameter), PASS, errorMsg);

		}
	}

	inline void TestsetScan2DROI() {
		for (size_t i = 0; i < caseCan.size(); i++)
		{

			std::istringstream setsequence(caseCan[i][1]), getsequence(caseCan[i][2]);
			std::string setresult, getidealresult;
			std::vector<int> setvalue, getvalue, getroitovalue;

			while (setsequence >> setresult) {
				setvalue.push_back(atoi(setresult.c_str()));
			}
			mmind::api::ROI myRoi(setvalue[0], setvalue[1], setvalue[2], setvalue[3]), getRoi;
			auto errorMsg = newshowError(device.setScan2DROI(myRoi));
			newshowError(device.getScan2DROI(getRoi));
			while (getsequence >> getidealresult) {
				getvalue.push_back(atoi(getidealresult.c_str()));
			}
			getroitovalue.emplace_back(getRoi.x);
			getroitovalue.emplace_back(getRoi.y);
			getroitovalue.emplace_back(getRoi.width);
			getroitovalue.emplace_back(getRoi.height);

			if (getvalue[0] != getRoi.x || getvalue[1] != getRoi.y || getvalue[2] != getRoi.width || getvalue[3] != getRoi.height) {
				std::cout << "TestsetScan2DROI test failure. " << std::endl;
				writeMyCsv.writeResultToCsv(testCase, tostring(setvalue), tostring(getroitovalue), FAIL, errorMsg);
			}
			std::cout << "TestsetScan2DROI test successful. " << std::endl;
			writeMyCsv.writeResultToCsv(testCase, tostring(setvalue), tostring(getroitovalue), PASS, errorMsg);
		}
	}

	inline void TestsetScan3DROI() {
		for (size_t i = 0; i < caseCan.size(); i++)
		{

			std::istringstream setsequence(caseCan[i][1]);
			std::istringstream getsequence(caseCan[i][2]);
			std::string setresult, getidealresult;
			std::vector<int> setvalue, getvalue, getroitovalue;

			while (setsequence >> setresult) {
				setvalue.push_back(atoi(setresult.c_str()));
			}
			mmind::api::ROI myRoi(setvalue[0], setvalue[1], setvalue[2], setvalue[3]), getRoi;
			auto errorMsg = newshowError(device.setScan3DROI(myRoi));
			newshowError(device.getScan3DROI(getRoi));
			while (getsequence >> getidealresult) {
				getvalue.push_back(atoi(getidealresult.c_str()));
			}
			getroitovalue.emplace_back(getRoi.x);
			getroitovalue.emplace_back(getRoi.y);
			getroitovalue.emplace_back(getRoi.width);
			getroitovalue.emplace_back(getRoi.height);
			if (getvalue[0] != getRoi.x || getvalue[1] != getRoi.y || getvalue[2] != getRoi.width || getvalue[3] != getRoi.height) {
				std::cout << "TestsetScan3DROI test failure. " << std::endl;
				writeMyCsv.writeResultToCsv(testCase, tostring(setvalue), tostring(getroitovalue), FAIL, errorMsg);
			}
			std::cout << "TestsetScan3DROI test successful. " << std::endl;
			writeMyCsv.writeResultToCsv(testCase, tostring(setvalue), tostring(getroitovalue), PASS, errorMsg);

		}

	}

	inline void TestsetScan3DExposure() {
		for (size_t i = 0; i < caseCan.size(); i++) {
			std::istringstream setsequence(caseCan[i][1]), getsequence(caseCan[i][2]);
			std::string setresult, getidealresult;
			std::vector<double> setvalue, getvalue;
			std::vector<std::string> getidealvalue, getvaluetostr;

			while (setsequence >> setresult) {
				setvalue.push_back(std::atof(setresult.c_str()));
			}
			auto errorMsg = newshowError(device.setScan3DExposure(setvalue));
			newshowError(device.getScan3DExposure(getvalue));

			while (getsequence >> getidealresult) {
				getidealvalue.push_back(std::to_string(atof(getidealresult.c_str())));
			}
			for (size_t i = 0; i < getvalue.size(); i++) {
				std::cout << std::to_string(getvalue[i]) << " ";
				getvaluetostr.push_back(std::to_string(getvalue[i]));
			}

			if (getidealvalue != getvaluetostr) {
				std::cout << "TestsetScan3DExposure test failure. " << std::endl;
				writeMyCsv.writeResultToCsv(testCase, tostring(setvalue), tostring(getvalue), FAIL, errorMsg);
				continue;
			}
			writeMyCsv.writeResultToCsv(testCase, tostring(setvalue), tostring(getvalue), PASS, errorMsg);
			std::cout << "TestsetScan3DExposure test successful. " << std::endl;

		}

	}

	inline void TestsetScan3DExposure_Lsr_Laser() {
		for (size_t i = 0; i < caseCan.size(); i++) {
			std::istringstream setsequence(caseCan[i][1]), getsequence(caseCan[i][2]);
			std::string setresult, getidealresult;
			std::vector<double> setvalue, getvalue;
			std::vector<std::string> getidealvalue, getvaluetostr;

			while (setsequence >> setresult) {
				setvalue.push_back(std::atof(setresult.c_str()));
			}
			auto errorMsg = newshowError(device.setScan3DExposure(setvalue));
			newshowError(device.getScan3DExposure(getvalue));

			while (getsequence >> getidealresult) {
				getidealvalue.push_back(std::to_string(atof(getidealresult.c_str())));
			}

			// 将get出来的结果变为string类型的vector方便比较
			for (size_t i = 0; i < getvalue.size(); i++) {
				std::cout << std::to_string(getvalue[i]) << " ";
				getvaluetostr.push_back(std::to_string(getvalue[i]));
			}

			if (getidealvalue != getvaluetostr) {
				std::cout << "TestsetScan3DExposureLsrLaser test failure. " << std::endl;
				writeMyCsv.writeResultToCsv(testCase, tostring(setvalue), tostring(getvalue), FAIL, errorMsg);

				continue;
			}
			writeMyCsv.writeResultToCsv(testCase, tostring(setvalue), tostring(getvalue), PASS, errorMsg);
			std::cout << "TestsetScan3DExposureLsrLaser test successful. " << std::endl;
		}
	}

	inline void TestsetScan3DGain() {
		for (size_t i = 0; i < caseCan.size(); i++) {
			double getvalue;
			auto errorMsg = newshowError(device.setScan3DGain(atof(caseCan[i][1].c_str())));
			newshowError(device.getScan3DGain(getvalue));
			if (std::to_string(getvalue) != std::to_string(atof(caseCan[i][2].c_str()))) {
				std::cout << "TestsetScan3DGain test Failure. " << std::endl;
				writeMyCsv.writeResultToCsv(testCase, std::to_string(atof(caseCan[i][1].c_str())), std::to_string(getvalue), FAIL, errorMsg);
				continue;
			}
			std::cout << "TestsetScan3DGain test successful. " << std::endl;
			writeMyCsv.writeResultToCsv(testCase, std::to_string(atof(caseCan[i][1].c_str())), std::to_string(getvalue), PASS, errorMsg);
		}
	}

	inline void TestsetDepthRange() {
		for (size_t i = 0; i < caseCan.size(); i++) {
			std::vector<int> setvalue, getidealvalue, getroitovalue;
			std::string setresult, getidealresult;
			std::istringstream setsequence(caseCan[i][1]), getsequence(caseCan[i][2]);
			while (setsequence >> setresult) {
				setvalue.push_back(atoi(setresult.c_str()));
			}
			mmind::api::DepthRange value(setvalue[0], setvalue[1]), getvalue;
			auto errorMsg = newshowError(device.setDepthRange(value));
			newshowError(device.getDepthRange(getvalue));

			while (getsequence >> getidealresult) {
				getidealvalue.push_back(atoi(getidealresult.c_str()));
			}

			getroitovalue.emplace_back(getvalue.lower);
			getroitovalue.emplace_back(getvalue.upper);
			if (getvalue.lower != getidealvalue[0] || getvalue.upper != getidealvalue[1]) {
				std::cout << "TestsetDepthRange test failure. " << std::endl;
				writeMyCsv.writeResultToCsv(testCase, tostring(setvalue), tostring(getroitovalue), FAIL, errorMsg);
				continue;
			}
			std::cout << "TestsetDepthRange test successful. " << std::endl;
			writeMyCsv.writeResultToCsv(testCase, tostring(setvalue), tostring(getroitovalue), PASS, errorMsg);
		}
	
	}

	inline void TestsetFringeContrastThreshold() {
		for (size_t i = 0; i < caseCan.size(); i++) {
			int getvalue;
			auto errorMsg = newshowError(device.setFringeContrastThreshold(atoi(caseCan[i][1].c_str())));
			newshowError(device.getFringeContrastThreshold(getvalue));
			if (getvalue != atoi(caseCan[i][2].c_str())) {
				std::cout << "TestsetFringeContrastThreshold test falure. " << std::endl;
				writeMyCsv.writeResultToCsv(testCase, std::to_string(atoi(caseCan[i][1].c_str())), std::to_string(getvalue), FAIL, errorMsg);
				continue;
			}
			writeMyCsv.writeResultToCsv(testCase, std::to_string(atoi(caseCan[i][1].c_str())), std::to_string(getvalue),PASS, errorMsg);
			std::cout << "TestsetFringeContrastThreshold test successful. " << std::endl;
		}
	}

	inline void TestsetFringeMinThreshold() {
		for (size_t i = 0; i < caseCan.size(); i++) {
			int getvalue;
			auto errorMsg = newshowError(device.setFringeContrastThreshold(atoi(caseCan[i][1].c_str())));
			newshowError(device.getFringeContrastThreshold(getvalue));
			if (getvalue != atoi(caseCan[i][2].c_str())) {
				writeMyCsv.writeResultToCsv(testCase, std::to_string(atoi(caseCan[i][1].c_str())), std::to_string(getvalue), FAIL, errorMsg);
				std::cout << "TestsetFringeMinThreshold test failure. " << std::endl;
				continue;
			}
			std::cout << "TestsetFringeMinThreshold test successful. " << std::endl;
			writeMyCsv.writeResultToCsv(testCase, std::to_string(atoi(caseCan[i][1].c_str())), std::to_string(getvalue), PASS, errorMsg);
		}
	}

	inline void TestsetCloudOutlierFilterMode() {
		std::vector<mmind::api::PointCloudProcessingSettings::CloudOutlierFilterMode> modelCan;
		modelCan.push_back(mmind::api::PointCloudProcessingSettings::CloudOutlierFilterMode::Off);
		modelCan.push_back(mmind::api::PointCloudProcessingSettings::CloudOutlierFilterMode::Normal);
		modelCan.push_back(mmind::api::PointCloudProcessingSettings::CloudOutlierFilterMode::Weak);

		for (size_t i = 0; i < modelCan.size(); i++) {
			for (size_t j = 0; j < caseCan.size(); j++) {
				mmind::api::PointCloudProcessingSettings::CloudOutlierFilterMode getvalue;
				if (static_cast<int>(modelCan[i]) == atoi(caseCan[j][1].c_str())) {
					auto errorMsg = newshowError(device.setCloudOutlierFilterMode(modelCan[i]));
					newshowError(device.getCloudOutlierFilterMode(getvalue));
					if (static_cast<int>(getvalue) == atoi(caseCan[j][2].c_str())) {
						std::cout << " TestsetCloudOutlierFilterMode test successful. " << static_cast<int>(getvalue) << std::endl;
						writeMyCsv.writeResultToCsv(testCase, std::to_string(static_cast<int>(modelCan[i])), std::to_string(static_cast<int>(getvalue)), PASS, errorMsg);
						continue;
					}
					writeMyCsv.writeResultToCsv(testCase, std::to_string(static_cast<int>(modelCan[i])), std::to_string(static_cast<int>(getvalue)), FAIL, errorMsg);
					std::cout << " TestsetCloudOutlierFilterMode test failure. " << static_cast<int>(modelCan[i]) << std::endl;
				}
			}
		}
	}

	inline void TestsetCloudSmoothMode() {
		std::vector<mmind::api::PointCloudProcessingSettings::CloudSmoothMode> modelCan;
		modelCan.push_back(mmind::api::PointCloudProcessingSettings::CloudSmoothMode::Off);
		modelCan.push_back(mmind::api::PointCloudProcessingSettings::CloudSmoothMode::Normal);
		modelCan.push_back(mmind::api::PointCloudProcessingSettings::CloudSmoothMode::Weak);
		modelCan.push_back(mmind::api::PointCloudProcessingSettings::CloudSmoothMode::Strong);

		for (size_t i = 0; i < modelCan.size(); i++) {
			for (size_t j = 0; j < caseCan.size(); j++) {
				mmind::api::PointCloudProcessingSettings::CloudSmoothMode getvalue;
				if (static_cast<int>(modelCan[i]) == atoi(caseCan[j][1].c_str())) {
					auto errorMsg = newshowError(device.setCloudSmoothMode(modelCan[i]));
					newshowError(device.getCloudSmoothMode(getvalue));
					if (static_cast<int>(getvalue) == atoi(caseCan[j][2].c_str())) {
						std::cout << "set Cloud Smooth Mode test successful. " << static_cast<int>(getvalue) << std::endl;
						writeMyCsv.writeResultToCsv(testCase, std::to_string(static_cast<int>(modelCan[i])), std::to_string(static_cast<int>(getvalue)), PASS, errorMsg);
						continue;
					}
					writeMyCsv.writeResultToCsv(testCase, std::to_string(static_cast<int>(modelCan[i])), std::to_string(static_cast<int>(getvalue)), FAIL, errorMsg);
					std::cout << "set Cloud Smooth Mode test failure. " << static_cast<int>(modelCan[i]) << std::endl;
				}
			}
		}
	}

	inline void TestsetLaserSettings_FringeCodingMode() {
		std::vector<mmind::api::LaserSettings::LaserFringeCodingMode> modelCan;
		modelCan.push_back(mmind::api::LaserSettings::LaserFringeCodingMode::Fast);
		modelCan.push_back(mmind::api::LaserSettings::LaserFringeCodingMode::Accurate);
		mmind::api::LaserSettings getLsr;
		for (size_t i = 0; i < caseCan.size(); i++)
		{
			showError(device.getLaserSettings(getLsr));
			getLsr.FringeCodingMode = modelCan[std::atoi(caseCan[i][1].c_str())];
			auto errorMsg = newshowError(device.setLaserSettings(getLsr));
			newshowError(device.getLaserSettings(getLsr));
			if (getLsr.FringeCodingMode != std::atoi(caseCan[i][2].c_str())) {
				std::cout << "TestsetLaserSettings_FringeCodingMode test failure. " << std::endl;
				writeMyCsv.writeResultToCsv(testCase, std::to_string(static_cast<int>(modelCan[std::atoi(caseCan[i][1].c_str())])), std::to_string(static_cast<int>(getLsr.FringeCodingMode)), FAIL, errorMsg);
				continue;
			}
			writeMyCsv.writeResultToCsv(testCase, std::to_string(static_cast<int>(modelCan[std::atoi(caseCan[i][1].c_str())])), std::to_string(static_cast<int>(getLsr.FringeCodingMode)), PASS, errorMsg);
			std::cout << "TestsetLaserSettings_FringeCodingMode test successful. " << std::endl;
		}
	}

	inline void TestsetLaserSettings_FramePartitionCount() {
		mmind::api::LaserSettings getLsr;
		for (size_t i = 0; i < caseCan.size(); i++)
		{
			showError(device.getLaserSettings(getLsr));
			getLsr.FramePartitionCount = std::atoi(caseCan[i][1].c_str());
			auto errorMsg = newshowError(device.setLaserSettings(getLsr));
			newshowError(device.getLaserSettings(getLsr));
			if (getLsr.FramePartitionCount != std::atoi(caseCan[i][2].c_str())) {
				std::cout << "TestsetLaserSettings_FramePartitionCount test failure. " << std::endl;
				writeMyCsv.writeResultToCsv(testCase, std::to_string(std::atoi(caseCan[i][1].c_str())), std::to_string(getLsr.FramePartitionCount), FAIL, errorMsg);

				continue;
			}
			std::cout << "TestsetLaserSettings_FramePartitionCount test successful. " << std::endl;
			writeMyCsv.writeResultToCsv(testCase, std::to_string(std::atoi(caseCan[i][1].c_str())), std::to_string(getLsr.FramePartitionCount), PASS, errorMsg);

		}
	}

	inline void TestsetLaserSettings_FrameRangeStart_FrameRangeEnd() {
		for (size_t i = 0; i < caseCan.size(); i++) {
			std::string setresult, getidealresult;
			std::istringstream setsequence(caseCan[i][1]), getidealsequence(caseCan[i][2]);
			std::vector<int> setvalue, getidealvalue, getroitovalue;
			while (setsequence >> setresult) {
				setvalue.push_back(std::atoi(setresult.c_str()));
			}
			mmind::api::LaserSettings getLsr;
			showError(device.getLaserSettings(getLsr));
			getLsr.FrameRangeStart = setvalue[0];
			getLsr.FrameRangeEnd = setvalue[1];
			std::cout << getLsr.FrameRangeStart << " " << getLsr.FrameRangeEnd << std::endl;

			auto errorMsg = newshowError(device.setLaserSettings(getLsr));
			newshowError(device.getLaserSettings(getLsr));
			while (getidealsequence >> getidealresult) {
				getidealvalue.push_back(std::atoi(getidealresult.c_str()));
			}
			getroitovalue.emplace_back(getLsr.FrameRangeStart);
			getroitovalue.emplace_back(getLsr.FrameRangeEnd);
			if (getLsr.FrameRangeStart != getidealvalue[0] || getLsr.FrameRangeEnd != getidealvalue[1]) {
				std::cout << "TestsetLaserSettings_FrameRangeStart_FrameRangeEnd test failure. " << std::endl;
				writeMyCsv.writeResultToCsv(testCase, tostring(setvalue), tostring(getroitovalue), FAIL, errorMsg);

				continue;
			}
			std::cout << "TestsetLaserSettings_FrameRangeStart_FrameRangeEnd test successful. " << std::endl;
			writeMyCsv.writeResultToCsv(testCase, tostring(setvalue), tostring(getroitovalue), PASS, errorMsg);
		}
	}

	inline void TestsetLaserSettings_PowerLevel() {
		mmind::api::LaserSettings getLsr;
		for (size_t i = 0; i < caseCan.size(); i++)
		{
			newshowError(device.getLaserSettings(getLsr));
			getLsr.PowerLevel = std::atoi(caseCan[i][1].c_str());
			auto errorMsg = newshowError(device.setLaserSettings(getLsr));
			newshowError(device.getLaserSettings(getLsr));
			if (getLsr.PowerLevel != std::atoi(caseCan[i][2].c_str())) {
				std::cout << getLsr.PowerLevel << " TestsetLaserSettings_PowerLevel test failure " << std::atoi(caseCan[i][2].c_str()) << std::endl;
				writeMyCsv.writeResultToCsv(testCase, std::to_string(std::atoi(caseCan[i][1].c_str())), std::to_string(getLsr.PowerLevel), FAIL, errorMsg);

				continue;
			}
			std::cout << "TestsetLaserSettings_PowerLevel test successful" << std::endl;
			writeMyCsv.writeResultToCsv(testCase, std::to_string(std::atoi(caseCan[i][1].c_str())), std::to_string(getLsr.PowerLevel), PASS, errorMsg);

		}
	}

	inline void TestsetUhpCaptureMode() {
		std::vector<mmind::api::UhpSettings::UhpCaptureMode> modelCan;
		modelCan.push_back(mmind::api::UhpSettings::UhpCaptureMode::Camera1);
		modelCan.push_back(mmind::api::UhpSettings::UhpCaptureMode::Camera2);
		modelCan.push_back(mmind::api::UhpSettings::UhpCaptureMode::Merge);

		for (size_t i = 0; i < modelCan.size(); i++) {
			for (size_t j = 0; j < caseCan.size(); j++) {
				mmind::api::UhpSettings::UhpCaptureMode getvalue;
				if (static_cast<int>(modelCan[i]) == atoi(caseCan[j][1].c_str())) {
					auto errorMsg = newshowError(device.setUhpCaptureMode(modelCan[i]));
					newshowError(device.getUhpCaptureMode(getvalue));
					if (static_cast<int>(getvalue) == atoi(caseCan[j][2].c_str())) {
						std::cout << "TestsetUhpCaptureMode test successful. " << static_cast<int>(getvalue) << std::endl;
						writeMyCsv.writeResultToCsv(testCase, std::to_string(static_cast<int>(modelCan[i])), std::to_string(static_cast<int>(getvalue)), PASS, errorMsg);
						continue;
					}
					writeMyCsv.writeResultToCsv(testCase, std::to_string(static_cast<int>(modelCan[i])), std::to_string(static_cast<int>(getvalue)), FAIL, errorMsg);
					std::cout << "TestsetUhpCaptureMode test failure. " << static_cast<int>(modelCan[i]) << std::endl;
				}
			}
		}
	}

	inline void TestsetUhpFringeCodingMode() {
		std::vector<mmind::api::UhpSettings::UhpFringeCodingMode> modelCan;
		modelCan.push_back(mmind::api::UhpSettings::UhpFringeCodingMode::Fast);
		modelCan.push_back(mmind::api::UhpSettings::UhpFringeCodingMode::Accurate);

		for (size_t i = 0; i < modelCan.size(); i++) {
			for (size_t j = 0; j < caseCan.size(); j++) {
				mmind::api::UhpSettings::UhpFringeCodingMode getvalue;
				if (static_cast<int>(modelCan[i]) == atoi(caseCan[j][1].c_str())) {
					auto errorMsg = newshowError(device.setUhpFringeCodingMode(modelCan[i]));
					showError(device.getUhpFringeCodingMode(getvalue));
					if (static_cast<int>(getvalue) == atoi(caseCan[j][2].c_str())) {
						std::cout << "TestsetUhpFringeCodingMode test successful. " << static_cast<int>(getvalue) << std::endl;

						writeMyCsv.writeResultToCsv(testCase, std::to_string(static_cast<int>(modelCan[i])), std::to_string(static_cast<int>(getvalue)), PASS, errorMsg);
						continue;
					}
					writeMyCsv.writeResultToCsv(testCase, std::to_string(static_cast<int>(modelCan[i])), std::to_string(static_cast<int>(getvalue)), FAIL, errorMsg);
					std::cout << "TestsetUhpFringeCodingMode test successful. " << static_cast<int>(modelCan[i]) << std::endl;

				}
			}
		}
	}

	inline void TestsetUhpSettings() {
		std::map<int, mmind::api::UhpSettings::UhpCaptureMode> CaptureMode;
		std::map<int, mmind::api::UhpSettings::UhpFringeCodingMode> FringeCodingMode;
		CaptureMode[0] = mmind::api::UhpSettings::UhpCaptureMode::Camera1;
		CaptureMode[1] = mmind::api::UhpSettings::UhpCaptureMode::Camera2;
		CaptureMode[2] = mmind::api::UhpSettings::UhpCaptureMode::Merge;
		FringeCodingMode[0] = mmind::api::UhpSettings::UhpFringeCodingMode::Fast;
		FringeCodingMode[1] = mmind::api::UhpSettings::UhpFringeCodingMode::Accurate;

		for (size_t i = 0; i < caseCan.size(); i++) {
			std::string setresult, getidealresult;
			std::istringstream setsequence(caseCan[i][1]), getidealsequence(caseCan[i][2]);
			std::vector<int> setvalue, getidealvalue, getroitovalue;
			while (setsequence >> setresult) {
				setvalue.push_back(std::atoi(setresult.c_str()));
			}
			while (getidealsequence >> getidealresult) {
				getidealvalue.push_back(std::atoi(getidealresult.c_str()));
			}

			mmind::api::UhpSettings getUhp;
			newshowError(device.getUhpSettings(getUhp));
			getUhp.CaptureMode = CaptureMode[setvalue[0]];
			getUhp.FringeCodingMode = FringeCodingMode[setvalue[1]];
			auto errorMsg = newshowError(device.setUhpSettings(getUhp));
			newshowError(device.getUhpSettings(getUhp));

			getroitovalue.emplace_back(static_cast<int>(getUhp.CaptureMode));
			getroitovalue.emplace_back(static_cast<int>(getUhp.FringeCodingMode));
			if (static_cast<int>(getUhp.CaptureMode) != getidealvalue[0] || static_cast<int>(getUhp.FringeCodingMode) != getidealvalue[1]) {
				writeMyCsv.writeResultToCsv(testCase, tostring(setvalue), tostring(getroitovalue), FAIL, errorMsg);
				std::cout << "TestsetUhpSettings test failure. " << std::endl;

				continue;
			}
			std::cout << "TestsetUhpSettings test successful. " << std::endl;
			writeMyCsv.writeResultToCsv(testCase, tostring(setvalue), tostring(getroitovalue), PASS, errorMsg);

		}
	
	}


	~TestFunc() {
		device.disconnect();
		std::cout << "Disconnected from the Mech-Eye device successfully." << std::endl;

	}

protected:
	readCsv readMyCsv;
	writeCsv writeMyCsv;
	std::vector<std::vector<std::string>> caseCan;
	std::string testCase;
};


class myTest : public TestFunc
{
public:
	myTest(std::string& testCase, std::string& CameraIp):TestFunc(testCase, CameraIp) { };
	myTest(std::string& CameraIp) :TestFunc(CameraIp) { };

	inline void _generalTestParameter() {   //13
		setTestCase("setScan2DHDRExposureSequence");
		TestsetScan2DHDRExposureSequence();

		setTestCase("setScan2DExpectedGrayValue");
		TestsetScan2DExpectedGrayValue();

		setTestCase("setScan2DToneMappingEnable");
		TestsetScan2DToneMappingEnable();

		setTestCase("setScan2DSharpenFactor");
		TestsetScan2DSharpenFactor();

		setTestCase("setScan2DROI");
		TestsetScan2DROI();

		setTestCase("setScan3DROI");
		TestsetScan3DROI();

		setTestCase("setScan3DGain");
		TestsetScan3DGain();

		setTestCase("setDepthRange");
		TestsetDepthRange();

		setTestCase("setFringeContrastThreshold");
		TestsetFringeContrastThreshold();

		setTestCase("setFringeMinThreshold");
		TestsetFringeMinThreshold();

		setTestCase("setCloudOutlierFilterMode");
		TestsetCloudOutlierFilterMode();

		setTestCase("setCloudSmoothMode");
		TestsetCloudSmoothMode();
	}

	inline void _UHPTestParameter() {   // 3
		setTestCase("setUhpCaptureMode(UHP)");
		TestsetUhpCaptureMode();

		setTestCase("setUhpFringeCodingMode(UHP)");
		TestsetUhpFringeCodingMode();

		setTestCase("UhpSettings(UHP)");
		TestsetUhpSettings();
	}

	inline void _Laser_LSR_TestParameter() {  // 5 

		setTestCase("setLaserSettings_FringeCodingMode(LSR_Laser)");
		TestsetLaserSettings_FringeCodingMode();

		setTestCase("setLaserSettings_FramePartitionCount(LSR_Laser)");
		TestsetLaserSettings_FramePartitionCount();

		setTestCase("setLaserSettings_FrameRangeStart_FrameRangeEnd(LSR_Laser)");
		TestsetLaserSettings_FrameRangeStart_FrameRangeEnd();

		setTestCase("setLaserSettings_PowerLevel(LSR_Laser)");
		TestsetLaserSettings_PowerLevel();

		setTestCase("setScan3DExposure(LSR_Laser)");
		TestsetScan3DExposure_Lsr_Laser();
	}
	
	inline void runParameter() {

		if (isLaser) {
			_generalTestParameter();
			_Laser_LSR_TestParameter();

			setTestCase("setScan2DExposureMode(Laser)");
			TestsetScan2DExposureMode();

			setTestCase("setScan2DExposureTime(Laser)");
			setScan2DExposureTime_Laser();

		}else
			if (isLSR){
				_generalTestParameter();
				_Laser_LSR_TestParameter();

				setTestCase("setScan2DExposureTime(LSR)");
				setScan2DExposureTime_LSR();

				setTestCase("setScan2DExposureMode(LSR)");
				TestsetScan2DExposureMode_LSR();

			}else
				if (isUHP){
					_generalTestParameter();
					_UHPTestParameter();
					setTestCase("setScan2DExposureTime");
					setScan2DExposureTime();

					setTestCase("setScan2DExposureMode");
					TestsetScan2DExposureMode();
				}
				else 
					if (other){
						_generalTestParameter();
						setTestCase("setScan2DExposureTime");
						setScan2DExposureTime();

						setTestCase("setScan2DExposureMode");
						TestsetScan2DExposureMode();
				}
	}


	~myTest(){
		std::cout << isLaser << isLSR << isUHP << other << "***************" << std::endl;
	}


};
