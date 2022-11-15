#include <iostream>
#include <string>
#include<numeric>
#include <exception>
#include <algorithm>
#include <thread>
#include <chrono>
#include "MechEyeApi.h"
#include "PclUtil.h"
#include "OpenCVUtil.h"

bool FLAG = true;

namespace MMFunc {

	std::string SplitStar(100, '*');
	std::string SplitLine(70, '=');
	std::string SplitPoint(40, '.');

	typedef enum class cam {
		Laser,
		UHP,
		ProXsNano,
		Other,
		NoCam
	};

	bool showError(mmind::api::ErrorStatus status)
	{
		if (status.isOK())
			return true;
		std::cout << "ErrorCode: " << status.errorCode
			<< " ErrorMessage: " << status.errorDescription
			<< std::endl;
		return false;
	}

	bool isNumber(std::string num)
	{
		for (std::string::iterator it = num.begin(); it != num.end(); it ++)
		{
			if (*it < '0' || *it  > '9')
			{
				return false;
			}
		}
		return true;
	}

	bool isDouble(std::string str)
	{
		try {
			double y = std:: stod(str);
		}
		catch (const std::exception&) {
			return false;
		}
		return true;
	}

	double saveMapTime(mmind::api::ColorMap* color, const std::string name)
	{
		std::string mapname = name + ".png";

		std::this_thread::sleep_for(std::chrono::seconds(3));
		auto testStart = std::chrono::high_resolution_clock::now();
		saveMap(*color, mapname);
		auto testEnd = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> tm = testEnd - testStart;

		std::cout << "Save 2D image take: " << tm.count() << " ms" << std::endl;
		return tm.count();

	}

	double saveMapTime(mmind::api::DepthMap* depth, const std::string name)
	{
		std::string mapname = name + ".tiff";

		std::this_thread::sleep_for(std::chrono::seconds(3));
		auto testStart = std::chrono::high_resolution_clock::now();
		saveMap(*depth, mapname);
		auto testEnd = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> tm = testEnd - testStart;

		std::cout << "Save depth image take: " << tm.count() << " ms" << std::endl;
		return tm.count();

	}

	double saveMapTime(mmind::api::PointXYZMap pointXYZMap, const std::string name)
	{
		std::string pointCloudPath = name + ".ply";

		std::this_thread::sleep_for(std::chrono::seconds(3));
		pcl::PointCloud<pcl::PointXYZ> pointCloud(pointXYZMap.width(), pointXYZMap.height());
		toPCL(pointCloud, pointXYZMap);
		//viewPCL(pointCloud);

		auto testStart = std::chrono::high_resolution_clock::now();
		savePLY(pointXYZMap, pointCloudPath);
		auto testEnd = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> tm = testEnd - testStart;
		std::cout << "Save pointcloud image take: " << tm.count() << " ms" << std::endl;
		return tm.count();

	}

	double saveMapTime(mmind::api::PointXYZBGRMap pointXYZBGRMap, const std::string name)
	{
		std::string colorPointCloudPath = name + ".ply";

		std::this_thread::sleep_for(std::chrono::seconds(3));
		pcl::PointCloud<pcl::PointXYZRGB> colorPointCloud(pointXYZBGRMap.width(), pointXYZBGRMap.height());
		toPCL(colorPointCloud, pointXYZBGRMap);
		//viewPCL(colorPointCloud);

		auto testStart = std::chrono::high_resolution_clock::now();
		savePLY(pointXYZBGRMap, colorPointCloudPath);
		auto testEnd = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> tm = testEnd - testStart;
		std::cout << "Save color pointcloud image take: " << tm.count() << " ms" << std::endl;

		return tm.count();
	}

