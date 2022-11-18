#!/usr/bin/python
# -*- coding: utf-8 -*-
import pytest
import warnings
from Basic import paramset
import main_test

warnings.filterwarnings('ignore')


class TestParameterLaser:
    def setup_class(self):
        self.obj = paramset.ParameterFunction(main_test.ip)
        self.laser_fringe_coding_mode_dic = {"Fast": 0, "Accurate": 1}

    @pytest.mark.skipif("Laser" not in main_test.camera_name, reason="Laser")
    @pytest.mark.run(order=1)
    @pytest.mark.parametrize('value', [(8,), (96,), (96, 4), (4, 4), (96, 96, 4), (4, 4, 4), (4,)])
    def test_scan_3d_exposure_laser_valid(self, value):
        get_value = self.obj.scan_3d_exposure(value)
        assert len(get_value) == len(value)
        for i in range(len(get_value)):
            assert str(get_value[i])[0: len(str(value[i]))] == str(value[i])

    @pytest.mark.skipif("LSR" not in main_test.camera_name and "DEEP" not in main_test.camera_name, reason="LSR, DEEP")
    @pytest.mark.run(order=1)
    @pytest.mark.parametrize('value', [(8,), (96,), (96, 8), (8, 8), (96, 96, 8), (96, 96, 96), (8, 8, 8)])
    def test_scan_3d_exposure_lsr_valid(self, value):
        get_value = self.obj.scan_3d_exposure(value)
        assert len(get_value) == len(value)
        for i in range(len(get_value)):
            assert str(get_value[i])[0: len(str(value[i]))] == str(value[i])

    @pytest.mark.skipif("Laser" not in main_test.camera_name, reason="Laser")
    @pytest.mark.run(order=1)
    @pytest.mark.parametrize('value', [(0.1,), (100,), (99,), (0.1, 0.1), (99, 99.1), (0.1, 0.1, 0), (99, 99, 99.1), (0.1, 0.1, 0.1, 0.1)])
    def test_scan_3d_exposure_laser_invalid(self, value):
        get_value = self.obj.scan_3d_exposure(value)
        assert get_value is None or get_value != value

    @pytest.mark.skipif("LSR" not in main_test.camera_name and "DEEP" not in main_test.camera_name, reason="LSR, DEEP")
    @pytest.mark.run(order=1)
    @pytest.mark.parametrize('value', [(0.1,), (100,), (99,), (0.1, 0.1), (99, 99.1), (0.1, 0.1, 0), (99, 99, 99.1), (0.1, 0.1, 0.1, 0.1)])
    def test_scan_3d_exposure_lsr_invalid(self, value):
        get_value = self.obj.scan_3d_exposure(value)
        assert get_value is None or value != get_value

    @pytest.mark.run(order=10)
    @pytest.mark.parametrize('mode', ["Fast", "Accurate"])
    def test_laser_fringe_coding_mode_valid(self, mode):
        assert self.laser_fringe_coding_mode_dic[mode] == self.obj.laser_fringe_coding_mode(mode)

    @pytest.mark.run(order=10)
    @pytest.mark.parametrize('start,end', [(0, 25), (0, 100), (1, 26), (1, 100), (75, 100), (74, 99)])
    def test_laser_frame_range_start_end_valid(self, start, end):
        get_start_end = self.obj.laser_frame_range_start_end(start, end)
        assert len(get_start_end) == 2 and get_start_end[0] == start and get_start_end[1] == end

    @pytest.mark.run(order=10)
    @pytest.mark.parametrize('start,end', [(1, 25), (0, 24), (1, 24), (75, 99), (99, 1), (25, 1)])
    def test_laser_frame_range_start_end_invalid(self, start, end):
        get_start_end = self.obj.laser_frame_range_start_end(start, end)
        assert get_start_end is None or (get_start_end[0] != start or get_start_end[1] != end)

    @pytest.mark.run(order=10)
    @pytest.mark.parametrize('value', [1, 2, 3, 4])
    def test_laser_frame_partition_count_valid(self, value):
        assert value == self.obj.laser_frame_partition_count(value)

    @pytest.mark.run(order=10)
    @pytest.mark.parametrize('value', [0, 5, 6])
    def test_laser_frame_partition_count_invalid(self, value):
        assert value != self.obj.laser_frame_partition_count(value)

    @pytest.mark.run(order=10)
    @pytest.mark.parametrize('value', [20, 100, 21, 99, 50])
    def test_laser_power_level_valid(self, value):
        assert value == self.obj.laser_power_level(value)

    @pytest.mark.run(order=10)
    @pytest.mark.parametrize('value', [0, 19, 101])
    def test_laser_power_level_invalid(self, value):
        assert value != self.obj.laser_power_level(value)
