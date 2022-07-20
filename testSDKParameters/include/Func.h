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

/*
template<typename T>
inline std::string tostring(std::vector<T>& param) {
	std::string p = "";
	for (auto x : param) {
		p = p + std::to_string(x) + " ";
	}
	return p;
}


inline void TestScan2DExposureMode(std::vector<std::vector<std::string>>& mymodel, mmind::api::MechEyeDevice& device, writeCsv& write, std::string& testCast) {

	std::vector<mmind::api::Scanning2DSettings::Scan2DExposureMode> modelCan;
	modelCan.push_back(mmind::api::Scanning2DSettings::Scan2DExposureMode::Timed);
	modelCan.push_back(mmind::api::Scanning2DSettings::Scan2DExposureMode::Auto);
	modelCan.push_back(mmind::api::Scanning2DSettings::Scan2DExposureMode::HDR);
	modelCan.push_back(mmind::api::Scanning2DSettings::Scan2DExposureMode::Flash);

	for (size_t i = 0; i < modelCan.size(); i++) {
		for (size_t j = 0; j < mymodel.size(); j++) {
			mmind::api::Scanning2DSettings::Scan2DExposureMode getvalue;
			if (static_cast<int>(modelCan[i]) == atoi(mymodel[j][1].c_str())) {
				showError(device.setScan2DExposureMode(modelCan[i]));
				showError(device.getScan2DExposureMode(getvalue));
				if (static_cast<int>(getvalue) == atoi(mymodel[j][2].c_str())) {
					std::cout << "The 2D exposure mode was set successfully： " << static_cast<int>(getvalue) << std::endl;
					write.writeResultToCsv(testCast, std::to_string(modelCan[i]), std::to_string(getvalue), "pass");
					continue;
				}
				write.writeResultToCsv(testCast, std::to_string(modelCan[i]), std::to_string(getvalue), "fail");
				std::cout << "Failed to set 2D exposure mode： " << static_cast<int>(modelCan[i]) << std::endl;
			}
		}
	}
}

inline void TestScan2DExposureModelsr(std::vector<std::vector<std::string>>& mymodel, mmind::api::MechEyeDevice& device, writeCsv& write, std::string& testCast) {
	std::vector<mmind::api::Scanning2DSettings::Scan2DExposureMode> modelCan;
	modelCan.push_back(mmind::api::Scanning2DSettings::Scan2DExposureMode::Timed);
	modelCan.push_back(mmind::api::Scanning2DSettings::Scan2DExposureMode::Auto);
	modelCan.push_back(mmind::api::Scanning2DSettings::Scan2DExposureMode::HDR);

	for (size_t i = 0; i < modelCan.size(); i++) {
		for (size_t j = 0; j < mymodel.size(); j++) {
			mmind::api::Scanning2DSettings::Scan2DExposureMode getvalue;
			if (static_cast<int>(modelCan[i]) == atoi(mymodel[j][1].c_str())) {
				showError(device.setScan2DExposureMode(modelCan[i]));
				showError(device.getScan2DExposureMode(getvalue));
				if (static_cast<int>(getvalue) == atoi(mymodel[j][2].c_str())) {
					std::cout << "The 2D exposure mode about lsr was set successfully: " << static_cast<int>(getvalue) << std::endl;
					write.writeResultToCsv(testCast, std::to_string(modelCan[i]), std::to_string(getvalue), "pass");
					continue;
				}
				write.writeResultToCsv(testCast, std::to_string(modelCan[i]), std::to_string(getvalue), "fail");
				std::cout << "Failed to set 2D exposure  mode about lsr: " << static_cast<int>(modelCan[i]) << std::endl;
			}
		}
	}

}

inline void TestsetScan2DExposureTime(std::vector<std::vector<std::string>>& mytime, mmind::api::MechEyeDevice& device, writeCsv& write, std::string& testCast) {
	for (size_t j = 0; j < mytime.size(); j++) {
		double setValue = atof(mytime[j][1].c_str());
		double getValue;
		showError(device.setScan2DExposureTime(setValue));
		showError(device.getScan2DExposureTime(getValue));

		// csv中预期的set参数与get出来的参数相等 [这里get出来好像是0.0999999999这样的，导致无法判断，改用字符串判断]
		if (std::to_string(atof(mytime[j][2].c_str())) == std::to_string(getValue)) {
			std::cout << "TestsetScan2DExposureTime successfully: set=" << std::to_string(setValue) << " get=" << std::to_string(getValue) << std::endl;

			write.writeResultToCsv(testCast, std::to_string(setValue), std::to_string(getValue), "pass");
			continue;
		}
		std::cout << "Failed to set 2D exposure time: set = " << std::to_string(setValue) << " get = " << std::to_string(getValue) << std::endl;

		write.writeResultToCsv(testCast, std::to_string(setValue), std::to_string(getValue), "fail");
	}
}

inline void TestsetScan2DExposureTimeLsr(std::vector<std::vector<std::string>>& mytime, mmind::api::MechEyeDevice& device, writeCsv& write, std::string& testCast) {
	for (size_t j = 0; j < mytime.size(); j++) {
		double setValue = atof(mytime[j][1].c_str());
		double getValue;
		showError(device.setScan2DExposureTime(setValue));
		showError(device.getScan2DExposureTime(getValue));

		// csv中预期的set参数与get出来的参数相等 [这里get出来好像是0.0999999999这样的，导致无法判断，改用字符串判断]
		if (std::to_string(atof(mytime[j][2].c_str())) == std::to_string(getValue)) {
			std::cout << "The 2D exposure mode was set successfully: set = " << std::to_string(setValue) << " get = " << std::to_string(getValue) << std::endl;
			write.writeResultToCsv(testCast, std::to_string(setValue), std::to_string(getValue), "pass");
			continue;
		}
		std::cout << "Failed to set 2D exposure time: set= " << std::to_string(setValue) << " get = " << std::to_string(getValue) << std::endl;
		write.writeResultToCsv(testCast, std::to_string(setValue), std::to_string(getValue), "fail");
	}
}

inline void TestsetScan2DHDRExposureSequence(std::vector<std::vector<std::string>>& mysequence, mmind::api::MechEyeDevice& device, writeCsv& write, std::string& testCast) {
	for (size_t i = 0; i < mysequence.size(); i++) {
		std::string setresult, getidelresult;
		std::istringstream setsequence(mysequence[i][1]), getidealsequence(mysequence[i][2]);
		std::vector<double>setvalue, getidealvalues, getvalue;
		while (setsequence >> setresult) {
			//std::cout << result << std::endl;
			setvalue.push_back(atof(setresult.c_str()));
		}
		for (auto x : setvalue) { std::cout << "[" << x << "]" << std::endl; }

		// 读取get ideal值
		while (getidealsequence >> getidelresult) {
			getidealvalues.push_back(atof(getidelresult.c_str()));
		}

		showError(device.setScan2DHDRExposureSequence(setvalue));
		showError(device.getScan2DHDRExposureSequence(getvalue));
		// 判断get出来的vector 和 csv读出来的vector是否相等
		if (tostring(getidealvalues) != tostring(getvalue)) {
			write.writeResultToCsv(testCast, tostring(setvalue), tostring(getvalue), "fail");

			std::cout << "Failed to set Scan2DHDRExposureSequence" << std::endl;
			continue;
		}
		write.writeResultToCsv(testCast, tostring(setvalue), tostring(getvalue), "pass");
		std::cout << "Scan2DHDRExposureSequence set successfully" << std::endl;
	}
}

inline void TestsetScan2DExpectedGrayValue(std::vector<std::vector<std::string>>& mygrayvalue, mmind::api::MechEyeDevice& device, writeCsv& write, std::string& testCast) {
	for (size_t i = 0; i < mygrayvalue.size(); i++) {
		int getvalue;
		showError(device.setScan2DExpectedGrayValue(atoi(mygrayvalue[i][1].c_str())));
		showError(device.getScan2DExpectedGrayValue(getvalue));
		if (getvalue != atoi(mygrayvalue[i][2].c_str())) {
			write.writeResultToCsv(testCast, std::to_string(atoi(mygrayvalue[i][1].c_str())), std::to_string(getvalue), "fail");

			std::cout << "TestsetScan2DExpectedGrayValue test failure." << std::endl;
			continue;
		}
		std::cout << "TestsetScan2DExpectedGrayValue test successful." << std::endl;
		write.writeResultToCsv(testCast, std::to_string(atoi(mygrayvalue[i][1].c_str())), std::to_string(getvalue), "pass");

	}
}

inline void TestsetScan2DToneMappingEnable(std::vector<std::vector<std::string>>& myenable, mmind::api::MechEyeDevice& device, writeCsv& write, std::string& testCast) {
	for (size_t i = 0; i < myenable.size(); i++) {
		bool getvalue;
		showError(device.setScan2DToneMappingEnable(atoi(myenable[i][1].c_str())));
		showError(device.getScan2DToneMappingEnable(getvalue));
		if (getvalue != atoi(myenable[i][1].c_str())) {
			std::cout << "TestsetScan2DToneMappingEnable test failure." << std::endl;
			write.writeResultToCsv(testCast, std::to_string(atoi(myenable[i][1].c_str())), std::to_string(getvalue), "fail");

			continue;
		}
		std::cout << "TestsetScan2DToneMappingEnable test successful." << std::endl;
		write.writeResultToCsv(testCast, std::to_string(atoi(myenable[i][1].c_str())), std::to_string(getvalue), "pass");
	}
}

inline void TestsetScan2DSharpenFactor(std::vector<std::vector<std::string>>& myparameters, mmind::api::MechEyeDevice& device, writeCsv& write, std::string& testCast) {
	for (size_t i = 0; i < myparameters.size(); i++) {
		double getparameter;
		showError(device.setScan2DSharpenFactor(atof(myparameters[i][1].c_str())));
		showError(device.getScan2DSharpenFactor(getparameter));
		if (std::to_string(getparameter) != std::to_string(atof(myparameters[i][2].c_str()))) {
			std::cout << "set Scan 2D Sharpen Factor test failure. " << std::endl;
			write.writeResultToCsv(testCast, std::to_string(atof(myparameters[i][1].c_str())), std::to_string(getparameter), "fail");
			continue;
		}
		std::cout << "set Scan 2D Sharpen Factor test successful. " << std::endl;

		write.writeResultToCsv(testCast, std::to_string(atof(myparameters[i][1].c_str())), std::to_string(getparameter), "pass");

	}

}

// 需要增加拍照图片尺寸边界值的测试(不同相机分辨率不同)
inline void TestsetScan2DROI(std::vector<std::vector<std::string>>& myparameters, mmind::api::MechEyeDevice& device, writeCsv& write, std::string& testCast) {
	for (size_t i = 0; i < myparameters.size(); i++)
	{

		std::istringstream setsequence(myparameters[i][1]), getsequence(myparameters[i][2]);
		std::string setresult, getidealresult;
		std::vector<int> setvalue, getvalue, getroitovalue;

		while (setsequence >> setresult) {
			setvalue.push_back(atoi(setresult.c_str()));
		}
		mmind::api::ROI myRoi(setvalue[0], setvalue[1], setvalue[2], setvalue[3]), getRoi;
		showError(device.setScan2DROI(myRoi));
		showError(device.getScan2DROI(getRoi));
		while (getsequence >> getidealresult) {
			getvalue.push_back(atoi(getidealresult.c_str()));
		}
		getroitovalue.emplace_back(getRoi.x);
		getroitovalue.emplace_back(getRoi.y);
		getroitovalue.emplace_back(getRoi.width);
		getroitovalue.emplace_back(getRoi.height);

		if (getvalue[0] != getRoi.x || getvalue[1] != getRoi.y || getvalue[2] != getRoi.width || getvalue[3] != getRoi.height) {
			std::cout << "set Scan 2D ROI test failure. " << std::endl;
			write.writeResultToCsv(testCast, tostring(setvalue), tostring(getroitovalue), "fail");
		}
		std::cout << "set Scan 2D ROI test successful. " << std::endl;
		write.writeResultToCsv(testCast, tostring(setvalue), tostring(getroitovalue), "pass");
	}

}

// 需要增加拍照图片尺寸边界值的测试(不同相机分辨率不同)
inline void TestsetScan3DROI(std::vector<std::vector<std::string>>& myparameters, mmind::api::MechEyeDevice& device, writeCsv& write, std::string& testCast) {
	for (size_t i = 0; i < myparameters.size(); i++)
	{

		std::istringstream setsequence(myparameters[i][1]);
		std::istringstream getsequence(myparameters[i][2]);
		std::string setresult, getidealresult;
		std::vector<int> setvalue, getvalue, getroitovalue;

		while (setsequence >> setresult) {
			setvalue.push_back(atoi(setresult.c_str()));
		}
		mmind::api::ROI myRoi(setvalue[0], setvalue[1], setvalue[2], setvalue[3]), getRoi;
		showError(device.setScan3DROI(myRoi));
		showError(device.getScan3DROI(getRoi));
		while (getsequence >> getidealresult) {
			getvalue.push_back(atoi(getidealresult.c_str()));
		}
		getroitovalue.emplace_back(getRoi.x);
		getroitovalue.emplace_back(getRoi.y);
		getroitovalue.emplace_back(getRoi.width);
		getroitovalue.emplace_back(getRoi.height);
		if (getvalue[0] != getRoi.x || getvalue[1] != getRoi.y || getvalue[2] != getRoi.width || getvalue[3] != getRoi.height) {
			std::cout << "set Scan 3D ROI test failure. " << std::endl;
			write.writeResultToCsv(testCast, tostring(setvalue), tostring(getroitovalue), "fail");
		}
		std::cout << "set Scan 3D ROI test successful. " << std::endl;
		write.writeResultToCsv(testCast, tostring(setvalue), tostring(getroitovalue), "pass");

	}

}

inline void TestsetScan3DExposure(std::vector<std::vector<std::string>>& myparameters, mmind::api::MechEyeDevice& device, writeCsv& write, std::string& testCast) {
	for (size_t i = 0; i < myparameters.size(); i++) {
		std::istringstream setsequence(myparameters[i][1]), getsequence(myparameters[i][2]);
		std::string setresult, getidealresult;
		std::vector<double> setvalue, getvalue;
		std::vector<std::string> getidealvalue, getvaluetostr;

		while (setsequence >> setresult) {
			setvalue.push_back(std::atof(setresult.c_str()));
		}
		showError(device.setScan3DExposure(setvalue));
		showError(device.getScan3DExposure(getvalue));

		while (getsequence >> getidealresult) {
			getidealvalue.push_back(std::to_string(atof(getidealresult.c_str())));
		}

		// 将get出来的结果变为string类型的vector方便比较
		for (size_t i = 0; i < getvalue.size(); i++) {
			std::cout << std::to_string(getvalue[i]) << " ";
			getvaluetostr.push_back(std::to_string(getvalue[i]));
		}

		if (getidealvalue != getvaluetostr) {
			std::cout << "TestsetScan3DExposure test failure. " << std::endl;

			write.writeResultToCsv(testCast, tostring(setvalue), tostring(getvalue), "fail");

			for (size_t i = 0; i < getvaluetostr.size(); i++)
			{
				std::cout << getvalue[i] << "--" << getidealvalue[i] << std::endl;
			}
			continue;
		}
		write.writeResultToCsv(testCast, tostring(setvalue), tostring(getvalue), "pass");
		std::cout << "TestsetScan3DExposure test successful. " << std::endl;

	}

}

inline void TestsetScan3DExposureLsrLaser(std::vector<std::vector<std::string>>& myparameters, mmind::api::MechEyeDevice& device, writeCsv& write, std::string& testCast) {
	for (size_t i = 0; i < myparameters.size(); i++) {
		std::istringstream setsequence(myparameters[i][1]), getsequence(myparameters[i][2]);
		std::string setresult, getidealresult;
		std::vector<double> setvalue, getvalue;
		std::vector<std::string> getidealvalue, getvaluetostr;

		while (setsequence >> setresult) {
			setvalue.push_back(std::atof(setresult.c_str()));
		}
		showError(device.setScan3DExposure(setvalue));
		showError(device.getScan3DExposure(getvalue));

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
			write.writeResultToCsv(testCast, tostring(setvalue), tostring(getvalue), "fail");

			continue;
		}
		write.writeResultToCsv(testCast, tostring(setvalue), tostring(getvalue), "pass");
		std::cout << "TestsetScan3DExposureLsrLaser test successful. " << std::endl;
	}

}


inline void TestsetScan3DGain(std::vector<std::vector<std::string>>& mygrayvalue, mmind::api::MechEyeDevice& device, writeCsv& write, std::string& testCast) {
	for (size_t i = 0; i < mygrayvalue.size(); i++) {
		double getvalue;
		showError(device.setScan3DGain(atof(mygrayvalue[i][1].c_str())));
		showError(device.getScan3DGain(getvalue));
		if (std::to_string(getvalue) != std::to_string(atof(mygrayvalue[i][2].c_str()))) {

			//std::cout << std::to_string(getvalue) << "-不相等-" << std::to_string(atof(mygrayvalue[i][2].c_str())) << std::endl;
			std::cout << "TestsetScan3DGain test Failure. " << std::endl;

			write.writeResultToCsv(testCast, std::to_string(atof(mygrayvalue[i][1].c_str())), std::to_string(getvalue), "fail");
			continue;
		}
		std::cout << "TestsetScan3DGain test successful. " << std::endl;
		write.writeResultToCsv(testCast, std::to_string(atof(mygrayvalue[i][1].c_str())), std::to_string(getvalue), "pass");

	}
}

inline void TestsetDepthRange(std::vector<std::vector<std::string>>& myparameters, mmind::api::MechEyeDevice& device, writeCsv& write, std::string& testCast) {
	for (size_t i = 0; i < myparameters.size(); i++) {
		std::vector<int> setvalue, getidealvalue, getroitovalue;
		std::string setresult, getidealresult;
		std::istringstream setsequence(myparameters[i][1]), getsequence(myparameters[i][2]);
		while (setsequence >> setresult) {
			setvalue.push_back(atoi(setresult.c_str()));
		}
		mmind::api::DepthRange value(setvalue[0], setvalue[1]), getvalue;
		showError(device.setDepthRange(value));
		showError(device.getDepthRange(getvalue));

		while (getsequence >> getidealresult) {
			getidealvalue.push_back(atoi(getidealresult.c_str()));
		}

		getroitovalue.emplace_back(getvalue.lower);
		getroitovalue.emplace_back(getvalue.upper);
		if (getvalue.lower != getidealvalue[0] || getvalue.upper != getidealvalue[1]) {
			std::cout << "TestsetDepthRange test failure. " << std::endl;
			//std::cout << getvalue.lower << " " << getidealvalue[0] << "=不相等=" << getvalue.upper << " " << getidealvalue[1] << std::endl;
			write.writeResultToCsv(testCast, tostring(setvalue), tostring(getroitovalue), "fail");

			continue;
		}
		std::cout << "TestsetDepthRange test successful. " << std::endl;
		write.writeResultToCsv(testCast, tostring(setvalue), tostring(getroitovalue), "pass");
	}

}

inline void TestsetFringeContrastThreshold(std::vector<std::vector<std::string>>& myparameters, mmind::api::MechEyeDevice& device, writeCsv& write, std::string& testCast) {
	for (size_t i = 0; i < myparameters.size(); i++) {
		int getvalue;
		showError(device.setFringeContrastThreshold(atoi(myparameters[i][1].c_str())));
		showError(device.getFringeContrastThreshold(getvalue));
		if (getvalue != atoi(myparameters[i][2].c_str())) {
			//std::cout << getvalue << " 不相等 " << atoi(myparameters[i][2].c_str()) << std::endl;
			std::cout << "TestsetFringeContrastThreshold test falure. " << std::endl;

			write.writeResultToCsv(testCast, std::to_string(atoi(myparameters[i][1].c_str())), std::to_string(getvalue), "fail");
			continue;
		}
		write.writeResultToCsv(testCast, std::to_string(atoi(myparameters[i][1].c_str())), std::to_string(getvalue), "pass");
		std::cout << "TestsetFringeContrastThreshold test successful. " << std::endl;
	}

}

inline void TestsetFringeMinThreshold(std::vector<std::vector<std::string>>& myparameters, mmind::api::MechEyeDevice& device, writeCsv& write, std::string& testCast) {
	for (size_t i = 0; i < myparameters.size(); i++) {
		int getvalue;
		showError(device.setFringeContrastThreshold(atoi(myparameters[i][1].c_str())));
		showError(device.getFringeContrastThreshold(getvalue));
		if (getvalue != atoi(myparameters[i][2].c_str())) {
			write.writeResultToCsv(testCast, std::to_string(atoi(myparameters[i][1].c_str())), std::to_string(getvalue), "fail");
			//std::cout << getvalue << " 不相等 " << atoi(myparameters[i][2].c_str()) << std::endl;
			std::cout << "TestsetFringeMinThreshold test failure. " << std::endl;

			continue;
		}
		//std::cout << "相等" << std::endl;
		std::cout << "TestsetFringeMinThreshold test successful. " << std::endl;

		write.writeResultToCsv(testCast, std::to_string(atoi(myparameters[i][1].c_str())), std::to_string(getvalue), "pass");

	}
}

inline void TestsetCloudOutlierFilterMode(std::vector<std::vector<std::string>>& mymodel, mmind::api::MechEyeDevice& device, writeCsv& write, std::string& testCast) {
	std::vector<mmind::api::PointCloudProcessingSettings::CloudOutlierFilterMode> modelCan;
	modelCan.push_back(mmind::api::PointCloudProcessingSettings::CloudOutlierFilterMode::Off);
	modelCan.push_back(mmind::api::PointCloudProcessingSettings::CloudOutlierFilterMode::Normal);
	modelCan.push_back(mmind::api::PointCloudProcessingSettings::CloudOutlierFilterMode::Weak);

	for (size_t i = 0; i < modelCan.size(); i++) {
		for (size_t j = 0; j < mymodel.size(); j++) {
			mmind::api::PointCloudProcessingSettings::CloudOutlierFilterMode getvalue;
			if (static_cast<int>(modelCan[i]) == atoi(mymodel[j][1].c_str())) {
				showError(device.setCloudOutlierFilterMode(modelCan[i]));
				showError(device.getCloudOutlierFilterMode(getvalue));
				if (static_cast<int>(getvalue) == atoi(mymodel[j][2].c_str())) {
					std::cout << " set Cloud Outlier Filter Mode test successful. " << static_cast<int>(getvalue) << std::endl;
					write.writeResultToCsv(testCast, std::to_string(static_cast<int>(modelCan[i])), std::to_string(static_cast<int>(getvalue)), "pass");
					continue;
				}
				write.writeResultToCsv(testCast, std::to_string(static_cast<int>(modelCan[i])), std::to_string(static_cast<int>(getvalue)), "fail");
				std::cout << " set Cloud Outlier Filter Mode test failure. " << static_cast<int>(modelCan[i]) << std::endl;
			}
		}
	}
}

inline void TestsetCloudSmoothMode(std::vector<std::vector<std::string>>& mymodel, mmind::api::MechEyeDevice& device, writeCsv& write, std::string& testCast) {
	std::vector<mmind::api::PointCloudProcessingSettings::CloudSmoothMode> modelCan;
	modelCan.push_back(mmind::api::PointCloudProcessingSettings::CloudSmoothMode::Off);
	modelCan.push_back(mmind::api::PointCloudProcessingSettings::CloudSmoothMode::Normal);
	modelCan.push_back(mmind::api::PointCloudProcessingSettings::CloudSmoothMode::Weak);
	modelCan.push_back(mmind::api::PointCloudProcessingSettings::CloudSmoothMode::Strong);

	for (size_t i = 0; i < modelCan.size(); i++) {
		for (size_t j = 0; j < mymodel.size(); j++) {
			mmind::api::PointCloudProcessingSettings::CloudSmoothMode getvalue;
			if (static_cast<int>(modelCan[i]) == atoi(mymodel[j][1].c_str())) {
				showError(device.setCloudSmoothMode(modelCan[i]));
				showError(device.getCloudSmoothMode(getvalue));
				if (static_cast<int>(getvalue) == atoi(mymodel[j][2].c_str())) {
					std::cout << "set Cloud Smooth Mode test successful. " << static_cast<int>(getvalue) << std::endl;
					write.writeResultToCsv(testCast, std::to_string(static_cast<int>(modelCan[i])), std::to_string(static_cast<int>(getvalue)), "pass");
					continue;
				}
				write.writeResultToCsv(testCast, std::to_string(static_cast<int>(modelCan[i])), std::to_string(static_cast<int>(getvalue)), "fail");
				std::cout << "set Cloud Smooth Mode test failure. " << static_cast<int>(modelCan[i]) << std::endl;
			}
		}
	}
}

inline void TestsetLaserSettings_FringeCodingMode(std::vector<std::vector<std::string>>& mymodel, mmind::api::MechEyeDevice& device, writeCsv& write, std::string& testCast) {
	std::vector<mmind::api::LaserSettings::LaserFringeCodingMode> modelCan;
	modelCan.push_back(mmind::api::LaserSettings::LaserFringeCodingMode::Fast);
	modelCan.push_back(mmind::api::LaserSettings::LaserFringeCodingMode::Accurate);
	mmind::api::LaserSettings getLsr;
	for (size_t i = 0; i < mymodel.size(); i++)
	{
		showError(device.getLaserSettings(getLsr));
		getLsr.FringeCodingMode = modelCan[std::atoi(mymodel[i][1].c_str())];
		showError(device.setLaserSettings(getLsr));
		showError(device.getLaserSettings(getLsr));
		if (getLsr.FringeCodingMode != std::atoi(mymodel[i][2].c_str())) {
			std::cout << "set Laser Settings Fringe Coding Mode test failure. " << std::endl;
			write.writeResultToCsv(testCast, std::to_string(static_cast<int>(modelCan[std::atoi(mymodel[i][1].c_str())])), std::to_string(static_cast<int>(getLsr.FringeCodingMode)), "fail");
			continue;
		}
		write.writeResultToCsv(testCast, std::to_string(static_cast<int>(modelCan[std::atoi(mymodel[i][1].c_str())])), std::to_string(static_cast<int>(getLsr.FringeCodingMode)), "pass");
		std::cout << "set Laser Settings Fringe Coding Mode test successful. " << std::endl;
	}
}

inline void TestsetLaserSettings_FramePartitionCount(std::vector<std::vector<std::string>>& mymodel, mmind::api::MechEyeDevice& device, writeCsv& write, std::string& testCast) {
	mmind::api::LaserSettings getLsr;
	for (size_t i = 0; i < mymodel.size(); i++)
	{
		showError(device.getLaserSettings(getLsr));
		getLsr.FramePartitionCount = std::atoi(mymodel[i][1].c_str());
		showError(device.setLaserSettings(getLsr));
		showError(device.getLaserSettings(getLsr));
		if (getLsr.FramePartitionCount != std::atoi(mymodel[i][2].c_str())) {
			std::cout << "set Laser Settings and Frame Partition Count test failure. " << std::endl;
			write.writeResultToCsv(testCast, std::to_string(std::atoi(mymodel[i][1].c_str())), std::to_string(getLsr.FramePartitionCount), "fail");

			continue;
		}
		std::cout << "set Laser Settings and Frame Partition Count test successful. " << std::endl;
		write.writeResultToCsv(testCast, std::to_string(std::atoi(mymodel[i][1].c_str())), std::to_string(getLsr.FramePartitionCount), "pass");

	}

}

inline void TestsetLaserSettings_FrameRangeStart_FrameRangeEnd(std::vector<std::vector<std::string>>& myparameters, mmind::api::MechEyeDevice& device, writeCsv& write, std::string& testCast) {
	for (size_t i = 0; i < myparameters.size(); i++) {
		std::string setresult, getidealresult;
		std::istringstream setsequence(myparameters[i][1]), getidealsequence(myparameters[i][2]);
		std::vector<int> setvalue, getidealvalue, getroitovalue;
		while (setsequence >> setresult) {
			setvalue.push_back(std::atoi(setresult.c_str()));
		}
		mmind::api::LaserSettings getLsr;
		showError(device.getLaserSettings(getLsr));
		getLsr.FrameRangeStart = setvalue[0];
		getLsr.FrameRangeEnd = setvalue[1];
		std::cout << getLsr.FrameRangeStart << " " << getLsr.FrameRangeEnd << std::endl;

		showError(device.setLaserSettings(getLsr));
		showError(device.getLaserSettings(getLsr));
		while (getidealsequence >> getidealresult) {
			getidealvalue.push_back(std::atoi(getidealresult.c_str()));
		}
		getroitovalue.emplace_back(getLsr.FrameRangeStart);
		getroitovalue.emplace_back(getLsr.FrameRangeEnd);
		if (getLsr.FrameRangeStart != getidealvalue[0] || getLsr.FrameRangeEnd != getidealvalue[1]) {
			std::cout << "TestsetLaserSettings_FrameRangeStart_FrameRangeEnd test failure. " << std::endl;
			write.writeResultToCsv(testCast, tostring(setvalue), tostring(getroitovalue), "fail");

			continue;
		}
		std::cout << "TestsetLaserSettings_FrameRangeStart_FrameRangeEnd test successful. " << std::endl;
		write.writeResultToCsv(testCast, tostring(setvalue), tostring(getroitovalue), "pass");

	}



}

inline void TestsetLaserSettings_PowerLevel(std::vector<std::vector<std::string>>& mymodel, mmind::api::MechEyeDevice& device, writeCsv& write, std::string& testCast) {
	mmind::api::LaserSettings getLsr;
	for (size_t i = 0; i < mymodel.size(); i++)
	{
		showError(device.getLaserSettings(getLsr));
		getLsr.PowerLevel = std::atoi(mymodel[i][1].c_str());
		showError(device.setLaserSettings(getLsr));
		showError(device.getLaserSettings(getLsr));
		if (getLsr.PowerLevel != std::atoi(mymodel[i][2].c_str())) {
			std::cout << getLsr.PowerLevel << " TestsetLaserSettings_PowerLevel test failure " << std::atoi(mymodel[i][2].c_str()) << std::endl;
			write.writeResultToCsv(testCast, std::to_string(std::atoi(mymodel[i][1].c_str())), std::to_string(getLsr.PowerLevel), "fail");

			continue;
		}
		std::cout << "TestsetLaserSettings_PowerLevel test successful" << std::endl;
		write.writeResultToCsv(testCast, std::to_string(std::atoi(mymodel[i][1].c_str())), std::to_string(getLsr.PowerLevel), "pass");

	}

}

inline void TestsetUhpCaptureMode(std::vector<std::vector<std::string>>& mymodel, mmind::api::MechEyeDevice& device, writeCsv& write, std::string& testCast) {
	std::vector<mmind::api::UhpSettings::UhpCaptureMode> modelCan;
	modelCan.push_back(mmind::api::UhpSettings::UhpCaptureMode::Camera1);
	modelCan.push_back(mmind::api::UhpSettings::UhpCaptureMode::Camera2);
	modelCan.push_back(mmind::api::UhpSettings::UhpCaptureMode::Merge);


	for (size_t i = 0; i < modelCan.size(); i++) {
		for (size_t j = 0; j < mymodel.size(); j++) {
			mmind::api::UhpSettings::UhpCaptureMode getvalue;
			if (static_cast<int>(modelCan[i]) == atoi(mymodel[j][1].c_str())) {
				showError(device.setUhpCaptureMode(modelCan[i]));
				showError(device.getUhpCaptureMode(getvalue));
				if (static_cast<int>(getvalue) == atoi(mymodel[j][2].c_str())) {
					std::cout << "TestsetUhpCaptureMode test successful. " << static_cast<int>(getvalue) << std::endl;
					write.writeResultToCsv(testCast, std::to_string(static_cast<int>(modelCan[i])), std::to_string(static_cast<int>(getvalue)), "pass");
					continue;
				}
				write.writeResultToCsv(testCast, std::to_string(static_cast<int>(modelCan[i])), std::to_string(static_cast<int>(getvalue)), "fail");
				std::cout << "TestsetUhpCaptureMode test failure. " << static_cast<int>(modelCan[i]) << std::endl;
			}
		}
	}
}

inline void TestsetUhpFringeCodingMode(std::vector<std::vector<std::string>>& mymodel, mmind::api::MechEyeDevice& device, writeCsv& write, std::string& testCast) {
	std::vector<mmind::api::UhpSettings::UhpFringeCodingMode> modelCan;
	modelCan.push_back(mmind::api::UhpSettings::UhpFringeCodingMode::Fast);
	modelCan.push_back(mmind::api::UhpSettings::UhpFringeCodingMode::Accurate);


	for (size_t i = 0; i < modelCan.size(); i++) {
		for (size_t j = 0; j < mymodel.size(); j++) {
			mmind::api::UhpSettings::UhpFringeCodingMode getvalue;
			if (static_cast<int>(modelCan[i]) == atoi(mymodel[j][1].c_str())) {
				showError(device.setUhpFringeCodingMode(modelCan[i]));
				showError(device.getUhpFringeCodingMode(getvalue));
				if (static_cast<int>(getvalue) == atoi(mymodel[j][2].c_str())) {
					std::cout << "TestsetUhpFringeCodingMode test successful. " << static_cast<int>(getvalue) << std::endl;

					write.writeResultToCsv(testCast, std::to_string(static_cast<int>(modelCan[i])), std::to_string(static_cast<int>(getvalue)), "pass");
					continue;
				}
				write.writeResultToCsv(testCast, std::to_string(static_cast<int>(modelCan[i])), std::to_string(static_cast<int>(getvalue)), "fail");
				std::cout << "TestsetUhpFringeCodingMode test successful. " << static_cast<int>(modelCan[i]) << std::endl;

			}
		}
	}

}

inline void TestsetUhpSettings(std::vector<std::vector<std::string>>& mymodel, mmind::api::MechEyeDevice& device, writeCsv& write, std::string& testCast) {
	std::map<int, mmind::api::UhpSettings::UhpCaptureMode> CaptureMode;
	std::map<int, mmind::api::UhpSettings::UhpFringeCodingMode> FringeCodingMode;
	CaptureMode[0] = mmind::api::UhpSettings::UhpCaptureMode::Camera1;
	CaptureMode[1] = mmind::api::UhpSettings::UhpCaptureMode::Camera2;
	CaptureMode[2] = mmind::api::UhpSettings::UhpCaptureMode::Merge;
	FringeCodingMode[0] = mmind::api::UhpSettings::UhpFringeCodingMode::Fast;
	FringeCodingMode[1] = mmind::api::UhpSettings::UhpFringeCodingMode::Accurate;

	for (size_t i = 0; i < mymodel.size(); i++) {
		std::string setresult, getidealresult;
		std::istringstream setsequence(mymodel[i][1]), getidealsequence(mymodel[i][2]);
		std::vector<int> setvalue, getidealvalue, getroitovalue;
		while (setsequence >> setresult) {
			setvalue.push_back(std::atoi(setresult.c_str()));
		}
		while (getidealsequence >> getidealresult) {
			getidealvalue.push_back(std::atoi(getidealresult.c_str()));
		}

		mmind::api::UhpSettings getUhp;
		showError(device.getUhpSettings(getUhp));
		getUhp.CaptureMode = CaptureMode[setvalue[0]];
		getUhp.FringeCodingMode = FringeCodingMode[setvalue[1]];
		showError(device.setUhpSettings(getUhp));
		showError(device.getUhpSettings(getUhp));

		getroitovalue.emplace_back(static_cast<int>(getUhp.CaptureMode));
		getroitovalue.emplace_back(static_cast<int>(getUhp.FringeCodingMode));
		if (static_cast<int>(getUhp.CaptureMode) != getidealvalue[0] || static_cast<int>(getUhp.FringeCodingMode) != getidealvalue[1]) {
			write.writeResultToCsv(testCast, tostring(setvalue), tostring(getroitovalue), "fail");
			std::cout << "TestsetUhpSettings test failure. " << std::endl;

			continue;
		}
		std::cout << "TestsetUhpSettings test successful. " << std::endl;
		write.writeResultToCsv(testCast, tostring(setvalue), tostring(getroitovalue), "pass");

	}

}

*/