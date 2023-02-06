#!/usr/bin/python
# -*- coding: utf-8 -*-
import sys
import qdarkstyle
from UI_Design import camera_windows
from PyQt5.QtWidgets import *

if __name__ == '__main__':
    app = QApplication(sys.argv)
    win = camera_windows.FunctCameraGradeChange()
    app.setStyleSheet(qdarkstyle.load_stylesheet_pyqt5())
    win.show()
    sys.exit(app.exec_())