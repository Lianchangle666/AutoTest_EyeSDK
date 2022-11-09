#include <iostream>
#include <sstream>
#include "ReadCsv.h"
#include "SampleUtil.h"
#include "AuxiliaryFunction.h"

class FunctionPackage
{
public:
	FunctionPackage() = delete;
	FunctionPackage(FunctionPackage&) = delete;
	FunctionPackage(const std::string path, const std::string ip);

	inline void _FunctionScan3DExposure(int);
	inline void _FunctionScan3DGain(int);
	inline void _FunctionScan3DROI(int);

	inline void _FunctionScan2DExposureMode(int);
	inline void _FunctionScan2DExposureTime(int);
	inline void _FunctionScan2DExpectedGrayValue(int);
	inline void _FunctionScan2DROI(int);
	inline void _FunctionScan2DToneMappingEnable(int);
	inline void _FunctionScan2DHDRExposureSequence(int);
	inline void _FunctionScan2DSharpenFactor(int);

	inline void _FunctionCloudSmoothMode(int);
	inline void _FunctionCloudOutlierFilterMode(int);
	inline void _FunctionFringeContrastThreshold(int);
	inline void _FunctionFringeMinThreshold(int);
	inline void _FunctionProjectorFringeCodingMode(int);
	inline void _FunctionProjectorPowerLevel(int);
	inline void _FunctionProjectorAntiFlickerMode(int);
	
	inline void _FunctionUhpCaptureMode(int);
	inline void _FunctionUhpFringeCodingMode(int);

	inline void _FunctionLaserFringeCodingMode(int);
	inline void _FunctionLaserFramePartitionCount(int);
	inline void _FunctionLaserPowerLevel(int);
	inline void _FunctionLaserRangeEndStart(int);

	inline void FunctionMain();

	~FunctionPackage();


private:
	std::string ip;
	std::string path;
	std::vector<CaseValue> allcase;

protected:
	mmind::api::MechEyeDevice device;
};


FunctionPackage::FunctionPackage(const std::string path, const std::string ip) :path(path), ip(ip)
{
	ReadFile File(path);
	File.ReadTestCase();
	this->allcase = File.ReadTestCase();

	// connect camera
	device.connect(ip);

	// print device information
	mmind::api::MechEyeDeviceInfo deviceinfo;
	device.getDeviceInfo(deviceinfo);
	printDeviceInfo(deviceinfo);

	// print device matrix
	mmind::api::DeviceIntri intri;
	device.getDeviceIntri(intri);
	printCalibParams(intri);

	// print image resolution
	mmind::api::DeviceResolution resolution;
	device.getDeviceResolution(resolution);
	printDeviceResolution(resolution);
	width = resolution.colorMapWidth;
	height = resolution.colorMapHeight;
};


inline void FunctionPackage::_FunctionScan3DExposure(int i)
{
	std::vector<double> getexplore3d;

	auto setexplore3d = StringSplitNumber<double>(allcase[i].second);
	ShowError(device.setScan3DExposure(setexplore3d));
	ShowError(device.getScan3DExposure(getexplore3d));
	auto getstring = NumberCombineString<double>(getexplore3d);

	if (CompareVectorEqual(setexplore3d, getexplore3d))
	{
		std::cout << "¡¾Successful¡¿Scan3DExposure :  get:"<< getstring <<"  input:"<< allcase[i].second <<std::endl;
	}
	else
	{
		std::cout << "¡¾Fail¡¿Scan3DExposure :  get:" << getstring << "  input:" << allcase[i].second << std::endl;
	}
}

inline void FunctionPackage::_FunctionScan3DGain(int i)
{
	double g3d;
	ShowError(device.setScan3DGain(std::stod(allcase[i].second)));
	ShowError(device.getScan3DGain(g3d));
	if (std::stof(allcase[i].second) == g3d)
	{
		std::cout << "¡¾Successful¡¿Scan3DGain :  get:" << g3d << "  input:" << allcase[i].second << std::endl;
	}
	else
	{
		std::cout << "¡¾Fail¡¿Scan3DGain :  get:" << g3d << "  input:" << allcase[i].second << std::endl;
	}
}

