#pragma once
#include <iostream>
#include <thread>
#include <string>
#include "MechEyeApi.h"
#include "MainFunction.h"
#include "OpenCVUtil.h"

std::string split(80, '*');

class CapturePackage : public FunctionPackage
{
public:
	CapturePackage() = delete;
	CapturePackage(CapturePackage&) = delete;
	CapturePackage(const std::string, std::string);
	
	inline void FunctionCaptureColorMap(const std::string);
	inline void FunctionCaptureDepthMap(const std::string);

	~CapturePackage();

private:
	std::string _ip;
	std::string _path;
	std::string folder;
};

CapturePackage::CapturePackage(const std::string _path, std::string _ip) : FunctionPackage(_path, _ip) 
{
	this->folder = ".\\capture_foldr";

	std::string command;
	command = "mkdir" + folder;
	system(command.c_str());
};

inline void CapturePackage::FunctionCaptureColorMap(const std::string name)
{
	COLOR_MAP color;
	const std::string colorFile = folder + "\\" + name + ".png";

	auto start = std::chrono::high_resolution_clock::now();
	ShowError(device.captureColorMap(color));
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> tm = end - start;
	std::cout << "Capture colormap time(ms): " << tm.count() << std::endl;

	saveMap(color, colorFile);
	std::cout << split << std::endl;

	std::this_thread::sleep_for(std::chrono::seconds(1));

}

inline void CapturePackage::FunctionCaptureDepthMap(const std::string name)
{
	DEPTH_MAP depth;

	auto start = std::chrono::high_resolution_clock::now();
	const std::string colorFile = folder + "\\" + name + ".tiff";
	ShowError(device.captureDepthMap(depth));
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> tm = end - start;
	std::cout << "Capture depthmap time(ms): " << tm.count() << std::endl;

	saveMap(depth, colorFile);
	std::cout << split << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));
}

CapturePackage::~CapturePackage() { }