	static std::vector<double> capture(mmind::api::MechEyeDevice* Dv, const int type, int times = 15)
	{

		std::vector<double> captureTimes, saveMaptimes;
		switch (type)
		{
		case 1:
		{
			mmind::api::ColorMap cm;
			while (times > 0)
			{
				auto testStart = std::chrono::high_resolution_clock::now();
				Dv->captureColorMap(cm);
				auto testEnd = std::chrono::high_resolution_clock::now();
				std::chrono::duration<double, std::milli> tm = testEnd - testStart;
				captureTimes.emplace_back(tm.count());
				std::cout << "Capture 2D image time: " << tm.count() << " ms" << std::endl;

				saveMaptimes.emplace_back(saveMapTime(&cm, std::to_string(times)));
				std::cout << SplitPoint << std::endl;
				--times;
			}
		}
		case 2:
		{
			mmind::api::DepthMap dm;
			while (times > 0)
			{
				auto testStart = std::chrono::high_resolution_clock::now();
				Dv->captureDepthMap(dm);
				auto testEnd = std::chrono::high_resolution_clock::now();
				std::chrono::duration<double, std::milli> tm = testEnd - testStart;
				captureTimes.emplace_back(tm.count());
				std::cout << "Capture depth image time: " << tm.count() << " ms" << std::endl;

				saveMaptimes.emplace_back(saveMapTime(&dm, std::to_string(times)));
				std::cout << SplitPoint << std::endl;
				--times;
			}
		}
		case 3:
		{
			mmind::api::PointXYZMap pm;
			while (times > 0)
			{

				auto testStart = std::chrono::high_resolution_clock::now();
				Dv->capturePointXYZMap(pm);
				auto testEnd = std::chrono::high_resolution_clock::now();
				std::chrono::duration<double, std::milli> tm = testEnd - testStart;
				captureTimes.emplace_back(tm.count());
				std::cout << "Capture pointcloud map time: " << tm.count() << " ms" << std::endl;

				saveMaptimes.emplace_back(saveMapTime(pm, std::to_string(times)));
				std::cout << SplitPoint << std::endl;
				--times;
			}
		}
		case 4:
		{
			mmind::api::PointXYZBGRMap pcm;
			while (times > 0)
			{
				auto testStart = std::chrono::high_resolution_clock::now();
				Dv->capturePointXYZBGRMap(pcm);
				auto testEnd = std::chrono::high_resolution_clock::now();
				std::chrono::duration<double, std::milli> tm = testEnd - testStart;
				captureTimes.emplace_back(tm.count());
				std::cout << "Capture color pointcloud map time: " << tm.count() << " ms" << std::endl;

				saveMaptimes.emplace_back(saveMapTime(pcm, std::to_string(times)));
				std::cout << SplitPoint << std::endl;
				--times;
			}
		}

		}
		std::vector<double>m(captureTimes.begin() + 4, captureTimes.end());
		std::vector<double>n(saveMaptimes.begin() + 4, saveMaptimes.end());

		std::cout << SplitStar << std::endl
				  << "Capture image average time: " 
				  << accumulate(captureTimes.begin() + 4, captureTimes.end(), 0) / static_cast<double>(m.size()) << " ms" << std::endl
				  << "Save image average time: " 
				  << accumulate(saveMaptimes.begin() + 4, saveMaptimes.end(), 0) / static_cast<double>(n.size()) << " ms" << std::endl
				  << SplitStar << std::endl;

		return captureTimes;
	}

	cam isCameraSeries(std::string serious)
	{
		cam laser = cam::Laser;
		cam uhp = cam::UHP;
		cam proxsnano = cam::ProXsNano;
		cam other = cam::Other;

		std::transform(serious.begin(), serious.end(), serious.begin(), tolower);

		std::vector<std::string> Laser{ "laser", "lsr"};
		std::vector<std::string> ProjectorCam{ "nano", "pro xs", "pro m", "pro s" };


		for (auto& type : Laser)
		{
			if (serious.find(type) != std::string::npos)
				return laser;
		}


		for (auto& type : ProjectorCam)
		{
			if (serious.find(type) != std::string::npos)
				return proxsnano;
		}

		if (serious.find("uhp") != std::string::npos)
			return uhp;
	
		return other;
	}

	
}

