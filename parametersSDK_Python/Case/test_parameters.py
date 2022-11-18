#!/usr/bin/python
# -*- coding: utf-8 -*-
import pytest
import warnings
from Basic import paramset
import main_test

warnings.filterwarnings('ignore')


class TestParamFunction:

    def setup_class(self):
        self.obj = paramset.ParameterFunction(main_test.ip)

        self.exposure_2d_mode_dic = {"Timed": 0, "Auto": 1, "HDR": 2, "Flash": 3}
        self.cloud_smooth_mode_dic = {"Off": 0, "Normal": 1, "Weak": 2, "Strong": 3}
        self.cloud_outlier_filter_mode_dic = {"Off": 0, "Weak": 1, "Normal": 2}
        self.projector_fringe_coding_mode_dic = {"Fast": 0, "Accurate": 1}
        self.projector_power_level_dic = {"High": 0, "Normal": 1, "Low": 2}
        self.projector_anti_flicker_mode_dic = {"Off": 0, "AC50Hz": 1, "AC60Hz": 2}

    @pytest.mark.skipif("Laser" in main_test.camera_name or "LSR" in main_test.camera_name or "DEEP" in main_test.camera_name,
                        reason="Laser or LSR")
    @pytest.mark.run(order=1)
    @pytest.mark.parametrize('value', [(0.1,), (99,), (0.1, 0.1), (99, 99), (0.1, 0.1, 0.1), (99, 99, 99), (0.1, 0.1, 30)])
    def test_scan_3d_exposure_valid(self, value):
        get_value = self.obj.scan_3d_exposure(value)
        assert len(get_value) == len(value)
        for i in range(len(get_value)):
            assert str(get_value[i])[0: len(str(value[i]))] == str(value[i])

    @pytest.mark.skipif("Laser" in main_test.camera_name or "LSR" in main_test.camera_name,
                        reason="Laser or LSR")
    @pytest.mark.run(order=1)
    @pytest.mark.parametrize('value', [(0,), (100,), (0.1, 0), (99, 99.1), (0.1, 0.1, 0), (99, 99, 99.1), (0.1, 0.1, 0.1, 0.1)])
    def test_scan_3d_exposure_invalid(self, value):
        get_value = self.obj.scan_3d_exposure(value)
        assert get_value is None

    @pytest.mark.run(order=2)
    @pytest.mark.parametrize('value', [0, 1, 15, 16])
    def test_scan_3d_gain_valid(self, value):
        print(value, self.obj.scan_3d_gain(value))
        assert value == self.obj.scan_3d_gain(value)

    @pytest.mark.run(order=3)
    @pytest.mark.parametrize('value', [0.1, 17, 16.1, 18])
    def test_scan_3d_gain_invalid(self, value):
        print(value, self.obj.scan_3d_gain(value))
        assert value != self.obj.scan_3d_gain(value)

    @pytest.mark.run(order=3)
    @pytest.mark.parametrize('x,y,width,height', [(0, 0, 0, 0), (0, 0, 1, 1), (0, 0, main_test.depth_width, main_test.depth_height)])
    def test_scan_3d_roi_valid(self, x, y, width, height):
        roi = self.obj.scan_3d_roi(x, y, int(width), int(height))
        assert int(roi.x()) == int(x) and int(roi.y()) == int(y) and int(roi.width()) == int(width) and int(roi.height()) == int(height)

    @pytest.mark.run(order=3)
    @pytest.mark.parametrize('x,y,width,height', [(0, 0, int(main_test.depth_width) + 1, int(
        main_test.depth_height) + 1)])
    def test_scan_3d_roi_invalid(self, x, y, width, height):
        print(x, y, width, height)
        roi = self.obj.scan_3d_roi(x, y, int(width), int(height))
        assert roi is None

    @pytest.mark.skipif("Laser" in main_test.camera_name, reason="Laser or LSR")
    @pytest.mark.run(order=4)
    @pytest.mark.parametrize('value,mode', [(0.1, "Timed"), (1, "Timed"), (998.9, "Timed"), (999, "Timed")])
    def test_scan_2d_exposure_time_valid(self, value, mode):
        assert str(self.obj.scan_2d_exposure_time(value))[0: len(str(value))] == str(value)
        assert self.exposure_2d_mode_dic[mode] == self.obj.scan_2d_exposure_mode(mode)

    @pytest.mark.run(order=5)
    @pytest.mark.parametrize('value,mode', [(0, "Timed"), (999.1, "Timed"), (1000, "Timed")])
    def test_scan_2d_exposure_time_invalid(self, value, mode):
        assert str(self.obj.scan_2d_exposure_time(value))[0: len(str(value))] != str(value)
        assert self.exposure_2d_mode_dic[mode] == self.obj.scan_2d_exposure_mode(mode)

    @pytest.mark.run(order=6)
    @pytest.mark.parametrize('value,mode', [(True, "HDR"), (False, "HDR")])
    def test_scan_2d_tone_mapping_enable_invalid(self, value, mode):
        assert bool(self.obj.scan_2d_tone_mapping_enable(value)) == value
        assert self.exposure_2d_mode_dic[mode] == self.obj.scan_2d_exposure_mode(mode)

    @pytest.mark.run(order=8)
    @pytest.mark.parametrize('value,mode', [(True, "HDR"), (False, "HDR")])
    def test_scan_2d_tone_mapping_enable_valid(self, value, mode):
        assert bool(self.obj.scan_2d_tone_mapping_enable(value)) == value
        assert self.exposure_2d_mode_dic[mode] == self.obj.scan_2d_exposure_mode(mode)

    @pytest.mark.run(order=8)
    @pytest.mark.parametrize('value', [(0.1,), (999,), (0.1, 0.1), (999, 999), (0.1, 0.1, 0.1), (999, 999, 999), (0.1, 0.1, 0.1, 0.1), (999, 999, 999, 999), (0.1, 0.1, 0.1, 0.1, 0.1), (999, 999, 999, 999, 999), (0.1, 0.1, 30)])
    def test_scan_2d_hdr_exposure_sequence_valid(self, value):
        get_value = self.obj.scan_2d_hdr_exposure_sequence(value)
        assert len(get_value) == len(value)
        for i in range(len(get_value)):
            assert str(get_value[i])[0: len(str(value[i]))] == str(value[i])

    @pytest.mark.run(order=8)
    @pytest.mark.parametrize('value', [(0,), (1000,), (0.1, 0), (999, 999.1), (0.1, 0.1, 0), (999, 999, 999.1), (0.1, 0.1, 0, 0.1), (999, 999, 999.1, 999), (0.1, 0.1, 0.1, 0.1, 0), (999, 999, 999, 999, 0), (0.1, 0.1, 0.1, 0.1, 0.1, 0.1)])
    def test_scan_2d_hdr_exposure_sequence_invalid(self, value):
        get_value = self.obj.scan_2d_hdr_exposure_sequence(value)
        assert get_value is None

    @pytest.mark.run(order=9)
    @pytest.mark.parametrize('value,mode', [(0, "Auto"), (1, "Auto"), (254, "Auto"), (255, "Auto")])
    def test_scan_2d_expected_gray_value_valid(self, value, mode):
        assert self.obj.scan_2d_expected_gray_value(value) == value
        assert self.exposure_2d_mode_dic[mode] == self.obj.scan_2d_exposure_mode(mode)

    @pytest.mark.run(order=10)
    @pytest.mark.parametrize('value,mode', [(256, "Auto"), (257, "Auto")])
    def test_scan_2d_expected_gray_value_invalid(self, value, mode):
        assert str(self.obj.scan_2d_expected_gray_value(value)) != value
        assert self.exposure_2d_mode_dic[mode] == self.obj.scan_2d_exposure_mode(mode)

    @pytest.mark.run(order=3)
    @pytest.mark.parametrize('x,y,width,height', [(0, 0, 0, 0), (0, 0, 1, 1), (0, 0, main_test.color_width, main_test.color_height)])
    def test_scan_2d_roi_valid(self, x, y, width, height):
        roi = self.obj.scan_2d_roi(x, y, int(width), int(height))
        assert int(roi.x()) == int(x) and int(roi.y()) == int(y) and int(roi.width()) == int(width) and int(roi.height()) == int(height)

    @pytest.mark.run(order=3)
    @pytest.mark.parametrize('x,y,width,height', [(0, 0, int(main_test.color_width) + 1, int(
        main_test.color_height) + 1)])
    def test_scan_2d_roi_invalid(self, x, y, width, height):
        print(x, y, width, height)
        roi = self.obj.scan_2d_roi(x, y, int(width), int(height))
        assert roi is None

    @pytest.mark.run(order=10)
    @pytest.mark.parametrize('value,mode', [(0, "Timed"), (0.1, "Timed"), (4.9, "Timed"), (5, "Timed")])
    def test_scan_2d_sharpen_factor_timed_valid(self, value, mode):
        assert str(self.obj.scan_2d_sharpen_factor(value))[0: len(str(value))] == str(value)
        assert self.exposure_2d_mode_dic[mode] == self.obj.scan_2d_exposure_mode(mode)

    @pytest.mark.run(order=10)
    @pytest.mark.parametrize('value,mode', [(5.1, "Timed"), (6, "Timed")])
    def test_scan_2d_sharpen_factor_timed_invalid(self, value, mode):
        assert str(self.obj.scan_2d_sharpen_factor(value))[0: len(str(value))] != str(value)
        assert self.exposure_2d_mode_dic[mode] == self.obj.scan_2d_exposure_mode(mode)

    @pytest.mark.run(order=10)
    @pytest.mark.parametrize('value,mode', [(0, "Auto"), (0.1, "Auto"), (4.9, "Auto"), (5, "Auto")])
    def test_scan_2d_sharpen_factor_auto_valid(self, value, mode):
        assert str(self.obj.scan_2d_sharpen_factor(value))[0: len(str(value))] == str(value)
        assert self.exposure_2d_mode_dic[mode] == self.obj.scan_2d_exposure_mode(mode)

    @pytest.mark.run(order=10)
    @pytest.mark.parametrize('value,mode', [(5.1, "Auto"), (6, "Auto")])
    def test_scan_2d_sharpen_factor_auto_invalid(self, value, mode):
        assert str(self.obj.scan_2d_sharpen_factor(value))[0: len(str(value))] != str(value)
        assert self.exposure_2d_mode_dic[mode] == self.obj.scan_2d_exposure_mode(mode)

    @pytest.mark.run(order=10)
    @pytest.mark.parametrize('value,mode', [(0, "HDR"), (0.1, "HDR"), (4.9, "HDR"), (5, "HDR")])
    def test_scan_2d_sharpen_factor_hdr_valid(self, value, mode):
        assert str(self.obj.scan_2d_sharpen_factor(value))[0: len(str(value))] == str(value)
        assert self.exposure_2d_mode_dic[mode] == self.obj.scan_2d_exposure_mode(mode)

    @pytest.mark.run(order=10)
    @pytest.mark.parametrize('value,mode', [(5.1, "HDR"), (6, "HDR")])
    def test_scan_2d_sharpen_factor_hdr_invalid(self, value, mode):
        assert str(self.obj.scan_2d_sharpen_factor(value))[0: len(str(value))] != str(value)
        assert self.exposure_2d_mode_dic[mode] == self.obj.scan_2d_exposure_mode(mode)

    @pytest.mark.skipif("LSR" in main_test.camera_name or "DEEP" in main_test.camera_name, reason="LSR, DEEP")
    @pytest.mark.run(order=10)
    @pytest.mark.parametrize('value,mode', [(0, "Flash"), (0.1, "Flash"), (4.9, "Flash"), (5, "Flash")])
    def test_scan_2d_sharpen_factor_flash_valid(self, value, mode):
        assert str(self.obj.scan_2d_sharpen_factor(value))[0: len(str(value))] == str(value)
        assert self.exposure_2d_mode_dic[mode] == self.obj.scan_2d_exposure_mode(mode)

    @pytest.mark.skipif("LSR" in main_test.camera_name or "DEEP" in main_test.camera_name, reason="LSR, DEEP")
    @pytest.mark.run(order=10)
    @pytest.mark.parametrize('value,mode', [(5.1, "Flash"), (6, "Flash")])
    def test_scan_2d_sharpen_factor_flash_invalid(self, value, mode):
        assert str(self.obj.scan_2d_sharpen_factor(value))[0: len(str(value))] != str(value)
        assert self.exposure_2d_mode_dic[mode] == self.obj.scan_2d_exposure_mode(mode)

    @pytest.mark.run(order=10)
    @pytest.mark.parametrize('mode', ["Off", "Weak", "Normal", "Strong"])
    def test_cloud_smooth_mode_valid(self, mode):
        assert self.cloud_smooth_mode_dic[mode] == self.obj.cloud_smooth_mode(mode)

    @pytest.mark.run(order=10)
    @pytest.mark.parametrize('mode', ["Off", "Weak", "Normal"])
    def test_cloud_outlier_filter_mode_valid(self, mode):
        assert self.cloud_outlier_filter_mode_dic[mode] == self.obj.cloud_outlier_filter_mode(mode)

    @pytest.mark.run(order=10)
    @pytest.mark.parametrize('lower,upper', [(1, 2), (1, 5000), (4000, 5000)])
    def test_depth_range_valid(self, lower, upper):
        print(lower, upper)
        depth = self.obj.depth_range(lower, upper)
        assert lower == int(depth.lower()) and upper == int(depth.upper())

    @pytest.mark.skipif("NANO" not in main_test.camera_name.upper() and "PRO XS" not in main_test.camera_name.upper(), reason="Nano NANO PROXS")
    @pytest.mark.run(order=10)
    @pytest.mark.parametrize('mode', ["Fast", "Accurate"])
    def test_projector_fringe_coding_mode_valid(self, mode):
        assert self.projector_fringe_coding_mode_dic[mode] == self.obj.projector_fringe_coding_mode(mode)

    @pytest.mark.skipif("NANO" not in main_test.camera_name.upper() and "PRO XS" not in main_test.camera_name.upper(), reason="Nano NANO PROXS")
    @pytest.mark.run(order=10)
    @pytest.mark.parametrize('mode', ["High", "Normal", "Low"])
    def test_projector_projector_power_level_valid(self, mode):
        assert self.projector_power_level_dic[mode] == self.obj.projector_projector_power_level(mode)

    @pytest.mark.skipif("NANO" not in main_test.camera_name.upper() and "PRO XS" not in main_test.camera_name.upper(), reason="Nano NANO PROXS")
    @pytest.mark.run(order=10)
    @pytest.mark.parametrize('mode', ["Off", "AC50Hz", "AC60Hz"])
    def test_projector_projector_anti_flicker_mode_valid(self, mode):
        assert self.projector_anti_flicker_mode_dic[mode] == self.obj.projector_projector_anti_flicker_mode(mode)

