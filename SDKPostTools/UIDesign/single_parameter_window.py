#!/usr/bin/python
# -*- coding: utf-8 -*-
import sys
import qdarkstyle
import threading
from PyQt5 import QtCore
from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *
from ParametersPackag.find_camera_info import FindCameraInfo
from main import img_image


class SingleParameterWindow(QWidget):
    def __init__(self):
        super(SingleParameterWindow, self).__init__()
        self.setWindowTitle('Mech-Eye POSTER')
        self.resize(300, 100)
        self.setWindowFlags(QtCore.Qt.WindowCloseButtonHint)
        self.connect_info = FindCameraInfo()
        self.device_list = self.connect_info.find_all_camera()

        self.scan_2d_hdr_exposure_sequence_spin_box_list = []
        self.scan_3d_exposure_spin_box_list = []

        self.main_widget()
        self.main_layout()
        self.main_style()
        self.main_value()

    def main_layout(self):
        g_layout = QGridLayout(self)
        g_layout.setSpacing(8)
        g_layout.addWidget(self.title_image(), 0, 0, 1, 3)
        g_layout.addWidget(self.search_camera(), 1, 0, 1, 2)
        g_layout.addWidget(self.camera_information(), 1, 2, 1, 1)

        g_layout.addWidget(self.camera_log(), 0, 4, 6, 2)
        g_layout.addWidget(self.camera_parameter(), 2, 0, 1, 3)
        g_layout.addWidget(self.range_parameter(), 3, 0, 1, 3)

        g_layout.addWidget(self.laser_camera_parameter(), 4, 0, 1, 1)
        g_layout.addWidget(self.uhp_camera_parameter(), 4, 1, 1, 1)
        g_layout.addWidget(self.user_sets(), 4, 2, 1, 1)

        g_layout.addWidget(self.start_close(), 5, 0, 1, 3)
        self.setLayout(g_layout)

    def main_widget(self):
        self.image_lable = QLabel()
        self.connect_by_choose_camera_label = QLabel('ConnectCameraByChoose')
        self.connect_by_choose_camera_combox = QComboBox()
        self.connect_by_choose_camera_button = QPushButton("Connect")
        self.connect_by_ip_camera_label = QLabel('ConnectCameraByIP')
        self.connect_by_ip_camera_line_edit = QLineEdit()
        self.connect_by_ip_camera_button = QPushButton("Connect")

        self.get_device_info_button = QPushButton("get_device_info")
        self.get_device_intrinsic_button = QPushButton("get_device_intrinsic")
        self.get_device_resolution_button = QPushButton("get_device_resolution")

        self.camera_message_edit = QTextEdit()
        self.scan_2d_exposure_mode_checkbox = QCheckBox("scan_2d_exposure_mode")
        self.scan_2d_exposure_mode_combox = QComboBox()

        self.scan_2d_exposure_time_checkbox = QCheckBox("scan_2d_exposure_time")
        self.scan_2d_exposure_time_spinbox = QDoubleSpinBox()

        self.scan_2d_hdr_exposure_sequence_checkbox = QCheckBox("scan_2d_hdr_exposure_sequence")
        self.scan_2d_hdr_exposure_sequence_spinbox = QSpinBox()
        self.add_2d_hdr_exposure_sequence_button = QPushButton('+')
        self.sub_2d_hdr_exposure_sequence_button = QPushButton('-')

        self.scan_2d_expected_gray_checkbox = QCheckBox("scan_2d_expected_gray")
        self.scan_2d_expected_gray_spinbox = QSpinBox()

        self.scan_2d_tone_mapping_checkbox = QCheckBox("scan_2d_tone_mapping")
        self.scan_2d_tone_mapping_spinbox = QComboBox()

        self.scan_2d_sharpen_factor_checkbox = QCheckBox("scan_2d_sharpen_factor")
        self.scan_2d_sharpen_factor_spinbox = QDoubleSpinBox()

        self.scan_3d_exposure_checkbox = QCheckBox("scan_3d_exposure")
        self.scan_3d_exposure_spinbox = QSpinBox()
        self.add_scan_3d_exposure_button = QPushButton('+')
        self.sub_scan_3d_exposure_button = QPushButton('-')

        self.scan_3d_gain_checkbox = QCheckBox("scan_3d_gain")
        self.scan_3d_gain_spinbox = QDoubleSpinBox()

        self.fringe_contrast_threshold_checkbox = QCheckBox("fringe_contrast_threshold")
        self.fringe_contrast_threshold_spinbox = QSpinBox()

        self.fringe_min_threshold_checkbox = QCheckBox("fringe_min_threshold")
        self.fringe_min_threshold_spinbox = QSpinBox()

        self.cloud_outlier_filter_mode_checkbox = QCheckBox("cloud_outlier_filter_mode")
        self.cloud_outlier_filter_mode_spinbox = QComboBox()

        self.cloud_smooth_mode_checkbox = QCheckBox("cloud_smooth_mode")
        self.cloud_smooth_mode_spinbox = QComboBox()

        self.projector_fringe_coding_mode_checkbox = QCheckBox("projector_fringe_coding_mode")
        self.projector_fringe_coding_mode_spinbox = QComboBox()

        self.projector_power_level_checkbox = QCheckBox("projector_power_level")
        self.projector_power_level_spinbox = QComboBox()

        self.projector_anti_flicker_mode_checkbox = QCheckBox("projector_anti_flicker_mode")
        self.projector_anti_flicker_mode_spinbox = QComboBox()

        self.scan_2d_roi_checkbox = QCheckBox("scan_2d_roi")
        self.scan_2d_roi_x_lable = QLabel('X')
        self.scan_2d_roi_x_spinbox = QSpinBox()
        self.scan_2d_roi_y_lable = QLabel('Y')
        self.scan_2d_roi_y_spinbox = QSpinBox()
        self.scan_2d_roi_w_lable = QLabel('Width')
        self.scan_2d_roi_w_spinbox = QSpinBox()
        self.scan_2d_roi_h_lable = QLabel('Hight')
        self.scan_2d_roi_h_spinbox = QSpinBox()

        self.scan_3d_roi_checkbox = QCheckBox("scan_3d_roi")
        self.scan_3d_roi_x_lable = QLabel('X')
        self.scan_3d_roi_x_spinbox = QSpinBox()
        self.scan_3d_roi_y_lable = QLabel('Y')
        self.scan_3d_roi_y_spinbox = QSpinBox()
        self.scan_3d_roi_w_lable = QLabel('Width')
        self.scan_3d_roi_w_spinbox = QSpinBox()
        self.scan_3d_roi_h_lable = QLabel('Hight')
        self.scan_3d_roi_h_spinbox = QSpinBox()

        self.depth_range_checkbox = QCheckBox("depth_range")
        self.depth_range_upper_lable = QLabel('Upper')
        self.depth_range_upper_spinbox = QSpinBox()
        self.depth_range_lower_lable = QLabel('lower')
        self.depth_range_lower_spinbox = QSpinBox()

        self.projector_fringe_coding_mode_checkbox = QCheckBox("projector_fringe_coding_mode")
        self.projector_fringe_coding_mode_spinbox = QComboBox()

        self.projector_power_level_checkbox = QCheckBox("projector_power_level")
        self.projector_power_level_spinbox = QComboBox()

        self.projector_anti_flicker_mode_checkbox = QCheckBox("projector_anti_flicker_mode")
        self.projector_anti_flicker_mode_spinbox = QComboBox()

        # -------------------Laser--------------------------------
        self.laser_checkbox = QCheckBox("LaserSetting")

        self.fringe_coding_mode_checkbox = QLabel("fringe_coding_mode")
        self.fringe_coding_mode_spinbox = QComboBox()

        self.frame_range_start_checkbox = QLabel("frame_range_start")
        self.frame_range_start_spinbox = QSpinBox()

        self.frame_range_end_checkbox = QLabel("frame_range_end")
        self.frame_range_end_spinbox = QSpinBox()

        self.frame_partition_count_checkbox = QLabel("frame_partition_count")
        self.frame_partition_count_spinbox = QSpinBox()

        self.power_level_checkbox = QLabel("power_level")
        self.power_level_spinbox = QSpinBox()
        # --------------------------------------------------------

        # -------------------UHP--------------------------------
        self.uhp_capture_mode_checkbox = QLabel("uhp_capture_mode")
        self.uhp_capture_mode_spinbox = QComboBox()

        self.uhp_fringe_coding_mode_checkbox = QLabel("uhp_fringe_coding_mode")
        self.uhp_fringe_coding_mode_spinbox = QComboBox()

        self.get_all_user_sets_checkbox = QPushButton("get_all_user_sets")

        self.get_current_user_sets_checkbox = QCheckBox("set_current_user_sets")
        self.get_current_user_sets_spinbox = QLineEdit()

        self.delete_user_set_checkbox = QCheckBox("delete_user_set")
        self.delete_user_set_spinbox = QLineEdit()

        self.add_user_set_checkbox = QCheckBox("add_user_set")
        self.add_user_set_spinbox = QLineEdit()

        self.post_button = QPushButton("Post")
        self.close_button = QPushButton("Close")

        self.widget_dic = {
            self.scan_2d_exposure_mode_checkbox: self.scan_2d_exposure_mode_combox,
            self.scan_2d_exposure_time_checkbox: self.scan_2d_exposure_time_spinbox,
            # self.scan_2d_hdr_exposure_sequence_checkbox: self.scan_2d_hdr_exposure_sequence_spinbox,
            self.scan_2d_expected_gray_checkbox: self.scan_2d_expected_gray_spinbox,
            self.scan_2d_tone_mapping_checkbox: self.scan_2d_tone_mapping_spinbox,
            self.scan_2d_sharpen_factor_checkbox: self.scan_2d_sharpen_factor_spinbox,
            # self.scan_3d_exposure_checkbox: self.scan_3d_exposure_spinbox,
            self.scan_3d_gain_checkbox: self.scan_3d_gain_spinbox,
            self.fringe_contrast_threshold_checkbox: self.fringe_contrast_threshold_spinbox,
            self.fringe_min_threshold_checkbox: self.fringe_min_threshold_spinbox,
            self.cloud_outlier_filter_mode_checkbox: self.cloud_outlier_filter_mode_spinbox,
            self.cloud_smooth_mode_checkbox: self.cloud_smooth_mode_spinbox,
            self.projector_fringe_coding_mode_checkbox: self.projector_fringe_coding_mode_spinbox,
            self.projector_power_level_checkbox: self.projector_power_level_spinbox,
            self.projector_anti_flicker_mode_checkbox: self.projector_anti_flicker_mode_spinbox,

        }

        self.laser_dic = {
            self.fringe_coding_mode_checkbox: self.fringe_coding_mode_spinbox,
            self.frame_partition_count_checkbox: self.frame_partition_count_spinbox,
            self.frame_range_start_checkbox: self.frame_range_start_spinbox,
            self.frame_range_end_checkbox: self.frame_range_end_spinbox,
            self.power_level_checkbox: self.power_level_spinbox,
        }

        self.uhp_dic = {
            self.uhp_capture_mode_checkbox: self.uhp_capture_mode_spinbox,
            self.uhp_fringe_coding_mode_checkbox: self.uhp_fringe_coding_mode_spinbox,
        }

        self.user_sets_dic = {
            # self.get_all_user_sets_checkbox: self.get_all_user_sets_spinbox,
            self.get_current_user_sets_checkbox: self.get_current_user_sets_spinbox,
            self.delete_user_set_checkbox: self.delete_user_set_spinbox,
            self.add_user_set_checkbox: self.add_user_set_spinbox,

        }

    def main_style(self):
        self.connect_by_choose_camera_label.setFixedSize(QtCore.QSize(150, 20))
        self.connect_by_choose_camera_combox.setFixedSize(QtCore.QSize(400, 20))
        self.connect_by_choose_camera_button.setFixedSize(QtCore.QSize(70, 20))
        self.connect_by_ip_camera_label.setFixedSize(QtCore.QSize(150, 20))
        self.connect_by_ip_camera_line_edit.setFixedSize(QtCore.QSize(400, 20))
        self.connect_by_ip_camera_button.setFixedSize(QtCore.QSize(70, 20))
        self.camera_message_edit.setFixedSize(QtCore.QSize(400, 800))
        self.post_button.setFixedSize(QtCore.QSize(120, 25))
        self.close_button.setFixedSize(QtCore.QSize(120, 25))

        self.get_device_info_button.setFixedSize(QtCore.QSize(200, 20))
        self.get_device_resolution_button.setFixedSize(QtCore.QSize(200, 20))
        self.get_device_intrinsic_button.setFixedSize(QtCore.QSize(200, 20))

        self.scan_2d_exposure_mode_combox.setFixedSize(QtCore.QSize(70, 20))
        self.scan_2d_exposure_time_spinbox.setFixedSize(QtCore.QSize(70, 20))
        self.scan_2d_expected_gray_spinbox.setFixedSize(QtCore.QSize(70, 20))
        self.scan_2d_tone_mapping_spinbox.setFixedSize(QtCore.QSize(70, 20))
        self.scan_2d_sharpen_factor_spinbox.setFixedSize(QtCore.QSize(70, 20))
        self.scan_3d_gain_spinbox.setFixedSize(QtCore.QSize(70, 20))
        self.fringe_contrast_threshold_spinbox.setFixedSize(QtCore.QSize(70, 20))
        self.fringe_min_threshold_spinbox.setFixedSize(QtCore.QSize(70, 20))
        self.cloud_smooth_mode_spinbox.setFixedSize(QtCore.QSize(70, 20))
        self.cloud_outlier_filter_mode_spinbox.setFixedSize(QtCore.QSize(70, 20))
        self.projector_fringe_coding_mode_spinbox.setFixedSize(QtCore.QSize(70, 20))
        self.projector_power_level_spinbox.setFixedSize(QtCore.QSize(70, 20))
        self.projector_anti_flicker_mode_spinbox.setFixedSize(QtCore.QSize(70, 20))

        self.add_2d_hdr_exposure_sequence_button.setFixedSize(QtCore.QSize(50, 20))
        self.sub_2d_hdr_exposure_sequence_button.setFixedSize(QtCore.QSize(50, 20))
        self.add_scan_3d_exposure_button.setFixedSize(QtCore.QSize(50, 20))
        self.sub_scan_3d_exposure_button.setFixedSize(QtCore.QSize(50, 20))
        self.scan_2d_hdr_exposure_sequence_checkbox.setFixedSize(QtCore.QSize(200, 20))
        self.scan_3d_exposure_checkbox.setFixedSize(QtCore.QSize(200, 20))

        self.scan_2d_roi_checkbox.setFixedSize(QtCore.QSize(90, 25))
        self.scan_2d_roi_x_lable.setFixedSize(QtCore.QSize(15, 25))
        self.scan_2d_roi_x_spinbox.setFixedSize(QtCore.QSize(60, 25))
        self.scan_2d_roi_y_lable.setFixedSize(QtCore.QSize(15, 25))
        self.scan_2d_roi_y_spinbox.setFixedSize(QtCore.QSize(60, 25))
        self.scan_2d_roi_w_lable.setFixedSize(QtCore.QSize(50, 25))
        self.scan_2d_roi_w_spinbox.setFixedSize(QtCore.QSize(60, 25))
        self.scan_2d_roi_h_lable.setFixedSize(QtCore.QSize(50, 25))
        self.scan_2d_roi_h_spinbox.setFixedSize(QtCore.QSize(60, 25))

        self.scan_3d_roi_checkbox.setFixedSize(QtCore.QSize(90, 25))
        self.scan_3d_roi_x_lable.setFixedSize(QtCore.QSize(15, 25))
        self.scan_3d_roi_x_spinbox.setFixedSize(QtCore.QSize(60, 25))
        self.scan_3d_roi_y_lable.setFixedSize(QtCore.QSize(15, 25))
        self.scan_3d_roi_y_spinbox.setFixedSize(QtCore.QSize(60, 25))
        self.scan_3d_roi_w_lable.setFixedSize(QtCore.QSize(50, 25))
        self.scan_3d_roi_w_spinbox.setFixedSize(QtCore.QSize(60, 25))
        self.scan_3d_roi_h_lable.setFixedSize(QtCore.QSize(50, 25))
        self.scan_3d_roi_h_spinbox.setFixedSize(QtCore.QSize(60, 25))

        self.depth_range_upper_lable.setFixedSize(QtCore.QSize(40, 25))
        self.depth_range_lower_lable.setFixedSize(QtCore.QSize(40, 25))

        self.get_all_user_sets_checkbox.setFixedSize(QtCore.QSize(150, 20))
        self.get_current_user_sets_checkbox.setFixedSize(QtCore.QSize(150, 20))
        self.delete_user_set_checkbox.setFixedSize(QtCore.QSize(150, 20))
        self.add_user_set_checkbox.setFixedSize(QtCore.QSize(150, 20))

        self.uhp_capture_mode_checkbox.setFixedSize(QtCore.QSize(140, 20))
        self.uhp_capture_mode_spinbox.setFixedSize(QtCore.QSize(70, 20))
        self.uhp_fringe_coding_mode_checkbox.setFixedSize(QtCore.QSize(140, 20))
        self.uhp_fringe_coding_mode_spinbox.setFixedSize(QtCore.QSize(70, 20))

        self.fringe_coding_mode_checkbox.setFixedSize(QtCore.QSize(120, 20))
        self.fringe_coding_mode_spinbox.setFixedSize(QtCore.QSize(70, 20))
        self.frame_partition_count_checkbox.setFixedSize(QtCore.QSize(120, 20))
        self.frame_partition_count_spinbox.setFixedSize(QtCore.QSize(70, 20))
        self.frame_range_start_spinbox.setFixedSize(QtCore.QSize(70, 20))
        self.frame_range_end_spinbox.setFixedSize(QtCore.QSize(70, 20))
        self.power_level_spinbox.setFixedSize(QtCore.QSize(70, 20))

        self.frame_partition_count_spinbox.setRange(0, 10000000)
        self.frame_range_end_spinbox.setRange(0, 10000000)
        self.frame_range_start_spinbox.setRange(0, 10000000)
        self.power_level_spinbox.setRange(0, 10000000)

        self.scan_2d_exposure_time_spinbox.setRange(0, 10000000)
        self.scan_2d_expected_gray_spinbox.setRange(0, 10000000)
        self.scan_2d_roi_x_spinbox.setRange(0, 10000000)
        self.scan_2d_roi_y_spinbox.setRange(0, 10000000)
        self.scan_2d_roi_w_spinbox.setRange(0, 10000000)
        self.scan_2d_roi_h_spinbox.setRange(0, 10000000)
        self.scan_3d_roi_x_spinbox.setRange(0, 10000000)
        self.scan_3d_roi_y_spinbox.setRange(0, 10000000)
        self.scan_3d_roi_w_spinbox.setRange(0, 10000000)
        self.scan_3d_roi_h_spinbox.setRange(0, 10000000)
        self.depth_range_lower_spinbox.setRange(0, 10000000)
        self.depth_range_upper_spinbox.setRange(0, 10000000)

        self.fringe_min_threshold_spinbox.setRange(0, 10000000)
        self.fringe_contrast_threshold_spinbox.setRange(0, 10000000)

        self.scan_2d_sharpen_factor_spinbox.setSingleStep(0.1)
        self.scan_2d_sharpen_factor_spinbox.setDecimals(1)
        self.scan_2d_sharpen_factor_spinbox.setRange(0, 10000000)

        self.scan_3d_gain_spinbox.setSingleStep(0.1)
        self.scan_3d_gain_spinbox.setDecimals(1)
        self.scan_3d_gain_spinbox.setRange(0, 10000000)

        self.scan_2d_exposure_time_spinbox.setSingleStep(0.1)
        self.scan_2d_exposure_time_spinbox.setDecimals(1)
        self.scan_2d_exposure_time_spinbox.setSuffix(' ms')
        self.scan_2d_exposure_time_spinbox.setRange(0, 10000000)
        self.camera_message_edit.setReadOnly(True)
        self.connect_by_ip_camera_line_edit.setInputMask('000.000.000.000;')

    def title_image(self):
        group_box = QGroupBox('', self)
        self.image_lable.setPixmap(QPixmap(img_image).scaled(700, 70))
        v_layout = QVBoxLayout(group_box)
        v_layout.addWidget(self.image_lable)
        return group_box

    def camera_information(self):
        group_box = QGroupBox('CameraInformation', self)
        v_layout = QVBoxLayout(group_box)

        v_layout.addWidget(self.get_device_info_button)
        v_layout.addWidget(self.get_device_intrinsic_button)
        v_layout.addWidget(self.get_device_resolution_button)

        return group_box

    def search_camera(self):
        group_box = QGroupBox('FindAndConnectCamera', self)
        v_layout = QVBoxLayout(group_box)

        h1_layout = QHBoxLayout()
        h1_layout.addWidget(self.connect_by_choose_camera_label)
        h1_layout.addWidget(self.connect_by_choose_camera_combox)
        h1_layout.addWidget(self.connect_by_choose_camera_button)

        h2_layout = QHBoxLayout()
        h2_layout.addWidget(self.connect_by_ip_camera_label)
        h2_layout.addWidget(self.connect_by_ip_camera_line_edit)
        h2_layout.addWidget(self.connect_by_ip_camera_button)

        h3_layout = QHBoxLayout()
        h3_layout.addWidget(self.get_device_info_button)
        h3_layout.addWidget(self.get_device_intrinsic_button)
        h3_layout.addWidget(self.get_device_resolution_button)

        v_layout.addLayout(h1_layout)
        v_layout.addLayout(h2_layout)
        v_layout.addLayout(h3_layout)

        return group_box

    def camera_parameter(self):
        group_box = QGroupBox('CameraParameter', self)
        v_layout = QVBoxLayout(group_box)   # all

        h_layout = QHBoxLayout()
        v1_layout = QVBoxLayout()
        v2_layout = QVBoxLayout()
        v3_layout = QVBoxLayout()

        self.v4_layout = QHBoxLayout()
        self.v5_layout = QHBoxLayout()

        case_num = len(self.widget_dic)
        n = 0
        for checkbox, valuebox in self.widget_dic.items():
            n += 1
            if n <= int(case_num/3):
                h1_layout = QHBoxLayout()
                h1_layout.addWidget(checkbox)
                h1_layout.addWidget(valuebox)
                v1_layout.addLayout(h1_layout)
            elif int(case_num/3) < n <= int(case_num/3) * 2:
                h2_layout = QHBoxLayout()
                h2_layout.addWidget(checkbox)
                h2_layout.addWidget(valuebox)
                v2_layout.addLayout(h2_layout)
            else:
                h3_layout = QHBoxLayout()
                h3_layout.addWidget(checkbox)
                h3_layout.addWidget(valuebox)
                v3_layout.addLayout(h3_layout)

        self.v4_layout.addWidget(self.scan_2d_hdr_exposure_sequence_checkbox)
        self.v4_layout.addWidget(self.add_2d_hdr_exposure_sequence_button)
        self.v4_layout.addWidget(self.sub_2d_hdr_exposure_sequence_button)

        self.v5_layout.addWidget(self.scan_3d_exposure_checkbox)
        self.v5_layout.addWidget(self.add_scan_3d_exposure_button)
        self.v5_layout.addWidget(self.sub_scan_3d_exposure_button)

        v1_layout.setAlignment(Qt.AlignLeft)
        v2_layout.setAlignment(Qt.AlignLeft)
        v3_layout.setAlignment(Qt.AlignLeft)
        self.v4_layout.setAlignment(Qt.AlignLeft)
        self.v5_layout.setAlignment(Qt.AlignLeft)

        h_layout.addLayout(v1_layout)
        h_layout.addLayout(v2_layout)
        h_layout.addLayout(v3_layout)

        v_layout.addLayout(h_layout)
        v_layout.addLayout(self.v4_layout)
        v_layout.addLayout(self.v5_layout)

        return group_box

    def range_parameter(self):
        group_box = QGroupBox('RangeParameter', self)
        v_layout = QVBoxLayout(group_box)

        h1_layout = QHBoxLayout()
        h1_layout.addWidget(self.scan_2d_roi_checkbox)
        h1_layout.addWidget(self.scan_2d_roi_x_lable)
        h1_layout.addWidget(self.scan_2d_roi_x_spinbox)
        h1_layout.addWidget(self.scan_2d_roi_y_lable)
        h1_layout.addWidget(self.scan_2d_roi_y_spinbox)
        h1_layout.addWidget(self.scan_2d_roi_w_lable)
        h1_layout.addWidget(self.scan_2d_roi_w_spinbox)
        h1_layout.addWidget(self.scan_2d_roi_h_lable)
        h1_layout.addWidget(self.scan_2d_roi_h_spinbox)

        # h3_layout = QHBoxLayout()
        h1_layout.addWidget(self.depth_range_checkbox)
        h1_layout.addWidget(self.depth_range_upper_lable)
        h1_layout.addWidget(self.depth_range_upper_spinbox)
        h1_layout.addWidget(self.depth_range_lower_lable)
        h1_layout.addWidget(self.depth_range_lower_spinbox)

        h2_layout = QHBoxLayout()
        h2_layout.addWidget(self.scan_3d_roi_checkbox)
        h2_layout.addWidget(self.scan_3d_roi_x_lable)
        h2_layout.addWidget(self.scan_3d_roi_x_spinbox)
        h2_layout.addWidget(self.scan_3d_roi_y_lable)
        h2_layout.addWidget(self.scan_3d_roi_y_spinbox)
        h2_layout.addWidget(self.scan_3d_roi_w_lable)
        h2_layout.addWidget(self.scan_3d_roi_w_spinbox)
        h2_layout.addWidget(self.scan_3d_roi_h_lable)
        h2_layout.addWidget(self.scan_3d_roi_h_spinbox)

        h1_layout.setAlignment(Qt.AlignLeft)
        h2_layout.setAlignment(Qt.AlignLeft)

        v_layout.addLayout(h1_layout)
        v_layout.addLayout(h2_layout)
        # v_layout.addLayout(h3_layout)

        return group_box

    def laser_camera_parameter(self):
        self.laser_group_box = QGroupBox('&LaserSetting', self)
        self.laser_group_box.setCheckable(True)
        self.laser_group_box.setChecked(False)

        self.laser_h_layout = QHBoxLayout(self.laser_group_box)
        v1_layout = QVBoxLayout()
        v2_layout = QVBoxLayout()

        case_num = len(self.laser_dic)
        n = 0
        for checkbox, valuebox in self.laser_dic.items():
            n += 1
            if n <= int(case_num/2):
                h1_layout = QHBoxLayout()
                h1_layout.addWidget(checkbox)
                h1_layout.addWidget(valuebox)
                v1_layout.addLayout(h1_layout)
            else:
                h2_layout = QHBoxLayout()
                h2_layout.addWidget(checkbox)
                h2_layout.addWidget(valuebox)
                v2_layout.addLayout(h2_layout)
        self.laser_h_layout.addLayout(v1_layout)
        self.laser_h_layout.addLayout(v2_layout)
        return self.laser_group_box

    def uhp_camera_parameter(self):
        self.uhp_group_box = QGroupBox('UHPSetting', self)
        self.uhp_group_box.setCheckable(True)
        self.uhp_group_box.setChecked(False)

        v_layout = QVBoxLayout(self.uhp_group_box)
        v1_layout = QVBoxLayout()
        v2_layout = QVBoxLayout()

        case_num = len(self.uhp_dic)
        n = 0
        for checkbox, valuebox in self.uhp_dic.items():
            n += 1
            if n <= int(case_num / 2):
                h1_layout = QHBoxLayout()
                h1_layout.addWidget(checkbox)
                h1_layout.addWidget(valuebox)
                v1_layout.addLayout(h1_layout)
            else:
                h2_layout = QHBoxLayout()
                h2_layout.addWidget(checkbox)
                h2_layout.addWidget(valuebox)
                v2_layout.addLayout(h2_layout)
        v_layout.addLayout(v1_layout)
        v_layout.addLayout(v2_layout)
        return self.uhp_group_box

    def user_sets(self):
        group_box = QGroupBox('UserSets', self)
        h_layout = QHBoxLayout(group_box)
        v1_layout = QVBoxLayout()
        v2_layout = QVBoxLayout()

        h0_layout = QHBoxLayout()
        h0_layout.addWidget(self.get_all_user_sets_checkbox)
        h0_layout.setAlignment(Qt.AlignLeft)
        v1_layout.addLayout(h0_layout)

        # h01_layout = QHBoxLayout()
        # h01_layout.addWidget(self.get_current_user_sets_checkbox)
        # h01_layout.setAlignment(Qt.AlignLeft)
        # v1_layout.addLayout(h01_layout)

        for checkbox, valuebox in self.user_sets_dic.items():
            h1_layout = QHBoxLayout()
            h1_layout.addWidget(checkbox)
            h1_layout.addWidget(valuebox)
            v1_layout.addLayout(h1_layout)

        h_layout.addLayout(v1_layout)
        h_layout.addLayout(v2_layout)
        return group_box

    def start_close(self):
        group_box = QGroupBox('', self)
        v_layout = QVBoxLayout(group_box)

        h_layout = QHBoxLayout()
        h_layout.addWidget(self.post_button)
        h_layout.addWidget(self.close_button)
        v_layout.addLayout(h_layout)

        return group_box

    def camera_log(self):
        group_box = QGroupBox('CameraMessage', self)
        h_layout = QHBoxLayout(group_box)
        h_layout.addWidget(self.camera_message_edit)
        return group_box