class DeviceType
{
public:
	DeviceType() = delete;
	DeviceType(DeviceType&) = delete;
	DeviceType(const std::string);
	MMFunc::cam connectFindCameraName();
	void execute();
	
	inline void set3DExposureMessage();
	inline void set2DExposureMessage();
	inline void setCloudModeMessage();
	inline void setCloudOutlierFilterModeMessage();

	inline void setUhpSettingsMessage();
	inline void setLaserSettingsMessage();
	inline void setProjectorMessage();


public:
	inline void captureType();

private:
	inline void _setUhpFringeCodingMode();
	inline void _setUhpCaptureMode();

	std::string ip;
	std::string cameraname;
	mmind::api::MechEyeDevice device;
};


DeviceType::DeviceType(const std::string ip) :ip(ip)
{
	std::string msg = mmind::api::getApiInformation();
	std::cout << MMFunc::SplitStar << std::endl
			  << msg << std::endl
			  << MMFunc::SplitStar <<std::endl;
}

inline void DeviceType::_setUhpCaptureMode()
{
	std::string num;

	while (FLAG)
	{
		std::cout << "Please enter UHP capture mode(1: Off, 2: Weak, 3: Normal): ";
		std::cin >> num;
		if (MMFunc::isNumber(num))
		{
			switch (std::stoll(num))
			{
			case 1:
				device.setUhpCaptureMode(mmind::api::UhpSettings::UhpCaptureMode::Camera1);
				FLAG = false;
				break;
			case 2:
				device.setUhpCaptureMode(mmind::api::UhpSettings::UhpCaptureMode::Camera2);
				FLAG = false;
				break;
			case 3:
				device.setUhpCaptureMode(mmind::api::UhpSettings::UhpCaptureMode::Merge);
				FLAG = false;
				break;
			default:
				std::cout << "Error, invalid input! ";
			}
		}
		else { std::cout << "Error, invalid input! "; }
	}
	std::cout << MMFunc::SplitLine << std::endl;
	FLAG = true;
}

inline void DeviceType::_setUhpFringeCodingMode()
{
	std::string num;

	while (FLAG)
	{
		std::cout << "Please enter UHP capture mode(1: Fast, 2: Accurate): ";
		std::cin >> num;
		if (MMFunc::isNumber(num))
		{
			switch (std::stoll(num))
			{
			case 1:
				device.setUhpFringeCodingMode(mmind::api::UhpSettings::UhpFringeCodingMode::Fast);
				FLAG = false;
				break;
			case 2:
				device.setUhpFringeCodingMode(mmind::api::UhpSettings::UhpFringeCodingMode::Accurate);
				FLAG = false;
				break;
			default:
				std::cout << "Error, invalid input! ";
			}
		}
		else { std::cout << "Error, invalid input! "; }
	}
	std::cout << MMFunc::SplitLine << std::endl;
	FLAG = true;

}

MMFunc::cam DeviceType::connectFindCameraName()
{
	MMFunc::cam nocam = MMFunc::cam::NoCam;

	if (!MMFunc::showError(device.connect(ip)))
	{
		std::cout << "Error, Please input valid camera ip !" << std::endl;
		return nocam;
	}

	mmind::api::MechEyeDeviceInfo info;
	MMFunc::showError(device.getDeviceInfo(info));

	std::cout << "Current Device Information: " << std::endl
		<< "Camera Name: " << info.model << std::endl
		<< "Camera   ID: " << info.id << std::endl
		<< "Camera   IP: " << info.ipAddress << std::endl
		<< "Firmware  V: " << info.firmwareVersion << std::endl
		<< "Hardware  V: " << info.hardwareVersion << std::endl
		<< MMFunc::SplitLine << std::endl;

	this->cameraname = info.model;

	return MMFunc::isCameraSeries(this->cameraname);
}