inline void FunctionPackage::_FunctionScan3DROI(int i)
{
	ROI_2D_3D getroi;
	ShowError(device.setScan3DROI(SringSplitROI(allcase[i].second)));
	ShowError(device.getScan3DROI(getroi));
	if (CompareROIEqual(getroi, SringSplitROI(allcase[i].second)))
	{
		std::cout << "¡¾Successful¡¿Scan3DROI :  get:" << RoiToString(getroi) << "  input:" << RoiToString(SringSplitROI(allcase[i].second)) << std::endl;
	}
	else
	{
		std::cout << "¡¾Fail¡¿Scan3DROI :  get:" << RoiToString(getroi) << "  input:" << RoiToString(SringSplitROI(allcase[i].second)) << std::endl;
	}
}

inline void FunctionPackage::_FunctionScan2DExposureMode(int i)
{
	SCAN_2D_EXPOSURE_MODE mode;
	ShowError(device.setScan2DExposureMode(Scan2DExposureMode(allcase[i].second)));
	ShowError(device.getScan2DExposureMode(mode));
	if (PrintScan2DExposureMode(mode) == allcase[i].second)
	{
		std::cout << "¡¾Successful¡¿Scan2DExposureMode :  get:" << PrintScan2DExposureMode(mode) << "  input:" << allcase[i].second << std::endl;
	}
	else
	{
		std::cout << "¡¾Fail¡¿Scan2DExposureMode :  get:" << PrintScan2DExposureMode(mode) << "  input:" << allcase[i].second << std::endl;
	}
}

// timed
inline void FunctionPackage::_FunctionScan2DExposureTime(int i)
{
	double value;
	ShowError(device.setScan2DExposureTime(std::stod(allcase[i].second)));
	ShowError(device.getScan2DExposureTime(value));
	if (value== std::stof(allcase[i].second))
	{
		std::cout << "¡¾Successful¡¿Scan2DExposureTime :  get:" << value << "  input:" << allcase[i].second << std::endl;
	}
	else
	{
		std::cout << "¡¾Fail¡¿Scan2DExposureTime :  get:" << value << "  input:" << allcase[i].second << std::endl;
	}
}
// Auto
inline void FunctionPackage::_FunctionScan2DExpectedGrayValue(int i)
{
	int value;
	ShowError(device.setScan2DExpectedGrayValue(std::stoi(allcase[i].second)));
	ShowError(device.getScan2DExpectedGrayValue(value));
	if (std::stoi(allcase[i].second) == value)
	{
		std::cout << "¡¾Successful¡¿Scan2DExpectedGrayValue :  get:" << value << "  input:" << std::stoi(allcase[i].second) << std::endl;
	}
	else
	{
		std::cout << "¡¾Fail¡¿Scan2DExpectedGrayValue :  get:" << value << "  input:" << std::stoi(allcase[i].second) << std::endl;
	}
}
// Auto
inline void FunctionPackage::_FunctionScan2DROI(int i)
{
	ROI_2D_3D getroi;
	ShowError(device.setScan2DROI(SringSplitROI(allcase[i].second)));
	ShowError(device.getScan2DROI(getroi));
	if (CompareROIEqual(getroi, SringSplitROI(allcase[i].second)))
	{
		std::cout << "¡¾Successful¡¿Scan2DROI :  get:" << RoiToString(getroi) << "  input:" << RoiToString(SringSplitROI(allcase[i].second)) << std::endl;
	}
	else
	{
		std::cout << "¡¾Fail¡¿Scan2DROI :  get:" << RoiToString(getroi) << "  input:" << RoiToString(SringSplitROI(allcase[i].second)) << std::endl;
	}
}
// HDR
inline void FunctionPackage::_FunctionScan2DToneMappingEnable(int i)
{
	bool mappingenable;
	ShowError(device.setScan2DToneMappingEnable(StringToBool(allcase[i].second)));
	ShowError(device.getScan2DToneMappingEnable(mappingenable));
	if (StringToBool(allcase[i].second) == mappingenable)
	{
		std::cout << "¡¾Successful¡¿Scan2DToneMappingEnable :  get:" << mappingenable << "  input:" << StringToBool(allcase[i].second) << std::endl;
	}
	else
	{
		std::cout << "¡¾Fail¡¿Scan2DToneMappingEnable :  get:" << mappingenable << "  input:" << StringToBool(allcase[i].second) << std::endl;
	}
}
// HDR
inline void FunctionPackage::_FunctionScan2DHDRExposureSequence(int i)
{
	std::vector<double> getexplore2d;
	auto setexplore2d = StringSplitNumber<double>(allcase[i].second);
	ShowError(device.setScan2DHDRExposureSequence(setexplore2d));
	ShowError(device.getScan2DHDRExposureSequence(getexplore2d));
	auto getstring = NumberCombineString<double>(getexplore2d);

	if (CompareVectorEqual(setexplore2d, getexplore2d))
	{
		std::cout << "¡¾Successful¡¿Scan2DHDRExposureSequence :  get:" << getstring << "  input:" << allcase[i].second << std::endl;
	}
	else
	{
		std::cout << "¡¾Fail¡¿Scan2DHDRExposureSequence :  get:" << getstring << "  input:" << allcase[i].second << std::endl;
	}
}
// All
inline void FunctionPackage::_FunctionScan2DSharpenFactor(int i)
{
	double value;
	ShowError(device.setScan2DSharpenFactor(std::stof(allcase[i].second)));
	ShowError(device.getScan2DSharpenFactor(value));
	if (std::stof(allcase[i].second) == value)
	{
		std::cout << "¡¾Successful¡¿Scan2DSharpenFactor :  get:" << value << "  input:" << std::stof(allcase[i].second) << std::endl;
	}
	else
	{
		std::cout << "¡¾Fail¡¿Scan2DSharpenFactor :  get:" << value << "  input:" << std::stof(allcase[i].second) << std::endl;
	}
}

