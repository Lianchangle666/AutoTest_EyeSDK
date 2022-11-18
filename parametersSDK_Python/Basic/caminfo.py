#!/usr/bin/python
# -*- coding: utf-8 -*-
from MechEye import Device
from Util import auxiliary


class GetCameraInfo(object):
    def __init__(self, ip):
        self.device = Device()
        self.ip = ip
        self.name = ''
        self.color_width, self.color_height, self.depth_width, self.depth_height = 0, 0, 0, 0
        if self.find_camera():
            self.device_resolution()
            self.device_intrinsic()

    def find_camera(self):
        connect_status = auxiliary.show_error(self.device.connect_by_ip(self.ip))
        if not connect_status:
            return False
        info = self.device.get_device_info()
        self.name = auxiliary.print_device_info(info)
        return True

    def device_intrinsic(self):
        intri = self.device.get_device_intrinsic()
        auxiliary.print_matrix("Texture Camera Matrix:", intri.texture_camera_intrinsic())
        auxiliary.print_matrix("From Depth Camera to Texture Camera:", intri.depth_camera_intrinsic())
        auxiliary.print_dist_coeffs("Texture Camera Distortion Coefficients:", intri.texture_camera_intrinsic())
        auxiliary.print_dist_coeffs("Depth Camera Distortion Coefficients:", intri.depth_camera_intrinsic())

    def device_resolution(self):
        resolution = self.device.get_device_resolution()
        self.color_width, self.color_height, self.depth_width, self.depth_height = auxiliary.print_resolution(resolution)


if __name__ == "__main__":
    a = GetCameraInfo("192.168.20.64")
    a.find_camera()
    a.device_resolution()
    a.device_intrinsic()
