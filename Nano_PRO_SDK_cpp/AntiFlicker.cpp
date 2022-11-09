/*******************************************************************************
 *BSD 3-Clause License
 *
 *Copyright (c) 2016-2022, Mech-Mind Robotics
 *All rights reserved.
 *
 *Redistribution and use in source and binary forms, with or without
 *modification, are permitted provided that the following conditions are met:
 *
 *1. Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 *2. Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 *3. Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 *THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 *FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 *OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ******************************************************************************/

#include <iostream>

#include "MechEyeApi.h"
#include "SampleUtil.h"

using MM_CodingMode = mmind::api::ProjectorSettings::FringeCodingMode;
using MM_PowerLevelMode = mmind::api::ProjectorSettings::PowerLevel;
using MM_AntiFlickerMode = mmind::api::ProjectorSettings::AntiFlickerMode;



int main()
{
    mmind::api::MechEyeDevice device;
    if (!findAndConnect(device))
        return -1;

    MM_CodingMode getcodingMode;
    showError(device.getProjectorFringeCodingMode(getcodingMode));
    std::string oldMode = (getcodingMode == MM_CodingMode::Fast ? "Fast" : "Accurate");
    std::cout << "old CloudOutlierFilterMode: " << oldMode << std::endl;
    showError(device.setProjectorFringeCodingMode(MM_CodingMode::Fast));
    showError(device.getProjectorFringeCodingMode(getcodingMode));
    std::string newMode = (getcodingMode == MM_CodingMode::Fast ? "Fast" : "Accurate");
    std::cout << "new CloudOutlierFilterMode: " << newMode << std::endl;


    MM_PowerLevelMode getPowerLevel;
    showError(device.getProjectorPowerLevel(getPowerLevel));
    std::string oldPowerLevelMode = (getPowerLevel == MM_PowerLevelMode::High ? "High" :
                                    (getPowerLevel == MM_PowerLevelMode::Normal ? "Normal" : "Low"));
    std::cout << "old PowerLevelMode: " << oldPowerLevelMode << std::endl;
    showError(device.setProjectorPowerLevel(MM_PowerLevelMode::Low));
    showError(device.getProjectorPowerLevel(getPowerLevel));
    std::string newPowerLevelMode = (getPowerLevel == MM_PowerLevelMode::High ? "High" :
        (getPowerLevel == MM_PowerLevelMode::Normal ? "Normal" : "Low"));
    std::cout << "new PowerLevelMode: " << newPowerLevelMode << std::endl;


    MM_AntiFlickerMode getAntiFlickerMode;
    showError(device.getProjectorAntiFlickerMode(getAntiFlickerMode));
    std::string oldAntiFlickerMode = (getAntiFlickerMode == MM_AntiFlickerMode::Off ? "Off" :
        (getAntiFlickerMode == MM_AntiFlickerMode::AC50Hz ? "AC50Hz" : "AC60Hz"));
    std::cout << "old PowerLevelMode: " << oldAntiFlickerMode << std::endl;
    showError(device.setProjectorAntiFlickerMode(MM_AntiFlickerMode::AC50Hz));
    showError(device.getProjectorAntiFlickerMode(getAntiFlickerMode));
    std::string newAntiFlickerMode = (getAntiFlickerMode == MM_AntiFlickerMode::Off ? "Off" :
        (getAntiFlickerMode == MM_AntiFlickerMode::AC50Hz ? "AC50Hz" : "AC60Hz"));
    std::cout << "new PowerLevelMode: " << newAntiFlickerMode << std::endl;


    device.disconnect();
    std::cout << "Disconnected from the Mech-Eye device successfully." << std::endl;
    return 0;
}