void DeviceType::execute()
{


	auto CF = DeviceType::connectFindCameraName();
	if (CF == MMFunc::cam::NoCam)
		return;

	set3DExposureMessage();
	set2DExposureMessage();
	setCloudModeMessage();
	setCloudOutlierFilterModeMessage();


	switch (CF)
	{
	case  MMFunc::cam::Laser:
	{
		setLaserSettingsMessage();
		break;
	}
	case  MMFunc::cam::UHP:
	{
		setUhpSettingsMessage();
		break;
	}
	case  MMFunc::cam::ProXsNano:
	{
		setProjectorMessage();
		break;
	}
	default:
		break;
	}

	captureType();
}

inline void DeviceType::set3DExposureMessage()
{
	std::vector<double> exposure3d;
	while (true)
	{
		std::string count;
		std::cout << "Please input 3D exposure count: ";
		std::cin >> count;
		if (MMFunc::isNumber(count) && std::stoi(count)> 0 && std::stoi(count) < 4)
		{
			int n = std::stoi(count);
			while (n > 0)
			{
				std::string exp3d;
				std::cout << "Please input 3D exposure time" << n << ": ";
				std::cin >> exp3d;
				if (MMFunc::isDouble(exp3d) && (std::stod(exp3d) >= 0.1) && (std::stod(exp3d) <= 99))
				{
					exposure3d.emplace_back(std::stod(exp3d));
					n--;
				}
				else { std::cout << "Error input(0.1-999), "; }
			}
			break;
		}
		std::cout << "Error input(0-3), ";

	}
	MMFunc::showError(device.setScan3DExposure(exposure3d));
	std::cout << MMFunc::SplitLine << std::endl;

}

inline void DeviceType::set2DExposureMessage()
{
	while (true)
	{
		std::string exp2d;
		std::cout << "Please input 2D exposure time: ";
		std::cin >> exp2d;
		if (MMFunc::isDouble(exp2d) && (std::stod(exp2d) >= 0.1) && (std::stod(exp2d) <= 999))
		{
			MMFunc::showError(device.setScan2DExposureMode(mmind::api::Scanning2DSettings::Scan2DExposureMode::Timed));
			MMFunc::showError(device.setScan2DExposureTime(std::stod(exp2d)));
			break;
		}
		std::cout << "Error input(0.1-999), ";
	}
	std::cout << MMFunc::SplitLine << std::endl;
}

inline void DeviceType::setCloudModeMessage()
{
	bool FLAG = true;
	std::string num;

	while (FLAG)
	{
		std::cout << "Please enter smooth mode(1: Off, 2: Weak, 3: Normal, 4: Strong): ";
		std::cin >> num;
		if (MMFunc::isNumber(num)) 
		{
			switch (std::stoll(num))
			{
			case 1:
				device.setCloudSmoothMode(mmind::api::PointCloudProcessingSettings::CloudSmoothMode::Off);
				FLAG = false;
				break;
			case 2:
				device.setCloudSmoothMode(mmind::api::PointCloudProcessingSettings::CloudSmoothMode::Weak);
				FLAG = false;
				break;
			case 3:
				device.setCloudSmoothMode(mmind::api::PointCloudProcessingSettings::CloudSmoothMode::Normal);
				FLAG = false;
				break;
			case 4:
				device.setCloudSmoothMode(mmind::api::PointCloudProcessingSettings::CloudSmoothMode::Strong);
				FLAG = false;
				break;
			default:
				//FLAG = true;
				std::cout << "Error, invalid input! ";
			}
		}
		else { std::cout << "Error, invalid input! "; }
	}
	FLAG = true;
	std::cout << MMFunc::SplitLine << std::endl;
}

