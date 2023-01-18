#!/usr/bin/python
# -*- coding: utf-8 -*-
from MechEye import Device


def print_dist_coeffs(coeffs):
    return "k1: {}, k2: {}, p1: {}, p2: {}, k3: {}".\
        format(
            coeffs.dist_coeffs_k1(),
            coeffs.dist_coeffs_k2(),
            coeffs.dist_coeffs_p1(),
            coeffs.dist_coeffs_p2(),
            coeffs.dist_coeffs_k3())


def print_matrix(matrix):
    return "[{}, {}\n    {}, {}]".\
        format(
            matrix.camera_matrix_fx(),
            matrix.camera_matrix_fy(),
            matrix.camera_matrix_cx(),
            matrix.camera_matrix_cy())


def show_error(status):
    if status.ok():
        return
    msg = "Error Code : {}, Error Description: {}".format(status.code(), status.description())
    print(msg)
    return msg


class FindCameraInfo():
    def __init__(self):
        self.device = Device()
        self.device_list = Device().get_device_list()

    def find_all_camera(self):
        if len(self.device_list) != 0:
            return [(str(info.model) + ' -> ' + str(info.ip)) for n, info in enumerate(self.device_list)]
        return []

    def connect_camera_from_device_list(self, index):
        status = self.device.connect(self.device_list[index])
        msg = show_error(status)
        if msg is None:
            return "Connect Mech-Eye Successfully."
        return msg

    def disconnect_from_device(self):
        self.device.disconnect()
        return "Disconnect from Mech-Eye Successfully."

    def connect_camera_from_device_ip(self, ipaddress):
        status = self.device.connect_by_ip(ipaddress)
        msg = show_error(status)
        if msg is None:
            return "Connect Mech-Eye Successfully."
        return msg

    def get_device_info_signal(self):
        msg = self.device.get_device_info()
        return [msg.model, msg.id, msg.ip, msg.firmware_version, msg.hardware_version, msg.port]

    def get_device_intrinsic_signal(self):
        msg = self.device.get_device_intrinsic()
        camera_dist_coeffs = print_dist_coeffs(msg.texture_camera_intrinsic())
        depth_dist_coeffs = print_dist_coeffs(msg.depth_camera_intrinsic())
        camera_matrix = print_matrix(msg.texture_camera_intrinsic())
        depth_matrix = print_matrix(msg.depth_camera_intrinsic())
        return [camera_dist_coeffs, depth_dist_coeffs, camera_matrix, depth_matrix]

    def get_device_resolution_signal(self):
        msg = self.device.get_device_resolution()
        return [msg.color_width(), msg.color_height(), msg.depth_width(), msg.depth_height()]

    def scan_2d_exposure_mode_signal(self, modename):
        mode_dic = {"Timed": 0, "Auto": 1, "HDR": 2, "Flash": 3}
        status = self.device.set_scan_2d_exposure_mode(modename)
        msg = show_error(status)
        if msg is None:
            get_value = self.device.get_scan_2d_exposure_mode()
            return [name for name, value in mode_dic.items() if value == get_value][0]
        return msg

    def scan_2d_exposure_time(self, exporetime):
        status = self.device.set_scan_2d_exposure_time(exporetime)
        msg = show_error(status)
        if msg is None:
            get_value = self.device.get_scan_2d_exposure_time()
            return get_value
        return msg

    def scan_2d_expected_gray_value_signal(self, grayvalue):
        status = self.device.set_scan_2d_expected_gray_value(grayvalue)
        msg = show_error(status)
        if msg is None:
            get_value = self.device.get_scan_2d_expected_gray_value()
            return get_value
        return msg

    def scan_2d_tone_mapping_enable_signal(self, boolvalue):
        status = self.device.set_scan_2d_tone_mapping_enable(boolvalue)
        msg = show_error(status)
        if msg is None:
            get_value = self.device.get_scan_2d_tone_mapping_enable()
            return get_value
        return msg

    def scan_2d_sharpen_signal(self, value):
        status = self.device.set_scan_2d_sharpen_factor(value)
        msg = show_error(status)
        if msg is None:
            get_value = self.device.get_scan_2d_sharpen_factor()
            return get_value
        return msg

    def scan_2d_roi_signal(self, x, y, width, height):
        status = self.device.set_scan_2d_roi(x, y, width, height)
        msg = show_error(status)
        if msg is None:
            get_value = self.device.get_scan_2d_roi()
            return [get_value.x(), get_value.y(), get_value.width(), get_value.height()]
        return msg

    def scan_3d_gain_signal(self, value):
        status = self.device.set_scan_3d_gain(value)
        msg = show_error(status)
        if msg is None:
            get_value = self.device.get_scan_3d_gain()
            return get_value
        return msg

    def scan_3d_roi_signal(self, x, y, width, height):
        status = self.device.set_scan_3d_roi(x, y, width, height)
        msg = show_error(status)
        if msg is None:
            get_value = self.device.get_scan_3d_roi()
            return [get_value.x(), get_value.y(), get_value.width(), get_value.height()]
        return msg

    def depth_range_signal(self, lower, upper):
        status = self.device.set_depth_range(lower, upper)
        msg = show_error(status)
        if msg is None:
            get_value = self.device.get_depth_range()
            return [get_value.lower(), get_value.upper()]
        return msg

    def fringe_contrast_threshold_signal(self, value):
        status = self.device.set_fringe_contrast_threshold(value)
        msg = show_error(status)
        if msg is None:
            get_value = self.device.get_fringe_contrast_threshold()
            return get_value
        return msg

    def fringe_min_threshold_signal(self, value):
        status = self.device.set_fringe_min_threshold(value)
        msg = show_error(status)
        if msg is None:
            get_value = self.device.get_fringe_min_threshold()
            return get_value
        return msg

    def cloud_outlier_filter_mode_signal(self, value):
        dic = {0: "Off", 1: "Weak", 2: "Normal"}
        status = self.device.set_cloud_outlier_filter_mode(value)
        msg = show_error(status)
        if msg is None:
            get_value = self.device.get_cloud_outlier_filter_mode()
            return dic[get_value]
        return msg

    def cloud_smooth_mode_signal(self, value):
        dic = {0: "Off", 1: "Normal", 2: "Weak", 3: "Strong"}
        status = self.device.set_cloud_smooth_mode(value)
        msg = show_error(status)
        if msg is None:
            get_value = self.device.get_cloud_smooth_mode()
            return dic[get_value]
        return msg

    def projector_fringe_coding_mode_signal(self, value):
        dic = {0: "Fast", 1: "Accurate"}
        status = self.device.set_projector_fringe_coding_mode(value)
        msg = show_error(status)
        if msg is None:
            get_value = self.device.get_projector_fringe_coding_mode()
            return dic[get_value]
        return msg

    def projector_anti_flicker_mode_signal(self, value):
        dic = {0: "Off", 1: "AC50Hz", 2: "AC60Hz"}
        status = self.device.set_projector_anti_flicker_mode(value)
        msg = show_error(status)
        if msg is None:
            get_value = self.device.get_projector_anti_flicker_mode()
            return dic[get_value]
        return msg

    def scan_2d_hdr_exposure_sequence_signal(self, timelist):
        status = self.device.set_scan_2d_hdr_exposure_sequence(timelist)
        msg = show_error(status)
        if msg is None:
            get_value = self.device.get_scan_2d_hdr_exposure_sequence()
            return get_value
        return msg

    def scan_3d_exposure_signal(self, timelist):
        status = self.device.set_scan_3d_exposure(timelist)
        msg = show_error(status)
        if msg is None:
            get_value = self.device.get_scan_3d_exposure()
            return get_value
        return msg

    def projector_power_level_signal(self, value):
        dic = {0: "High", 1: "Normal", 2: "Low"}
        status = self.device.set_projector_power_level(value)
        msg = show_error(status)
        if msg is None:
            get_value = self.device.get_projector_power_level()
            return dic[get_value]
        return msg

    def laser_settings_signal(self, mode, start, end, count, level):
        dic = {0: "Fast", 1: "Accurate"}
        status = self.device.set_laser_settings(mode, start, end, count, level)
        msg = show_error(status)
        if msg is None:
            get_value = self.device.get_laser_settings()
            return [dic[get_value.fringe_coding_mode()], get_value.frame_range_start(),
                    get_value.frame_range_end(), get_value.frame_partition_count(),
                    get_value.power_level()]
        return msg

    def uhp_settings_signal(self, capture_mode, fringe_coding_mode):
        uhp_capture_mode_dic = {0: "Camera1", 1: "Camera2", 2: "Merge"}
        uhp_fringe_coding_mode_dic = {0: "Fast", 1: "Accurate"}
        print(capture_mode, fringe_coding_mode)
        print('666666')
        status1 = self.device.set_uhp_capture_mode(capture_mode)
        status2 = self.device.set_uhp_fringe_coding_mode(fringe_coding_mode)
        msg1 = show_error(status1)
        msg2 = show_error(status2)
        if msg1 is None and msg2 is None:
            get_value1 = self.device.get_uhp_capture_mode()
            get_value2 = self.device.get_uhp_fringe_coding_mode()

            return [uhp_capture_mode_dic[get_value1],
                    uhp_fringe_coding_mode_dic[get_value2]]
        return msg1

    def current_user_sets(self, usersets):
        status = self.device.set_current_user_set(usersets)
        msg = show_error(status)
        if msg is None:
            get_user_set = self.device.get_current_user_set()
            return ''.join(get_user_set)
        return msg

    def all_user_sets(self):
        msg = self.device.get_all_user_sets()
        return "All User Sets: " + ', '.join(msg)

    def delete_user(self, uersets):
        status = self.device.delete_user_set(uersets)
        msg = show_error(status)
        return msg

    def add_user(self, uersets):
        status = self.device.add_user_set(uersets)
        msg = show_error(status)
        return msg


if __name__ == '__main__':
    a = FindCameraInfo()
    print(a.connect_camera_from_device_ip('192.168.20.157'))
    print(a.uhp_settings_signal('Camera1', 'Fast'))
    # a.scan_2d_exposure_mode('Flash')
    # for i in range(1, 0):
    #     print(i)
    # print(a.all_user_sets())