inline void  FunctionPackage::_FunctionCloudSmoothMode(int i)
{
	POINT_CLOUD_PROCESS_SMOOTH_MODE mode;
	showError(device.setCloudSmoothMode(CloudSmoothMode(allcase[i].second)));
	showError(device.getCloudSmoothMode(mode));
	if (PrintCloudSmoothModeName(mode) == allcase[i].second)
	{
		std::cout << "¡¾Successful¡¿CloudSmoothMode :  get:" << PrintCloudSmoothModeName(mode) << "  input:" << allcase[i].second << std::endl;
	}
	else
	{
		std::cout << "¡¾Fail¡¿CloudSmoothMode :  get:" << PrintCloudSmoothModeName(mode) << "  input:" << allcase[i].second << std::endl;
	}
}

inline void  FunctionPackage::_FunctionCloudOutlierFilterMode(int i)
{
	POINT_CLOUD_PROCESS_OUTLIER_FILTER_MODE mode;
	ShowError(device.setCloudOutlierFilterMode(CloudOutlierFilterMode(allcase[i].second)));
	ShowError(device.getCloudOutlierFilterMode(mode));
	if (PrintOutlierFilterModeName(mode) == allcase[i].second)
	{
		std::cout << "¡¾Successful¡¿CloudOutlierFilterMode :  get:" << PrintOutlierFilterModeName(mode) << "  input:" << allcase[i].second << std::endl;
	}
	else
	{
		std::cout << "¡¾Fail¡¿CloudOutlierFilterMode :  get:" << PrintOutlierFilterModeName(mode) << "  input:" << allcase[i].second << std::endl;
	}
}

inline void FunctionPackage::_FunctionFringeContrastThreshold(int i)
{
	int value;
	ShowError(device.setFringeContrastThreshold(std::stoi(allcase[i].second)));
	ShowError(device.getFringeContrastThreshold(value));
	if (value == std::stoi(allcase[i].second))
	{
		std::cout << "¡¾Successful¡¿FringeContrastThreshold :  get:" << value << "  input:" << allcase[i].second << std::endl;
	}
	else
	{
		std::cout << "¡¾Fail¡¿FringeContrastThreshold :  get:" << value << "  input:" << allcase[i].second << std::endl;
	}
}