class SingleParameterValueWindow(SingleParameterWindow):
    def __init__(self):
        super(SingleParameterValueWindow, self).__init__()
        self.signal_post()

    def main_value(self):
        [self.connect_by_choose_camera_combox.addItem(self.device_list[i]) for i in range(0, len(self.device_list))]

        scan_2d_exposure_mode = ["Timed", "Auto", "HDR", "Flash"]
        [self.scan_2d_exposure_mode_combox.addItem(scan_2d_exposure_mode[i]) for i in range(0, len(scan_2d_exposure_mode))]
        [self.scan_2d_tone_mapping_spinbox.addItem(i) for i in ["False", "True"]]
        [self.cloud_outlier_filter_mode_spinbox.addItem(i) for i in ["Off", "Weak", "Normal"]]
        [self.cloud_smooth_mode_spinbox.addItem(i) for i in ["Off", "Normal", "Weak", "Strong"]]

        [self.projector_fringe_coding_mode_spinbox.addItem(i) for i in ["Fast", "Accurate"]]
        [self.projector_anti_flicker_mode_spinbox.addItem(i) for i in ["Off", "AC50Hz", "AC60Hz"]]
        [self.projector_power_level_spinbox.addItem(i) for i in ["High", "Normal", "Low"]]

        [self.uhp_capture_mode_spinbox.addItem(i) for i in ["Camera1", "Camera2", "Merge"]]
        [self.uhp_fringe_coding_mode_spinbox.addItem(i) for i in ["Fast", "Accurate"]]
        [self.fringe_coding_mode_spinbox.addItem(i) for i in ["Fast", "Accurate"]]

    def signal_post(self):
        self.connect_by_choose_camera_button.clicked.connect(self.connect_camera_by_choose_signal)
        self.connect_by_ip_camera_button.clicked.connect(self.connect_camera_by_ip_signal)
        self.get_all_user_sets_checkbox.clicked.connect(self.print_user_sets)
        self.get_device_info_button.clicked.connect(self.print_device_info)
        self.get_device_intrinsic_button.clicked.connect(self.print_device_intrinsic)
        self.get_device_resolution_button.clicked.connect(self.print_device_resolution)
        self.add_2d_hdr_exposure_sequence_button.clicked.connect(self.add_sub_scan_2d_hdr_exposure_signal)
        self.sub_2d_hdr_exposure_sequence_button.clicked.connect(self.add_sub_scan_2d_hdr_exposure_signal)
        self.add_scan_3d_exposure_button.clicked.connect(self.add_sub_scan_3d_exposure_signal)
        self.sub_scan_3d_exposure_button.clicked.connect(self.add_sub_scan_3d_exposure_signal)

        # self.laser_group_box.clicked.connect(self.laser_group_box.hide)
        self.post_button.clicked.connect(self.post_signal)
        self.close_button.clicked.connect(self.close)

    def connect_camera_by_choose_signal(self):
        if self.connect_by_choose_camera_button.text() == 'Connect':
            print(self.connect_by_choose_camera_combox.currentText())
            index = self.connect_by_choose_camera_combox.currentIndex()
            connect_status = self.connect_info.connect_camera_from_device_list(index)
            self.camera_message_edit.append('· ' + connect_status)

            if 'error' not in connect_status.lower():
                self.connect_by_choose_camera_button.setText('Disconnect')
            else:
                QMessageBox.critical(self, 'Connect Error', connect_status, QMessageBox.Yes | QMessageBox.No, QMessageBox.Yes)
        elif self.connect_by_choose_camera_button.text() == 'Disconnect':
            disconnect_status = self.connect_info.disconnect_from_device()
            self.connect_by_choose_camera_button.setText('Connect')
            self.camera_message_edit.append('· ' + disconnect_status)

    def connect_camera_by_ip_signal(self):
        if self.connect_by_ip_camera_button.text() == 'Connect':
            print(self.connect_by_ip_camera_line_edit.text())
            ip_address = self.connect_by_ip_camera_line_edit.text()
            connect_status = self.connect_info.connect_camera_from_device_ip(ip_address)
            self.camera_message_edit.append('· ' + connect_status)

            if 'error' not in connect_status.lower():
                self.connect_by_ip_camera_button.setText('Disconnect')
            else:
                QMessageBox.critical(self, 'Connect Error', connect_status, QMessageBox.Yes | QMessageBox.No,
                                     QMessageBox.Yes)
        elif self.connect_by_ip_camera_button.text() == 'Disconnect':
            disconnect_status = self.connect_info.disconnect_from_device()
            self.connect_by_ip_camera_button.setText('Connect')
            self.camera_message_edit.append('· ' + disconnect_status)

    def add_sub_scan_2d_hdr_exposure_signal(self):
        if self.sender().text() == '+':
            if self.v4_layout.count() <= 10:
                add_spin = QDoubleSpinBox()
                add_spin.setFixedSize(QtCore.QSize(60, 20))
                add_spin.setSingleStep(0.1)
                add_spin.setDecimals(1)
                add_spin.setRange(0, 10000000)
                self.v4_layout.addWidget(add_spin)
                self.scan_2d_hdr_exposure_sequence_spin_box_list.append(add_spin)
                print(self.scan_2d_hdr_exposure_sequence_spin_box_list)
            else:
                QMessageBox.information(self, 'Error', "Add error, the number of controls is too large to continue adding.",\
                                        QMessageBox.Yes | QMessageBox.No, QMessageBox.Yes)
        else:
            if self.v4_layout.count() > 3:
                self.v4_layout.itemAt(3).widget().deleteLater()   # 从队首删除
                self.scan_2d_hdr_exposure_sequence_spin_box_list.pop(0)
                print(self.scan_2d_hdr_exposure_sequence_spin_box_list)

            else:
                QMessageBox.information(self, 'Error', "Subtract error, there are not enough controls to continue deleting.",\
                                        QMessageBox.Yes | QMessageBox.No, QMessageBox.Yes)

    def add_sub_scan_3d_exposure_signal(self):
        if self.sender().text() == '+':
            if self.v5_layout.count() <= 10:
                add_spin = QDoubleSpinBox()
                add_spin.setFixedSize(QtCore.QSize(60, 20))
                add_spin.setSingleStep(0.1)
                add_spin.setDecimals(1)
                add_spin.setRange(0, 10000000)
                self.v5_layout.addWidget(add_spin)
                self.scan_3d_exposure_spin_box_list.append(add_spin)
                print(self.scan_3d_exposure_spin_box_list)
            else:
                QMessageBox.information(self, 'Error', "Add error, the number of controls is too large to continue adding.",\
                                        QMessageBox.Yes | QMessageBox.No, QMessageBox.Yes)
        else:
            if self.v5_layout.count() > 3:
                self.v5_layout.itemAt(3).widget().deleteLater()   # 从队首删除
                self.scan_3d_exposure_spin_box_list.pop(0)
                print(self.scan_3d_exposure_spin_box_list)

            else:
                QMessageBox.information(self, 'Error', "Subtract error, there are not enough controls to continue deleting.",\
                                        QMessageBox.Yes | QMessageBox.No, QMessageBox.Yes)

    def print_device_info(self):
        device_info = self.connect_info.get_device_info_signal()
        print(device_info[0])
        self.camera_message_edit.append('· Camera Model           : {}\n'
                                        '· Camera ID              : {}\n'
                                        '· Camera IP              : {}\n'
                                        '· Camera Firmware Version: {}\n'
                                        '· Camera Hardware Version: {}\n'
                                        '· Camera Port            : {}\n'.
                                        format(device_info[0], device_info[1],
                                               device_info[2], device_info[3],
                                               device_info[4], device_info[5],
                                               ))

    def print_device_intrinsic(self):
        device_intrinsic = self.connect_info.get_device_intrinsic_signal()
        print(device_intrinsic[0])
        self.camera_message_edit.append('· CameraDistCoeffs =\n'
                                        '· {}\n'
                                        '· DepthDistCoeffs =\n'
                                        '· {}\n'
                                        '· CameraMatrix =\n'
                                        '· {}\n'
                                        '· DepthMatrix =\n'
                                        '· {}\n'
                                        .format(device_intrinsic[0], device_intrinsic[1],
                                                device_intrinsic[2], device_intrinsic[3]))

    def print_device_resolution(self):
        device_resolution = self.connect_info.get_device_resolution_signal()
        print(device_resolution[0])
        self.camera_message_edit.append('· Color Resolution: width * Heigh = {} * {}\n'
                                        '· Depth Resolution: width * Heigh = {} * {}\n'
                                        .format(device_resolution[0], device_resolution[1],
                                                device_resolution[2], device_resolution[3]))

    def print_user_sets(self):
        user_sets = self.connect_info.all_user_sets()
        self.camera_message_edit.append('· ' + user_sets)

    def print_current_user_sets(self):
        current_user_sets = self.connect_info.current_user_sets()
        self.camera_message_edit.append('· ' + current_user_sets)

    def post_signal(self):
        if self.scan_2d_exposure_mode_checkbox.isChecked():
            mode_name = self.scan_2d_exposure_mode_combox.currentText()
            print(mode_name)
            get_message = self.connect_info.scan_2d_exposure_mode_signal(mode_name)
            self.append_message(self.scan_2d_exposure_mode_checkbox.text(), mode_name, get_message)

        if self.scan_2d_exposure_time_checkbox.isChecked():
            exposure_value = self.scan_2d_exposure_time_spinbox.text()
            print(exposure_value)
            get_message = self.connect_info.scan_2d_exposure_time(float(exposure_value.split(' ')[0]))
            self.append_message(self.scan_2d_exposure_time_checkbox.text(), exposure_value, get_message)

        if self.scan_2d_expected_gray_checkbox.isChecked():
            exposure_value = self.scan_2d_expected_gray_spinbox.text()
            print(exposure_value)
            get_message = self.connect_info.scan_2d_expected_gray_value_signal(int(exposure_value))
            self.append_message(self.scan_2d_expected_gray_checkbox.text(), exposure_value, get_message)

        if self.scan_2d_tone_mapping_checkbox.isChecked():
            exposure_index = self.scan_2d_tone_mapping_spinbox.currentIndex()
            exposure_value = self.scan_2d_tone_mapping_spinbox.currentText()
            print(exposure_value)
            get_message = self.connect_info.scan_2d_tone_mapping_enable_signal(exposure_index)
            self.append_message(self.scan_2d_tone_mapping_checkbox.text(), exposure_value, get_message)

        if self.scan_2d_sharpen_factor_checkbox.isChecked():
            current_value = self.scan_2d_sharpen_factor_spinbox.text()
            get_current_value = self.connect_info.scan_2d_sharpen_signal(float(current_value))
            self.append_message(self.scan_2d_sharpen_factor_checkbox.text(), current_value, get_current_value)

        if self.scan_2d_roi_checkbox.isChecked():
            current_value = '\n· x = {}\n· y = {}\n· width = {}\n· height = {}\n'
            x_value = self.scan_2d_roi_x_spinbox.text()
            y_value = self.scan_2d_roi_y_spinbox.text()
            width_value = self.scan_2d_roi_w_spinbox.text()
            hight_value = self.scan_2d_roi_h_spinbox.text()

            get_value = \
                self.connect_info.scan_2d_roi_signal(int(x_value), int(y_value), int(width_value), int(hight_value))
            if isinstance(get_value, list):
                self.append_message(self.scan_2d_roi_checkbox.text(),
                                    current_value.format(int(x_value), int(y_value), int(width_value), int(hight_value)),
                                    current_value.format(get_value[0], get_value[1], get_value[2], get_value[3]))
            else:
                self.append_message(self.scan_2d_roi_checkbox.text(),
                                    current_value.format(int(x_value), int(y_value), int(width_value), int(hight_value)),
                                    get_value)

        if self.scan_3d_gain_checkbox.isChecked():
            current_value = self.scan_3d_gain_spinbox.text()
            get_current_value = self.connect_info.scan_3d_gain_signal(float(current_value))
            self.append_message(self.scan_3d_gain_checkbox.text(), self.scan_3d_gain_checkbox.text, current_value, get_current_value)

        if self.scan_3d_roi_checkbox.isChecked():
            current_value = '\n· x = {}\n· y = {}\n· width = {}\n· height = {}\n'
            x_value = self.scan_3d_roi_x_spinbox.text()
            y_value = self.scan_3d_roi_y_spinbox.text()
            width_value = self.scan_3d_roi_w_spinbox.text()
            hight_value = self.scan_3d_roi_h_spinbox.text()

            get_value = \
                self.connect_info.scan_3d_roi_signal(int(x_value), int(y_value), int(width_value), int(hight_value))
            if isinstance(get_value, list):
                self.append_message(self.scan_3d_roi_checkbox.text(),
                                    current_value.format(int(x_value), int(y_value), int(width_value), int(hight_value)),
                                    current_value.format(get_value[0], get_value[1], get_value[2], get_value[3]))
            else:
                self.append_message(self.scan_3d_roi_checkbox.text(),
                                    current_value.format(int(x_value), int(y_value), int(width_value), int(hight_value)),
                                    get_value)

        if self.depth_range_checkbox.isChecked():
            current_value = '\n· lower = {}\n· upper = {}\n'
            lower = self.depth_range_lower_spinbox.text()
            upper = self.depth_range_upper_spinbox.text()
            get_value = \
                self.connect_info.depth_range_signal(int(lower), int(upper))
            if isinstance(get_value, list):
                self.append_message(self.depth_range_checkbox.text(),
                                    current_value.format(int(lower), int(upper)),
                                    current_value.format(get_value[0], get_value[1]))
            else:
                self.append_message(self.depth_range_checkbox.text(),
                                    current_value.format(int(lower), int(upper)), get_value)

        if self.fringe_contrast_threshold_checkbox.isChecked():
            current_value = self.fringe_contrast_threshold_spinbox.text()
            get_current_value = self.connect_info.fringe_contrast_threshold_signal(int(current_value))
            self.append_message(self.fringe_contrast_threshold_checkbox.text(), current_value, get_current_value)

        if self.fringe_min_threshold_checkbox.isChecked():
            current_value = self.fringe_min_threshold_spinbox.text()
            get_current_value = self.connect_info.fringe_min_threshold_signal(int(current_value))
            self.append_message(current_value, get_current_value)

        if self.cloud_outlier_filter_mode_checkbox.isChecked():
            current_value = self.cloud_outlier_filter_mode_spinbox.currentText()
            get_current_value = self.connect_info.cloud_outlier_filter_mode_signal(current_value)
            print(get_current_value)
            self.append_message(self.cloud_outlier_filter_mode_checkbox.text(), current_value, get_current_value)

        if self.cloud_smooth_mode_checkbox.isChecked():
            current_value = self.cloud_smooth_mode_spinbox.currentText()
            get_current_value = self.connect_info.cloud_smooth_mode_signal(current_value)
            print(get_current_value)
            self.append_message(self.cloud_smooth_mode_checkbox.text(), current_value, get_current_value)

        if self.projector_fringe_coding_mode_checkbox.isChecked():
            mode_name = self.projector_fringe_coding_mode_spinbox.currentText()
            print(mode_name)
            get_message = self.connect_info.projector_fringe_coding_mode_signal(mode_name)
            self.append_message(self.projector_fringe_coding_mode_checkbox.text(), mode_name, get_message)

        if self.projector_anti_flicker_mode_checkbox.isChecked():
            mode_name = self.projector_anti_flicker_mode_spinbox.currentText()
            print(mode_name)
            get_message = self.connect_info.projector_anti_flicker_mode_signal(mode_name)
            self.append_message(self.projector_anti_flicker_mode_checkbox.text(), mode_name, get_message)

        if self.scan_2d_hdr_exposure_sequence_checkbox.isChecked():
            scan_2d_hdr_exposure_list = [float(i.text()) for i in self.scan_2d_hdr_exposure_sequence_spin_box_list]
            print(scan_2d_hdr_exposure_list)
            get_message = self.connect_info.scan_2d_hdr_exposure_sequence_signal(scan_2d_hdr_exposure_list)
            self.append_message(self.scan_2d_hdr_exposure_sequence_checkbox.text(), str(scan_2d_hdr_exposure_list), str(get_message))

        if self.scan_3d_exposure_checkbox.isChecked():
            scan_3d_exposure_list = [float(i.text()) for i in self.scan_3d_exposure_spin_box_list]
            print(scan_3d_exposure_list)
            get_message = self.connect_info.scan_3d_exposure_signal(scan_3d_exposure_list)
            self.append_message(self.scan_3d_exposure_checkbox.text(), str(scan_3d_exposure_list), str(get_message))

        if self.projector_power_level_checkbox.isChecked():
            mode_name = self.projector_power_level_spinbox.currentText()
            print(mode_name)
            get_message = self.connect_info.projector_power_level_signal(mode_name)
            self.append_message(self.projector_power_level_checkbox.text(), mode_name, get_message)

        if self.laser_group_box.isChecked():
            current_value = '\n· laser frame mode   = {}' \
                            '\n· laser frange start = {}' \
                            '\n· laser frange end   = {}' \
                            '\n· laser frange count = {}' \
                            '\n· laser power  level = {}\n'
            mode_index = self.fringe_coding_mode_spinbox.currentIndex()
            mode_name = self.fringe_coding_mode_spinbox.currentText()
            start = self.frame_range_start_spinbox.text()
            end = self.frame_range_end_spinbox.text()
            count = self.frame_partition_count_spinbox.text()
            level = self.power_level_spinbox.text()
            get_value = \
                self.connect_info.laser_settings_signal(mode_name, int(start), int(end), int(count), int(level))
            if isinstance(get_value, list):
                self.append_message('Laser settings',
                                    current_value.format(mode_name, int(start), int(end), int(count), int(level)),
                                    current_value.format(get_value[0], get_value[1], get_value[2], get_value[3], get_value[4]))
            else:
                self.append_message('Laser settings',
                                    current_value.format(mode_name, int(start), int(end), int(count), int(level)),
                                    get_value)

        if self.uhp_group_box.isChecked():
            current_value = '\n· uhp capture mode       = {}' \
                            '\n· uhp frange coding mode = {}\n'
            capture_mode_name = self.uhp_capture_mode_spinbox.currentText()
            print(capture_mode_name)
            coding_mode_name = self.uhp_fringe_coding_mode_spinbox.currentText()
            print(coding_mode_name)
            get_value = self.connect_info.uhp_settings_signal(capture_mode_name, coding_mode_name)
            print(get_value)
            if isinstance(get_value, list):
                self.append_message('UHP settings',
                                    current_value.format(capture_mode_name, coding_mode_name),
                                    current_value.format(get_value[0], get_value[1]))
            else:
                self.append_message('UHP settings', current_value.format(capture_mode_name, coding_mode_name), get_value)

        if self.get_current_user_sets_checkbox.isChecked():
            current_name = self.get_current_user_sets_spinbox.text()
            get_current_name = self.connect_info.current_user_sets(current_name)
            self.append_message(self.get_current_user_sets_checkbox.text(), current_name, get_current_name)

        if self.delete_user_set_checkbox.isChecked():
            delete_name = self.delete_user_set_spinbox.text()
            get_current_name = self.connect_info.delete_user(delete_name)
            self.append_message(self.delete_user_set_checkbox.text(),delete_name, get_current_name)

        if self.add_user_set_checkbox.isChecked():
            add_name = self.add_user_set_spinbox.text()
            print(add_name)
            get_add_message = self.connect_info.add_user(add_name)
            print(get_add_message)
            self.append_message(self.add_user_set_checkbox.text(), add_name, get_add_message)

    def append_message(self, label, post=' ', get=' '):
        self.camera_message_edit.append('· {}:\n\n· Post Message: {}\n· Get  Message: {}\n· {}'.format(label, post, get, '-'*60))
        print(self.laser_group_box.isChecked())
        print(self.uhp_group_box.isChecked())


if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = SingleParameterValueWindow()
    app.setStyleSheet(qdarkstyle.load_stylesheet_pyqt5())
    ex.show()
    sys.exit(app.exec_())