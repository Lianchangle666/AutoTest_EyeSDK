#!/usr/bin/python
# -*- coding: utf-8 -*-
import os
import threading
import time
import paramiko
from MechEye import Device
from Func_Design.thread_rewrite import CameraThread


def read_cam_type(filepath):
    with open(filepath, 'r', encoding='utf-8') as f:
        return [cam.split('\n')[0] for cam in f.readlines()]


def find_all_camera():
    return [(info.model, info.ip,) for info in Device.get_device_list()]


class SSHConnect(object):
    def __init__(self):
        self.ssh = paramiko.SSHClient()
        self.ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())

    def __connect_ssh(self, hostname, username, password):
        self.ssh.connect(hostname=hostname, username=username, password=password)

    def __execute_commond(self, cmd):
        stdin, stdout, stderr = self.ssh.exec_command(cmd, get_pty=True)
        stdin.write('ubuntu'+'\n')
        result = stdout.read().decode('utf-8')
        print(result)
        time.sleep(0.5)

    def __upload_file(self, winfile, linxfile):
        sftp = self.ssh.open_sftp()
        sftp.put(winfile, linxfile)
        sftp.close()
        time.sleep(0.5)

    def ssh_update_camera(self, hostname, firmwarepath, cameraname):
        try:
            self.__connect_ssh(hostname, 'ubuntu', 'ubuntu')
            self.__execute_commond('sudo systemctl stop mmind')
            self.__upload_file(firmwarepath, '/home/ubuntu/Server/mmind_eye')
            self.__execute_commond('sudo systemctl start mmind')
            return 'Successful: {} -> {} upgrade/degrade successful.'.format(cameraname, hostname)
        except Exception as e:
            return 'Fail: {} -> {} upgrade/degrade fail.'.format(cameraname, hostname)

    def __del__(self):
        self.ssh.close()


def run_all(info_list, firmware_folderpath):
    print('开始')
    result = []
    threads = []

    for ils in info_list:
        if ils[0] in ubuntu_18_cam_template:
            print(ils)
            ssh = SSHConnect()
            firmwarepath = firmware_folderpath + os.sep + 'mmind_eye_Ubuntu18'
            t = CameraThread(ssh.ssh_update_camera, args=(ils[1], firmwarepath, ils[0], ))
            t.start()
            threads.append(t)

        elif ils[0] in NX_cam_template:
            print(ils)
            ssh = SSHConnect()
            firmwarepath = firmware_folderpath + os.sep + 'mmind_eye_Nx'
            t = CameraThread(ssh.ssh_update_camera, args=(ils[1], firmwarepath, ils[0], ))
            t.start()
            threads.append(t)

        elif ils[0] in RK_cam_template:
            print(ils)
            ssh = SSHConnect()
            firmwarepath = firmware_folderpath + os.sep + 'mmind_eye_RK3399'
            t = CameraThread(ssh.ssh_update_camera, args=(ils[1], firmwarepath, ils[0], ))
            t.start()
            threads.append(t)

        elif ils[0] in ubuntu_16_cam_template:
            pass

    for t in threads:
        t.join()
        result.append(t.get_result())
    return result


cur_path = os.getcwd()
ubuntu_18_cam_template = read_cam_type(cur_path + os.sep + 'ubuntu18.CamType')
NX_cam_template = read_cam_type(cur_path + os.sep + 'NX.CamType')
RK_cam_template = read_cam_type(cur_path + os.sep + 'RK.CamType')
ubuntu_16_cam_template = read_cam_type(cur_path + os.sep + 'ubuntu16.CamType')