inline void FunctionPackage::_FunctionFringeMinThreshold(int i)
{
	int value;
	ShowError(device.setFringeMinThreshold(std::stoi(allcase[i].second)));
	ShowError(device.getFringeMinThreshold(value));
	if (value == std::stoi(allcase[i].second))
	{
		std::cout << "¡¾Successful¡¿FringeContrastThreshold :  get:" << value << "  input:" << allcase[i].second << std::endl;
	}
	else
	{
		std::cout << "¡¾Fail¡¿FringeContrastThreshold :  get:" << value << "  input:" << allcase[i].second << std::endl;
	}
}

inline void FunctionPackage::_FunctionProjectorFringeCodingMode(int i)
{
	PROJECTOR_FRINGE_CODING_MODE pl;
	std::string m = ShowError(device.setProjectorFringeCodingMode(ProjectFringeCodingMode(allcase[i].second)));
	//std::cout << m << std::endl;

	ShowError(device.getProjectorFringeCodingMode(pl));

	if (PrintProjectFringeCodingModeName(pl) == allcase[i].second)
	{
		std::cout << "¡¾Successful¡¿ProjectorFringeCodingMode :  get:" << PrintProjectFringeCodingModeName(pl) << "  input:" << allcase[i].second << std::endl;
	}
	else
	{
		std::cout << "¡¾Fail¡¿ProjectorFringeCodingMode :  get:" << PrintProjectFringeCodingModeName(pl) << "  input:" << allcase[i].second << std::endl;
	}
}

inline void FunctionPackage::_FunctionProjectorPowerLevel(int i)
{
	PROJECTOR_POWER_LEVEL pl;
	ShowError(device.setProjectorPowerLevel(ProjectorPowerLevelModel(allcase[i].second)));
	ShowError(device.getProjectorPowerLevel(pl));

	if (PrintProjectorPowerLevelModelName(pl) == allcase[i].second)
	{
		std::cout << "¡¾Successful¡¿ProjectorPowerLevel :  get:" << PrintProjectorPowerLevelModelName(pl) << "  input:" << allcase[i].second << std::endl;
	}
	else
	{
		std::cout << "¡¾Fail¡¿ProjectorPowerLevel :  get:" << PrintProjectorPowerLevelModelName(pl) << "  input:" << allcase[i].second << std::endl;
	}
}

