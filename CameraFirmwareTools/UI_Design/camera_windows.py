#!/usr/bin/python
# -*- coding: utf-8 -*-
import os
import sys
import qdarkstyle
import threading
from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
from PyQt5 import QtCore
from PyQt5.QtGui import *
from MechEye import Device
import qtawesome as qta
from Func_Design import ubuntu_ssh
from tabulate import tabulate
from Func_Design.thread_rewrite import CameraThread


def find_camera():
    cam_list = [(info.model, info.ip,) for info in Device.get_device_list()]
    if len(cam_list) != 0:
        cam = [' -> '.join(cam) for cam in cam_list]
        # print(cam)
        return cam


class CameraGradeChange(QWidget):
    def __init__(self, parent=None):
        super(CameraGradeChange, self).__init__(parent)
        self.resize(800, 500)
        self.setWindowTitle('MechEye Upgrade/Degrade Tools')
        self.setWindowFlags(QtCore.Qt.WindowCloseButtonHint)
        self.my_widget()
        self.my_layout()
        self.my_style()
        self.add_list_view_items()

    def my_widget(self):
        self.camera_view = QListView(self)
        self.firm_ware_path_label = QLabel('Firmware Path')
        self.firm_ware_path_edit = QLineEdit()
        self.firm_ware_path_open_bt = QPushButton()
        self.refresh_bt = QPushButton('Refresh Camera List')
        self.upgrade_degrade_bt = QPushButton('upgrade|degrade')
        self.cancel_bt = QPushButton('Cancel')
        self.log_edit = QTextEdit()

    def add_list_view_items(self):
        # self.camera_view.model().removeRow(row)
        self.cam_list = find_camera()
        print(self.cam_list)
        if self.cam_list:
            model = QStandardItemModel()
            for i in self.cam_list:
                model.appendRow(QStandardItem(QIcon(qta.icon('fa.camera', color='white')), i))

            self.camera_view.setModel(model)

    def my_layout(self):
        h_layout = QHBoxLayout()
        h_layout.addWidget(self.camera_view)

        v1_layout = QVBoxLayout()
        v1_layout.addWidget(self.refresh_bt)

        h11_layout = QHBoxLayout()
        h11_layout.addWidget(self.firm_ware_path_label)
        h11_layout.addWidget(self.firm_ware_path_edit)
        h11_layout.addWidget(self.firm_ware_path_open_bt)

        h22_layout = QHBoxLayout()
        h22_layout.addWidget(self.upgrade_degrade_bt)
        h22_layout.addWidget(self.cancel_bt)

        g33_groupbox = QGroupBox('Log', self)
        v331_layout = QVBoxLayout()
        v331_layout.addWidget(self.log_edit)
        g33_groupbox.setLayout(v331_layout)

        v1_layout.addLayout(h11_layout)
        v1_layout.addLayout(h22_layout)
        v1_layout.addWidget(g33_groupbox)

        h_layout.addLayout(v1_layout)
        self.setLayout(h_layout)

    def my_style(self):
        self.camera_view.setEditTriggers(QAbstractItemView.NoEditTriggers)
        self.camera_view.setSelectionMode(QAbstractItemView.MultiSelection)

        self.firm_ware_path_open_bt.setIcon(qta.icon('fa5s.folder', color='white'))
        self.refresh_bt.setIcon(qta.icon('ei.refresh', color='white'))
        self.cancel_bt.setIcon(qta.icon('fa.close', color='white'))
        self.upgrade_degrade_bt.setIcon(qta.icon('ph.arrows-down-up-bold', color='white'))

        self.camera_view.setIconSize(QSize(40, 40))
        self.firm_ware_path_open_bt.setIconSize(QSize(30, 30))

        self.log_edit.setReadOnly(True)


