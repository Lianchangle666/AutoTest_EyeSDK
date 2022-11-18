#!/usr/bin/python
# -*- coding: utf-8 -*-
from Basic import caminfo
from Util import auxiliary


class ParameterFunction(caminfo.GetCameraInfo):
    def __init__(self, ip):
        super(ParameterFunction, self).__init__(ip)

        self.laser_mode_dic = {"Fast": 0, "Accurate": 1}

    def scan_3d_exposure(self, value):
        if auxiliary.show_error(self.device.set_scan_3d_exposure(value)):
            return self.device.get_scan_3d_exposure()

    def scan_3d_gain(self, value):
        if auxiliary.show_error(self.device.set_scan_3d_gain(value)):
            return self.device.get_scan_3d_gain()

    def scan_3d_roi(self, x, y, width, height):
        if auxiliary.show_error(self.device.set_scan_3d_roi(x, y, width, height)):
            return self.device.get_scan_3d_roi()

    def scan_2d_exposure_mode(self, mode):
        if auxiliary.show_error(self.device.set_scan_2d_exposure_mode(mode)):
            return self.device.get_scan_2d_exposure_mode()

    def scan_2d_exposure_time(self, value):
        if auxiliary.show_error(self.device.set_scan_2d_exposure_time(value)):
            return self.device.get_scan_2d_exposure_time()

    def scan_2d_expected_gray_value(self, value):
        if auxiliary.show_error(self.device.set_scan_2d_expected_gray_value(value)):
            return self.device.get_scan_2d_expected_gray_value()

    def scan_2d_roi(self, x, y, width, height):
        if auxiliary.show_error(self.device.set_scan_2d_roi(x, y, width, height)):
            return self.device.get_scan_2d_roi()

    def scan_2d_tone_mapping_enable(self, value):
        if auxiliary.show_error(self.device.set_scan_2d_tone_mapping_enable(value)):
            return self.device.get_scan_2d_tone_mapping_enable()

    def scan_2d_hdr_exposure_sequence(self, value):
        if auxiliary.show_error(self.device.set_scan_2d_hdr_exposure_sequence(value)):
            return self.device.get_scan_2d_hdr_exposure_sequence()

    def scan_2d_sharpen_factor(self, value):
        if auxiliary.show_error(self.device.set_scan_2d_sharpen_factor(value)):
            return self.device.get_scan_2d_sharpen_factor()

    def cloud_smooth_mode(self, mode):
        if auxiliary.show_error(self.device.set_cloud_smooth_mode(mode)):
            return self.device.get_cloud_smooth_mode()

    def cloud_outlier_filter_mode(self, mode):
        if auxiliary.show_error(self.device.set_cloud_outlier_filter_mode(mode)):
            return self.device.get_cloud_outlier_filter_mode()

    def depth_range(self, lower, upper):
        if auxiliary.show_error(self.device.set_depth_range(lower, upper)):
            return self.device.get_depth_range()

    def projector_fringe_coding_mode(self, mode):
        if auxiliary.show_error(self.device.set_projector_fringe_coding_mode(mode)):
            return self.device.get_projector_fringe_coding_mode()

    def projector_projector_power_level(self, mode):
        if auxiliary.show_error(self.device.set_projector_power_level(mode)):
            return self.device.get_projector_power_level()

    def projector_projector_anti_flicker_mode(self, mode):
        if auxiliary.show_error(self.device.set_projector_anti_flicker_mode(mode)):
            return self.device.get_projector_anti_flicker_mode()

    def uhp_fringe_coding_mode(self, mode):
        if auxiliary.show_error(self.device.set_uhp_fringe_coding_mode(mode)):
            return self.device.get_uhp_fringe_coding_mode()

    def uhp_capture_mode(self, mode):
        if auxiliary.show_error(self.device.set_uhp_capture_mode(mode)):
            return self.device.get_uhp_capture_mode()

    def laser_fringe_coding_mode(self, mode):
        try:
            param = self.device.get_laser_settings()
            if auxiliary.show_error(self.device.set_laser_settings([name for name, value in self.laser_mode_dic.items() if mode == name][0],
                                                                   param.frame_range_start(),
                                                                   param.frame_range_end(),
                                                                   param.frame_partition_count(),
                                                                   param.power_level())):

                auxiliary.show_error(self.device.set_laser_settings(mode,
                                                                    param.frame_range_start(),
                                                                    param.frame_range_end(),
                                                                    param.frame_partition_count(),
                                                                    param.power_level()))
                return self.device.get_laser_settings().fringe_coding_mode()

        except Exception as e:
            pass

    def laser_frame_range_start_end(self, start, end):
        try:
            param = self.device.get_laser_settings()
            mode = [name for name, value in self.laser_mode_dic.items() if param.fringe_coding_mode() == value][0]
            if auxiliary.show_error(self.device.set_laser_settings(mode,
                                                                   param.frame_range_start(),
                                                                   param.frame_range_end(),
                                                                   param.frame_partition_count(),
                                                                   param.power_level())):
                auxiliary.show_error(self.device.set_laser_settings(mode,
                                                                    start,
                                                                    end,
                                                                    param.frame_partition_count(),
                                                                    param.power_level()))
                get_param = self.device.get_laser_settings()
                return [get_param.frame_range_start(), get_param.frame_range_end()]

        except Exception as e:
            pass

    def laser_frame_partition_count(self, value):
        try:
            param = self.device.get_laser_settings()
            mode = [name for name, value in self.laser_mode_dic.items() if param.fringe_coding_mode() == value][0]
            if auxiliary.show_error(self.device.set_laser_settings(mode,
                                                                   param.frame_range_start(),
                                                                   param.frame_range_end(),
                                                                   param.frame_partition_count(),
                                                                   param.power_level())):
                auxiliary.show_error(self.device.set_laser_settings(mode,
                                                                    param.frame_range_start(),
                                                                    param.frame_range_end(),
                                                                    value,
                                                                    param.power_level()))

                return self.device.get_laser_settings().frame_partition_count()

        except Exception as e:
            pass

    def laser_power_level(self, value):
        try:
            param = self.device.get_laser_settings()
            mode = [name for name, value in self.laser_mode_dic.items() if param.fringe_coding_mode() == value][0]
            if auxiliary.show_error(self.device.set_laser_settings(mode,
                                                                   param.frame_range_start(),
                                                                   param.frame_range_end(),
                                                                   param.frame_partition_count(),
                                                                   param.power_level())):
                auxiliary.show_error(self.device.set_laser_settings(mode,
                                                                    param.frame_range_start(),
                                                                    param.frame_range_end(),
                                                                    param.frame_partition_count(),
                                                                    value))

                return self.device.get_laser_settings().power_level()

        except Exception as e:
            pass

if __name__ == "__main__":
    b = ParameterFunction("192.168.20.107")
    # print(b.scan_2d_hdr_exposure_sequence([1]))
    # print(b.laser_fringe_coding_mode("Fast"))
    # print(b.laser_frame_range_start_end(1, 100))
    # c = b.depth_range(1,2)
    # print(c.lower(), c.upper())
    # d = b.scan_3d_roi(0, 0, 1920, 1200)
    # print(d.x(), d.y(), d.width(), d.height())
    # e = b.scan_2d_roi(0,0,1920,1200)
    # print(b.depth_height)
    # print(e.x(), e.y(), e.width(), e.height())
    print(b.scan_3d_exposure([1]))