inline void FunctionPackage::_FunctionProjectorAntiFlickerMode(int i)
{
	PROJECTOR_ANTI_FLICKER_MODE pl;
	ShowError(device.setProjectorAntiFlickerMode(ProjectorAntiFlickerMode(allcase[i].second)));
	ShowError(device.getProjectorAntiFlickerMode(pl));

	if (PrintProjectorAntiFlickerModeName(pl) == allcase[i].second)
	{
		std::cout << "¡¾Successful¡¿ProjectorAntiFlickerMode :  get:" << PrintProjectorAntiFlickerModeName(pl) << "  input:" << allcase[i].second << std::endl;
	}
	else
	{
		std::cout << "¡¾Fail¡¿ProjectorAntiFlickerMode :  get:" << PrintProjectorAntiFlickerModeName(pl) << "  input:" << allcase[i].second << std::endl;
	}
}
// UHP
inline void FunctionPackage::_FunctionUhpCaptureMode(int i)
{
	UHP_CAPTURE_MODE capturemode;
	ShowError(device.setUhpCaptureMode(UhpCaptureMode(allcase[i].second)));
	ShowError(device.getUhpCaptureMode(capturemode));
	if (allcase[i].second == PrintUhpCaptureModeName(capturemode))
	{
		std::cout << "¡¾Successful¡¿UhpCaptureMode :  get:" << PrintUhpCaptureModeName(capturemode) << "  input:" << allcase[i].second << std::endl;
	}
	else
	{
		std::cout << "¡¾Fail¡¿UhpCaptureMode :  get:" << PrintUhpCaptureModeName(capturemode) << "  input:" << allcase[i].second << std::endl;
	}

}
// UHP
inline void FunctionPackage::_FunctionUhpFringeCodingMode(int i)
{
	UHP_FRINGE_CODING_MODE fringecoding;
	ShowError(device.setUhpFringeCodingMode(UhpFringeMode(allcase[i].second)));
	ShowError(device.getUhpFringeCodingMode(fringecoding));
	if (allcase[i].second == PrintUhpFringeModeName(fringecoding))
	{
		std::cout << "¡¾Successful¡¿UhpFringeCodingMode :  get:" << PrintUhpFringeModeName(fringecoding) << "  input:" << allcase[i].second << std::endl;
	}
	else
	{
		std::cout << "¡¾Fail¡¿UhpFringeCodingMode :  get:" << PrintUhpFringeModeName(fringecoding) << "  input:" << allcase[i].second << std::endl;
	}
}
//Laser LSR
inline void FunctionPackage::_FunctionLaserFringeCodingMode(int i)
{
	LASER_LSR_SETTINGS lasersettings, getlasersettings;
	ShowError(device.getLaserSettings(lasersettings));
	lasersettings.fringeCodingMode = LaserFringeCodingMode(allcase[i].second);
	ShowError(device.setLaserSettings(lasersettings));
	ShowError(device.getLaserSettings(getlasersettings));
	if (allcase[i].second == PrintLaserFringeCodingModeName(getlasersettings.fringeCodingMode))
	{
		std::cout << "¡¾Successful¡¿LaserFringeCodingMode :  get:" << PrintLaserFringeCodingModeName(getlasersettings.fringeCodingMode) << "  input:" << allcase[i].second << std::endl;
	}
	else
	{
		std::cout << "¡¾Fail¡¿LaserFringeCodingMode :  get:" << PrintLaserFringeCodingModeName(getlasersettings.fringeCodingMode) << "  input:" << allcase[i].second << std::endl;
	}
}
//Laser LSR
inline void FunctionPackage::_FunctionLaserFramePartitionCount(int i)
{
	LASER_LSR_SETTINGS lasersettings, getlasersettings;
	ShowError(device.getLaserSettings(lasersettings));
	lasersettings.framePartitionCount = std::stoi(allcase[i].second);
	ShowError(device.setLaserSettings(lasersettings));
	ShowError(device.getLaserSettings(getlasersettings));
	if (std::stoi(allcase[i].second) == getlasersettings.framePartitionCount)
	{
		std::cout << "¡¾Successful¡¿LaserFramePartitionCount :  get:" << getlasersettings.framePartitionCount << "  input:" << std::stoi(allcase[i].second) << std::endl;
	}
	else
	{
		std::cout << "¡¾Fail¡¿LaserFramePartitionCount :  get:" << getlasersettings.framePartitionCount << "  input:" << std::stoi(allcase[i].second) << std::endl;
	}
}
//Laser LSR
inline void FunctionPackage::_FunctionLaserPowerLevel(int i)
{
	LASER_LSR_SETTINGS lasersettings, getlasersettings;
	ShowError(device.getLaserSettings(lasersettings));
	lasersettings.powerLevel = std::stoi(allcase[i].second);
	ShowError(device.setLaserSettings(lasersettings));
	ShowError(device.getLaserSettings(getlasersettings));
	if (std::stoi(allcase[i].second) == getlasersettings.powerLevel)
	{
		std::cout << "¡¾Successful¡¿LaserPowerLevel :  get:" << getlasersettings.powerLevel << "  input:" << std::stoi(allcase[i].second) << std::endl;
	}
	else
	{
		std::cout << "¡¾Fail¡¿LaserPowerLevel :  get:" << getlasersettings.powerLevel << "  input:" << std::stoi(allcase[i].second) << std::endl;
	}
}
//Laser LSR
inline void FunctionPackage::_FunctionLaserRangeEndStart(int i)
{
	LASER_LSR_SETTINGS lasersettings, getlasersettings;
	ShowError(device.getLaserSettings(lasersettings));
	auto str = StringSplitStringVector<std::string>(allcase[i].second);
	lasersettings.frameRangeStart = std::stoi(str[0]);
	lasersettings.frameRangeEnd = std::stoi(str[1]);
	ShowError(device.setLaserSettings(lasersettings));
	ShowError(device.getLaserSettings(getlasersettings));
	if (std::stoi(str[0]) == getlasersettings.frameRangeStart &&
		std::stoi(str[1]) == getlasersettings.frameRangeEnd)
	{
		std::cout << "¡¾Successful¡¿LaserRangeEndStart :  get:" << getlasersettings.frameRangeStart<< " "<< getlasersettings.frameRangeEnd << "  input:" << allcase[i].second << std::endl;
	}
	else
	{
		std::cout << "¡¾Fail¡¿LaserRangeEndStart :  get:" << getlasersettings.frameRangeStart<<" " << getlasersettings.frameRangeEnd << "  input:" << allcase[i].second << std::endl;
	}
}

