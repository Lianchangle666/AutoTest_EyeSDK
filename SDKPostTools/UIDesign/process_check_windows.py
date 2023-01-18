#!/usr/bin/python
# -*- coding: utf-8 -*-
import sys
import os
import time
import qdarkstyle
from threading import Thread
from PyQt5 import QtCore
from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from main import logo_image


class CalculatorThread(QThread):
    signal_progress_update = pyqtSignal(list)

    def __init__(self):
        super(CalculatorThread, self).__init__()
        self.total = 100
        self.i = 0

    def run(self):
        while True:
            self.i += 1
            self.signal_progress_update.emit([self.i, self.total])
            time.sleep(0.2)
            if self.i > self.total:
                break


class MyWidget(QWidget):
    def __init__(self):
        super(MyWidget, self).__init__()
        self.resize(80, 50)
        self.error_list = []
        self.n = 0

        self.setWindowFlags(QtCore.Qt.CustomizeWindowHint)
        self.ui_widgets()
        self.ui_style()
        self.ui_value()

    def ui_widgets(self):
        self.progress_bar = QProgressBar(self)
        self.process_label = QLabel("Loading API Environment ...")
        self.image_lable = QLabel()
        self.image_lable.setPixmap(QPixmap(logo_image).scaled(300, 60))
        self.designer = QLabel("Designer: Lian Changle")

    def ui_value(self):
        self.progress_bar.setValue(0)
        self.progress_bar.setMaximum(100)
        self.progress_bar.setFixedWidth(400)
        self.progress_bar.move(20, 40)
        self.process_label.setAlignment(Qt.AlignCenter)
        self.progress_bar.setAlignment(Qt.AlignCenter)
        self.image_lable.setAlignment(Qt.AlignCenter)
        self.designer.setAlignment(Qt.AlignRight)

    def ui_style(self):
        v_layout = QVBoxLayout()

        self.group_box = QGroupBox('', self)
        self.h_layout = QHBoxLayout()
        self.h_layout.addWidget(self.process_label)
        self.group_box.setLayout(self.h_layout)

        v_layout.addWidget(self.image_lable)
        v_layout.addWidget(self.group_box)
        v_layout.addWidget(self.progress_bar)
        v_layout.addWidget(self.designer)

        v_layout.addLayout(self.h_layout)
        self.setLayout(v_layout)

        self.thread = CalculatorThread()  # 线程要声明为成员变量（加上self）
        self.thread.signal_progress_update.connect(self.update_progress)
        # thread.run()  # 串行执行（非多线程方法）【DeBug时候使用】
        t1 = Thread(target=self.check_environment, args=())
        self.thread.start()  # 线程执行（调用run方法）
        t1.start()

    def update_progress(self, values):
        '''
        更新进度条的槽函数
        '''
        self.progress_bar.setValue(int(values[0] / values[1] * 100))
        if self.progress_bar.text() == "100%" and self.n == 0:
            self.hide()
            self.n += 1
            if len(self.error_list) == 0:
                t2 = Thread(target=self.show_single_window(), args=())
                t2.start()
            else:
                err = 'The error results are as follows:\n' + \
                      ''.join([str(num + 1) + '. ' + message for num, message in enumerate(self.error_list)])
                QMessageBox.about(self, 'CheckError', err)

    def check_environment(self):
        try:
            time.sleep(2)
            self.process_label.setText("Checking Python Version ...")
            time.sleep(1)
            python_version = float('.'.join(sys.version.split(' ')[0].split('.')[:2]))
            if python_version in [3.6, 3.7, 3.8, 3.9, 3.10]:
                self.process_label.setText("Python Version Checked Successfully...")
        except Exception as e:
            self.process_label.setText("Python Version Check Failure...")
            time.sleep(1)
            self.error_list.append("Please install python 3.6-3.10\n"
                              "Please add python environment variables\n")

        try:
            time.sleep(1)
            self.process_label.setText("Checking API Package ...")
            time.sleep(1)
            from MechEye import Device
            self.process_label.setText("API Package Checked Successfully...")
        except Exception as e:
            self.process_label.setText("API Package Check Failure...")
            # os.system('pip install {}'.format('MechEyeAPI'))
            time.sleep(1)
            # self.process_label.setText("Installing API Package Successful...")
            self.error_list.append("Please install MechEyeAPI Package 'pip install MechEyeAPI'\n")

        try:
            time.sleep(1)
            self.process_label.setText("Check Open3d Package...")
            time.sleep(1)
            import open3d
            self.process_label.setText("Open3d Package Checked Successful...")
        except Exception as e:
            self.process_label.setText("Open3d Package Check Failure...")
            # os.system('pip install {}'.format('Open3d'))
            time.sleep(1)
            # self.process_label.setText("Installing Open3d Package Successful...")
            self.error_list.append("Please install Open3d Package 'pip install Open3d'\n")

        try:
            time.sleep(1)
            self.process_label.setText("Check OpenCV Package...")
            time.sleep(1)
            import cv2
            self.process_label.setText("OpenCV Package Checked Successful...")

        except Exception as e:
            self.process_label.setText("Opencv Package Check Failure...")
            # os.system('pip install {}'.format('opencv-python'))
            time.sleep(2)
            # self.process_label.setText("Installing OpenCV Package Successful...")
            self.error_list.append("Please install CV2 Package 'pip install opencv-python'\n")
        print(self.error_list)
        self.process_label.setText("Finding connected Camera And Start Assistant...")

    def show_single_window(self):
        from UIDesign import single_parameter_window
        self.single_window = single_parameter_window.SingleParameterValueWindow()
        self.single_window.setStyleSheet(qdarkstyle.load_stylesheet_pyqt5())
        self.single_window.show()


if __name__ == '__main__':
    app = QApplication(sys.argv)
    myWin = MyWidget()
    myWin.setStyleSheet(qdarkstyle.load_stylesheet_pyqt5())
    myWin.show()
    sys.exit(app.exec_())

