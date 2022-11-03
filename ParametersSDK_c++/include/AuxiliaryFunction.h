#include <iostream>
#include "MechEyeApi.h"

using ROI_2D_3D = mmind::api::ROI;
using POINT_CLOUD_PROCESS_OUTLIER_FILTER_MODE = mmind::api::PointCloudProcessingSettings::CloudOutlierFilterMode;
using POINT_CLOUD_PROCESS_SMOOTH_MODE = mmind::api::PointCloudProcessingSettings::CloudSmoothMode;
using PROJECTOR_FRINGE_CODING_MODE = mmind::api::ProjectorSettings::FringeCodingMode;
using PROJECTOR_POWER_LEVEL = mmind::api::ProjectorSettings::PowerLevel;
using PROJECTOR_ANTI_FLICKER_MODE = mmind::api::ProjectorSettings::AntiFlickerMode;
using UHP_FRINGE_CODING_MODE = mmind::api::UhpSettings::UhpFringeCodingMode;
using UHP_CAPTURE_MODE = mmind::api::UhpSettings::UhpCaptureMode;
using LASER_LSR_SETTINGS = mmind::api::LaserSettings;
using LASER_LSR_SETTINGS_CODING_MODE = mmind::api::LaserSettings::LaserFringeCodingMode;



unsigned width = 0;
unsigned height = 0;

inline std::string ShowError(const mmind::api::ErrorStatus& status)
{
	if (status.isOK())
		return " ";

	return  "Error Code : " + std::to_string(status.errorCode) + ", Error Description: " + status.errorDescription ;
}


// split the string with Spaces and convert to int/double/float
template <typename T1>
std::vector<T1> StringSplitNumber(std::string linestr)
{
	std::vector<T1> value;
	std::string str;

	std::stringstream sin(linestr);
	while (std::getline(sin, str, ' '))
	{
		value.push_back(std::stof(str));
	}
	return value;
}

// split the string with Spaces and convert to string vector
template <typename T1>
std::vector<T1> StringSplitStringVector(std::string linestr)
{
	std::vector<T1> value;
	std::string str;

	std::stringstream sin(linestr);
	while (std::getline(sin, str, ' '))
	{
		value.push_back(str);
	}
	return value;
}

// Numeric arrays are converted to strings
template <typename T1>
std::string NumberCombineString(std::vector<T1> value)
{
	std::string str = "";
	for (int i = 0; i < value.size(); i++)
	{
		std::stringstream ss1;
		ss1 << value[i];
		str += ss1.str() + " ";
	}
	return str;
}


// Compares two number arrays for equality
bool CompareVectorEqual(std::vector<double>v1, std::vector<double>v2)
{
	int flag = 0;
	if (v1.size() != v2.size())
	{
		return false;
	}
	else
	{
		for (int i = 0; i < v1.size(); i++)
		{
			if (std::to_string(v1[i]) == std::to_string(v2[i]))
			{
				flag++;
			}
		}
		if (flag == v1.size())
			return true;
		return false;
	}

}

// Find test cases based on strings
bool FindTestCase(std::string& allstring, const std::string& objstring)
{
	std::string::size_type tmp = allstring.find(objstring);
	if (tmp == std::string::npos)
		return false;
	return true;
}

// Split the input ROI string into ROI type
ROI_2D_3D SringSplitROI(std::string linestr)
{
	ROI_2D_3D roi;
	auto ROI = StringSplitStringVector<std::string>(linestr);
	roi.x = std::stoi(ROI[0]);
	roi.y = std::stoi(ROI[1]);
	roi.width = ROI[2] == "width" ? width : (ROI[2] == "width+1" ? width + 1 : std::stoi(ROI[2]));
	roi.height = ROI[3] == "height" ? width : (ROI[3] == "height+1" ? height + 1 : std::stoi(ROI[3]));
	return roi;
}

// Compare two ROI type for equality
bool CompareROIEqual(ROI_2D_3D roi1, ROI_2D_3D roi2)
{
	if (roi1.height == roi2.height && roi1.width == roi2.width && roi1.x == roi2.x && roi1.y == roi2.y)
		return true;
	return false;
}

// Rois are converted to strings
std::string RoiToString(ROI_2D_3D roi)
{
	return std::to_string(roi.x)+ " " + std::to_string(roi.y) + " " + std::to_string(roi.width)+ " " + std::to_string(roi.height);
}

// Checks whether the string is a bool
bool StringToBool(std::string str)
{
	return (str == "TRUE");
}

//  Enter the mode name to return the CloudOutlierFilterMode mode type
POINT_CLOUD_PROCESS_OUTLIER_FILTER_MODE CloudOutlierFilterMode(std::string modelname)
{
	return modelname == "Off" ? POINT_CLOUD_PROCESS_OUTLIER_FILTER_MODE::Off :
		(modelname == "Weak" ? POINT_CLOUD_PROCESS_OUTLIER_FILTER_MODE::Weak :
			POINT_CLOUD_PROCESS_OUTLIER_FILTER_MODE::Normal);
}

// Enter the mode status and return CloudOutlierFilterMode Mode name
std::string PrintOutlierFilterModeName(POINT_CLOUD_PROCESS_OUTLIER_FILTER_MODE value)
{
	return value == POINT_CLOUD_PROCESS_OUTLIER_FILTER_MODE::Off ? "Off" :
		(value == POINT_CLOUD_PROCESS_OUTLIER_FILTER_MODE::Weak ? "Weak" :
			"Normal");
}

