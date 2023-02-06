#!/usr/bin/python
# -*- coding: utf-8 -*-
import threading


class CameraThread(threading.Thread):
    def __init__(self, func, args=()):
        super(CameraThread, self).__init__()
        self.func = func
        self.args = args

    def run(self):
        self.result = self.func(*self.args)

    def get_result(self):
        try:
            return self.result
        except Exception as e:
            return None