inline void DeviceType::setCloudOutlierFilterModeMessage()
{
	//bool FLAG = true;
	std::string num;

	while (FLAG)
	{
		std::cout << "Please enter outlier filter mode(1: Off, 2: Weak, 3: Normal): ";
		std::cin >> num;
		if (MMFunc::isNumber(num))
		{
			switch (std::stoll(num))
			{
			case 1:
				device.setCloudOutlierFilterMode(mmind::api::PointCloudProcessingSettings::CloudOutlierFilterMode::Off);
				FLAG = false;
				break;
			case 2:
				device.setCloudOutlierFilterMode(mmind::api::PointCloudProcessingSettings::CloudOutlierFilterMode::Weak);
				FLAG = false;
				break;
			case 3:
				device.setCloudOutlierFilterMode(mmind::api::PointCloudProcessingSettings::CloudOutlierFilterMode::Normal);
				FLAG = false;
				break;
			default:
				std::cout << "Error, invalid input! ";
			}
		}
		else { std::cout << "Error, invalid input! "; }
	}
	std::cout << MMFunc::SplitLine << std::endl;
	FLAG = true;

}

inline void DeviceType::setUhpSettingsMessage()
{
	_setUhpCaptureMode();
	_setUhpFringeCodingMode();
}

inline void DeviceType::setLaserSettingsMessage()
{
	std::string num;
	mmind::api::LaserSettings laser;

	while (FLAG)
	{
		device.getLaserSettings(laser);
		std::cout << "Please enter Laser fringe coding mode(1: Fast, 2: Accurate): ";
		std::cin >> num;
		if (MMFunc::isNumber(num))
		{
			switch (std::stoll(num))
			{
			case 1:
				laser.fringeCodingMode = mmind::api::LaserSettings::LaserFringeCodingMode::Fast;
				FLAG = false;
				break;
			case 2:
				laser.fringeCodingMode = mmind::api::LaserSettings::LaserFringeCodingMode::Accurate;
				FLAG = false;
				break;
			default:
				std::cout << "Error, invalid input! ";
			}
		}
		else { std::cout << "Error, invalid input! "; }
	}

	// laser.framePartitionCount = 4;
	// laser.powerLevel = 1;
	// laser.frameRangeStart = 1;
	// laser.frameRangeEnd = 100;
	device.setLaserSettings(laser);

	std::cout << MMFunc::SplitLine << std::endl;
	FLAG = true;

}

inline void DeviceType::setProjectorMessage()
{
	std::string num;

	while (FLAG)
	{
		std::cout << "Please enter projector fringe coding mode(1: Fast, 2: Accurate): ";
		std::cin >> num;
		if (MMFunc::isNumber(num))
		{
			switch (std::stoll(num))
			{
			case 1:
				device.setProjectorFringeCodingMode( mmind::api::ProjectorSettings::FringeCodingMode::Fast);
				FLAG = false;
				break;
			case 2:
				device.setProjectorFringeCodingMode(mmind::api::ProjectorSettings::FringeCodingMode::Accurate);
				FLAG = false;
				break;
			default:
				std::cout << "Error, invalid input! ";
			}
		}
		else { std::cout << "Error, invalid input! "; }
	}

	std::cout << MMFunc::SplitLine << std::endl;
	FLAG = true;
}

inline void DeviceType::captureType()
{
	std::string num;

	while (FLAG)
	{
		std::cout << "Please enter the time you want to calculate the type of map taken "
			<<"(1: 2D image, 2: Depth image, 3: pointcloud image, 4: color pointcloud image) : ";
		std::cin >> num;
		if (MMFunc::isNumber(num))
		{
			switch (std::stoll(num))
			{
			case 1:
			{
				MMFunc::capture(&device, std::stoll(num));
				FLAG = false;
				break;
			}

			case 2:
			{
				MMFunc::capture(&device, std::stoll(num));
				FLAG = false;
				break;
			}
			case 3:
			{
				MMFunc::capture(&device, std::stoll(num));
				FLAG = false;
				break;
			}
			case 4:
			{
				MMFunc::capture(&device, std::stoll(num));
				FLAG = false;
				break;
			}
			default:
				std::cout << "Error, invalid input! ";
			}
		}
		else { std::cout << "Error, invalid input! "; }
	}
	FLAG = true;

}


int main()
{
	const std::string ip = "192.168.20.234";

	DeviceType deviceCam(ip);
	deviceCam.execute();

    return 0;
}