void FunctionPackage::FunctionMain()
{
	for (int i = 0; i < allcase.size(); i++)
	{
		if (FindTestCase(allcase[i].first, "Scan3DExposure")) { _FunctionScan3DExposure(i); }
		else if (FindTestCase(allcase[i].first, "Scan3DGain")) { _FunctionScan3DGain(i); }
		else if (FindTestCase(allcase[i].first, "Scan3DROI")) { _FunctionScan3DROI(i); }

		else if (FindTestCase(allcase[i].first, "Scan2DExposureMode")) { _FunctionScan2DExposureMode(i); }
		else if (FindTestCase(allcase[i].first, "Scan2DExposureTime")) { _FunctionScan2DExposureTime(i); }
		else if (FindTestCase(allcase[i].first, "Scan2DExpectedGrayValue")) { _FunctionScan2DExpectedGrayValue(i); }
		else if (FindTestCase(allcase[i].first, "Scan23ROI")) { _FunctionScan2DROI(i); }
		else if (FindTestCase(allcase[i].first, "Scan2DToneMappingEnable")) { _FunctionScan2DToneMappingEnable(i); }
		else if (FindTestCase(allcase[i].first, "Scan2DHDRExposureSequence")) { _FunctionScan2DHDRExposureSequence(i); }
		else if (FindTestCase(allcase[i].first, "setScan2DSharpenFactor")) { _FunctionScan2DSharpenFactor(i); }


		else if (FindTestCase(allcase[i].first, "CloudSmoothMode")) { _FunctionCloudSmoothMode(i); }
		else if (FindTestCase(allcase[i].first, "CloudOutlierFilterMode")) { _FunctionCloudOutlierFilterMode(i); }
		else if (FindTestCase(allcase[i].first, "FringeContrastThreshold")) { _FunctionFringeContrastThreshold(i); }
		else if (FindTestCase(allcase[i].first, "FringeMinThreshold")) { _FunctionFringeMinThreshold(i); }

		else if (FindTestCase(allcase[i].first, "ProjectorFringeCodingMode")) { _FunctionProjectorFringeCodingMode(i); }
		else if (FindTestCase(allcase[i].first, "ProjectorPowerLevel")) { _FunctionProjectorPowerLevel(i); }
		else if (FindTestCase(allcase[i].first, "ProjectorAntiFlickerMode")) { _FunctionProjectorAntiFlickerMode(i); }

		else if (FindTestCase(allcase[i].first, "LaserFringeCodingMode")) { _FunctionLaserFringeCodingMode(i); }
		else if (FindTestCase(allcase[i].first, "LaserFramePartitionCount")) { _FunctionLaserFramePartitionCount(i); }
		else if (FindTestCase(allcase[i].first, "LaserPowerLevel")) { _FunctionLaserPowerLevel(i); }
		else if (FindTestCase(allcase[i].first, "LaserRangeEnd-Start")) { _FunctionLaserRangeEndStart(i); }

		else if (FindTestCase(allcase[i].first, "UhpCaptureMode")) { _FunctionUhpCaptureMode(i); }
		else if (FindTestCase(allcase[i].first, "UhpFringeCodingMode")) { _FunctionUhpFringeCodingMode(i); }

	}
}

FunctionPackage::~FunctionPackage()
{
	std::cout << "-------------Disconnnected Successfully.-------------" << std::endl;
	device.disconnect();
}