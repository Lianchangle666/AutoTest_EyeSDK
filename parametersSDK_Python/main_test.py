#!/usr/bin/python
# -*- coding: utf-8 -*-
import pytest
from Basic import caminfo


ip = "192.168.20.211"
msg = caminfo.GetCameraInfo(ip)

depth_width = msg.depth_width
depth_height = msg.depth_height
color_width = msg.color_width
color_height = msg.color_height
camera_name = msg.name
print(">>>>>>>" + camera_name + "<<<<<<<<")

try:

    if "LSR" in camera_name or "Laser" in camera_name or "DEEP" in camera_name:
        pytest.main(['-vs', './Case/test_laser_parame.py',
                     '--report={} 测试报告.html'.format(camera_name),
                     '--title={}参数测试报告'.format(camera_name),
                     '--tester=连常乐',
                     '--desc=相机测试报告',
                     '--template=2'])

    elif "UHP" in camera_name:
        pytest.main(['-vs', './Case/test_uhp_parame.py',
                     '--report={} 测试报告.html'.format(camera_name),
                     '--title={} 参数测试报告'.format(camera_name),
                     '--tester=连常乐',
                     '--desc=相机测试报告',
                     '--template=2'])

except Exception as e:
    pass
else:
    pytest.main(['-vs', './Case/test_parameters.py',
                 '--report={} 测试报告.html'.format(camera_name, camera_name),
                 '--title={} 参数测试报告'.format(camera_name),
                 '--tester=连常乐',
                 '--desc=相机测试报告',
                 '--template=2'])