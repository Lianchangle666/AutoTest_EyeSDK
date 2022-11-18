#!/usr/bin/python
# -*- coding: utf-8 -*-
import pytest
import warnings
from Basic import paramset
import main_test

warnings.filterwarnings('ignore')


class TestParameterUHP:
    def setup_class(self):
        self.obj = paramset.ParameterFunction(main_test.ip)

        self.uhp_fringe_coding_mode_dic = {"Fast": 0, "Accurate": 1}
        self.uhp_capture_mode_dic = {"Camera1": 0, "Camera2": 1, "Merge": 2}

    @pytest.mark.skipif("UHP" not in main_test.camera_name, reason="UHP")
    @pytest.mark.run(order=10)
    @pytest.mark.parametrize('mode', ["Fast", "Accurate"])
    def test_uhp_fringe_coding_mode_valid(self, mode):
        assert self.uhp_fringe_coding_mode_dic[mode] == self.obj.uhp_fringe_coding_mode(mode)

    @pytest.mark.skipif("UHP" not in main_test.camera_name, reason="UHP")
    @pytest.mark.run(order=10)
    @pytest.mark.parametrize('mode', ["Camera1", "Camera2", "Merge"])
    def test_uhp_capture_mode_valid(self, mode):
        assert self.uhp_capture_mode_dic[mode] == self.obj.uhp_capture_mode(mode)