class FunctCameraGradeChange(CameraGradeChange):
    def __init__(self):
        super(FunctCameraGradeChange, self).__init__()
        self.my_signal()
        self.chosen_cam = []  # 被选中的相机

    def my_signal(self):
        self.firm_ware_path_open_bt.clicked.connect(self.choose_firm_folder)
        self.upgrade_degrade_bt.clicked.connect(self.upgrade_degrade)
        self.cancel_bt.clicked.connect(self.close)
        self.camera_view.clicked.connect(self.click_items)
        self.firm_ware_path_edit.textEdited[str].connect(lambda: self.onChange())
        self.refresh_bt.clicked.connect(self.refrash_area)

    def choose_firm_folder(self):
        file_name = QFileDialog.getExistingDirectory(self, 'Find Camera FirmWare Folder', "./")
        self.firm_ware_path_edit.setText(file_name)
        self.log_text()

    def upgrade_degrade(self):
        if self.judge_upgrade_degrade():
            print("开始执行多线程")
            print(self.firm_ware_path_edit.text())
            print(self.chosen_cam)

            results = ubuntu_ssh.run_all(self.chosen_cam, self.firm_ware_path_edit.text())
            for result in results:
                self.log_edit.append('\n' + result)
            QMessageBox.about(self, 'Successful', 'Successful, Camera has been upgrade or degrade !')


    def judge_upgrade_degrade(self):
        try:
            folder_path = self.firm_ware_path_edit.text()
            if len(folder_path) != 0:
                folder_file = os.listdir(folder_path)
                print("file counts: {}, content: {}".format(len(folder_file), folder_file))
                if len(folder_file) == 4:
                    for file in folder_file:
                        print(file)
                        if file not in ['mmind_eye_Nx', 'mmind_eye_RK3399', 'mmind_eye_Ubuntu16', 'mmind_eye_Ubuntu18']:
                            QMessageBox.warning(self, 'Error', 'Make sure the folder contains only:\n'
                                                               '    1. mmind_eye_Nx\n'
                                                               '    2. mmind_eye_RK3399\n'
                                                               '    3. mmind_eye_Ubuntu16\n'
                                                               '    4. mmind_eye_Ubuntu18',
                                                 QMessageBox.Yes, QMessageBox.Yes)
                            return False

                    if not self.chosen_cam:
                        QMessageBox.warning(self, 'Error', 'Select the camera you want to upgrade or degrade !',
                                            QMessageBox.Yes, QMessageBox.Yes)
                    else:
                        print("okkkkkkkk")
                        return True
                else:
                    QMessageBox.warning(self, 'Error', 'Make sure the folder contains only:\n'
                                                       '    1. mmind_eye_Nx\n'
                                                       '    2. mmind_eye_RK3399\n'
                                                       '    3. mmind_eye_Ubuntu16\n'
                                                       '    4. mmind_eye_Ubuntu18',
                                        QMessageBox.Yes, QMessageBox.Yes)
            else:
                QMessageBox.warning(self, 'Error', 'Select the firmware folder path !', QMessageBox.Yes, QMessageBox.Yes)
            return False
        except Exception as e:
            QMessageBox.warning(self, 'Error', 'The firmware path is invalid !', QMessageBox.Yes, QMessageBox.Yes)
            return False

    def click_items(self, qModelIndex):
        cur_cam_ls = self.cam_list[qModelIndex.row()].split(' -> ')
        if cur_cam_ls not in self.chosen_cam:
            self.chosen_cam.append(cur_cam_ls)
        else:
            self.chosen_cam.pop(self.chosen_cam.index(cur_cam_ls))
        print(self.chosen_cam)
        self.log_text()

    def onChange(self):
        self.log_text()

    def log_text(self):
        self.log_edit.setText("Current selection camera: ")

        table_data = ["Camera Name", "IP Address"]
        choose = tabulate(self.chosen_cam, headers=table_data, tablefmt='grid')
        self.log_edit.append(choose)

        firm_ware_path = self.firm_ware_path_edit.text()
        if len(firm_ware_path) == 0:
            self.log_edit.append("\nFirmware path: None")
        else:
            self.log_edit.append("\nFirmware path: {}".format(firm_ware_path))

    def refrash_area(self):
        self.chosen_cam = []
        self.log_edit.clear()
        t = threading.Thread(target=self.add_list_view_items(), args=())
        t.setDaemon(True)
        t.start()