//  Enter the mode name to return the CloudSmoothMode mode type
POINT_CLOUD_PROCESS_SMOOTH_MODE CloudSmoothMode(std::string modelname)
{
	return modelname == "Off" ? POINT_CLOUD_PROCESS_SMOOTH_MODE::Off :
		(modelname == "Weak" ? POINT_CLOUD_PROCESS_SMOOTH_MODE::Weak :
			(modelname == "Normal" ? POINT_CLOUD_PROCESS_SMOOTH_MODE::Normal :
				POINT_CLOUD_PROCESS_SMOOTH_MODE::Strong));
}

// Enter the mode status and return CloudOutlierFilterMode Mode name
std::string PrintCloudSmoothModeName(POINT_CLOUD_PROCESS_SMOOTH_MODE value)
{
	return value == POINT_CLOUD_PROCESS_SMOOTH_MODE::Off ? "Off" :
		(value == POINT_CLOUD_PROCESS_SMOOTH_MODE::Weak ? "Weak" :
			(value == POINT_CLOUD_PROCESS_SMOOTH_MODE::Normal ? "Normal" :
				"Strong"));
}

//  Enter the mode name to return the ProjectFringeCodingMode mode type
PROJECTOR_FRINGE_CODING_MODE ProjectFringeCodingMode(std::string modelname)
{
	return modelname == "Fast" ? PROJECTOR_FRINGE_CODING_MODE::Fast : PROJECTOR_FRINGE_CODING_MODE::Accurate;
}

// Enter the mode status and return PrintProjectFringeCodingModeName Mode name
std::string PrintProjectFringeCodingModeName(PROJECTOR_FRINGE_CODING_MODE value)
{
	return value == PROJECTOR_FRINGE_CODING_MODE::Fast ? "Fast" : "Accurate";
}

//  Enter the mode name to return the ProjectorPowerLevelModel mode type
PROJECTOR_POWER_LEVEL ProjectorPowerLevelModel(std::string modelname)
{
	return modelname == "High" ? PROJECTOR_POWER_LEVEL::High :
		(modelname == "Normal" ? PROJECTOR_POWER_LEVEL::Normal :
			PROJECTOR_POWER_LEVEL::Low);
}

// Enter the mode status and return PrintProjectorPowerLevelModelName Mode name
std::string PrintProjectorPowerLevelModelName(PROJECTOR_POWER_LEVEL value)
{
	return value == PROJECTOR_POWER_LEVEL::High ? "High" :
		(value == PROJECTOR_POWER_LEVEL::Normal ? "Normal" : "Low");
}

//  Enter the mode name to return the ProjectorAntiFlickerMode mode type
PROJECTOR_ANTI_FLICKER_MODE ProjectorAntiFlickerMode(std::string modelname)
{
	return modelname == "Off" ? PROJECTOR_ANTI_FLICKER_MODE::Off :
		(modelname == "AC50Hz" ? PROJECTOR_ANTI_FLICKER_MODE::AC50Hz :
			PROJECTOR_ANTI_FLICKER_MODE::AC60Hz);
}

// Enter the mode status and return PrintProjectorAntiFlickerModeName Mode name
std::string PrintProjectorAntiFlickerModeName(PROJECTOR_ANTI_FLICKER_MODE value)
{
	return value == PROJECTOR_ANTI_FLICKER_MODE::Off ? "Off" :
		(value == PROJECTOR_ANTI_FLICKER_MODE::AC50Hz ? "AC50Hz" : "AC60Hz");
}


//  Enter the mode name to return the LaserFringeCodingMode mode type
LASER_LSR_SETTINGS_CODING_MODE LaserFringeCodingMode(std::string modelname)
{
	return modelname == "Accurate" ? LASER_LSR_SETTINGS_CODING_MODE::Accurate : LASER_LSR_SETTINGS_CODING_MODE::Fast;
}

// Enter the mode status and return PrintLaserFringeCodingModeName Mode name
std::string PrintLaserFringeCodingModeName(LASER_LSR_SETTINGS_CODING_MODE value)
{
	return value == LASER_LSR_SETTINGS_CODING_MODE::Accurate ? "Accurate" : "Fast";
}



//  Enter the mode name to return the UhpCaptureMode mode type
UHP_CAPTURE_MODE UhpCaptureMode(std::string modelname)
{
	return modelname == "Camera1" ? UHP_CAPTURE_MODE::Camera1 :
		(modelname == "Camera2"? UHP_CAPTURE_MODE::Camera2: UHP_CAPTURE_MODE::Merge);
}

// Enter the mode status and return PrintUhpCaptureModeName Mode name
std::string PrintUhpCaptureModeName(UHP_CAPTURE_MODE value)
{
	return value == UHP_CAPTURE_MODE::Camera1 ? "Camera1" : 
		(value == UHP_CAPTURE_MODE::Camera2? "Camera2": "Merge");
}


//  Enter the mode name to return the UhpFringeCodingMode mode type
UHP_FRINGE_CODING_MODE UhpFringeMode(std::string modelname)
{
	return modelname == "Fast" ? UHP_FRINGE_CODING_MODE::Fast : UHP_FRINGE_CODING_MODE::Accurate;
}

// Enter the mode status and return PrintUhpFringeModeName Mode name
std::string PrintUhpFringeModeName(UHP_FRINGE_CODING_MODE value)
{
	return value == UHP_FRINGE_CODING_MODE::Fast ? "Fast" : "Accurate";
}