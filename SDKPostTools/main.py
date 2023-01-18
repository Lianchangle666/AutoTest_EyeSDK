#!/usr/bin/python
# -*- coding: utf-8 -*-
import os
import sys
import qdarkstyle
from PyQt5.QtWidgets import *
from PyQt5 import QtCore
from UIDesign import process_check_windows

brand_image = os.get
cwd() + os.sep + 'img\brand.png'
img_image = os.getcwd() + os.sep + 'img\img.png'
logo_image = os.getcwd() + os.sep + 'img\logal.png'

print(brand_image)
print(img_image)
print(logo_image)


if __name__ == '__main__':
    app = QApplication(sys.argv)
    # QtCore.QCoreApplication.setAttribute(QtCore.Qt.AA_EnableHighDpiScaling)
    myWin = process_check_windows.MyWidget()
    myWin.setStyleSheet(qdarkstyle.load_stylesheet_pyqt5())
    myWin.show()
    sys.exit(app.exec_())