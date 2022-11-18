#!/usr/bin/python
# -*- coding: utf-8 -*-

star_count = 60


def show_error(status):
    if status.ok():
        return True
    print("Error Code : {}".format(status.code()),
          ",Error Description: {}".format(status.description()))
    return False


def print_device_info(info):
    cam_name = "Camera Name   |     " + info.model()
    cam_id = "Camera   Id   |     " + info.id()
    hardware_v = "Hardware  V   |     " + info.hardware_version()
    firmware_v = "Firmware  V   |     " + info.firmware_version()
    cam_ip = "Camera   Ip   |     " + info.ip()
    cam_port = "Camera Port   |     " + info.port()

    print("\n" + "=" * star_count + "\n" +
          "| " + cam_name + " " * (star_count - len(cam_name) - 3) + "|\n" +
          "-" * star_count + "\n"
          "| " + cam_id + " " * (star_count - len(cam_id) - 3) + "|\n" +
          "-" * star_count + "\n"
          "| " + hardware_v + " " * (star_count - len(hardware_v) - 3) + "|\n" +
          "-" * star_count + "\n"
          "| " + firmware_v + " " * (star_count - len(firmware_v) - 3) + "|\n" +
          "-" * star_count + "\n"
          "| " + cam_ip + " " * (star_count - len(cam_ip) - 3) + "|\n" +
          "-" * star_count + "\n"
          "| " + cam_port + " " * (star_count - len(cam_port) - 3) + "|\n" +
          "=" * star_count
          )
    return info.model()


def print_dist_coeffs(name, coeffs):
    k1 = "K1: " + str(coeffs.dist_coeffs_k1())
    k2 = " K2: " + str(coeffs.dist_coeffs_k2())
    p1 = "P1: " + str(coeffs.dist_coeffs_p1())
    p2 = " P2: " + str(coeffs.dist_coeffs_p2())
    k3 = "K3: " + str(coeffs.dist_coeffs_k3())

    print("| " + name + " " * (star_count - len(name) - 3) + "|\n" +
          "| " + k1 + k2 + " " * (star_count - len(k1) - len(k2) - 3) + "|\n" +
          "| " + p1 + p2 + " " * (star_count - len(p1) - len(p2) - 3) + "|\n" +
          "| " + k3 + " " * (star_count - len(str(k3)) - 3) + "|\n" +

          "=" * star_count
          )


def print_matrix(name, matrix):
    matri_fxy = "  [" + str(matrix.camera_matrix_fx()) + "," + str(matrix.camera_matrix_fy()) + "]"
    matri_cxy = "  [" + str(matrix.camera_matrix_cx()) + "," + str(matrix.camera_matrix_cy()) + "]"

    print(
          "| " + name + " " * (star_count - len(name) - 3) + "|\n" +
          "| " + matri_fxy + " " * (star_count - len(matri_fxy) - 3) + "|\n" +
          "| " + matri_cxy + " " * (star_count - len(matri_cxy) - 3) + "|\n" +
          "=" * star_count
          )


def print_resolution(resolute):
    color_resolution = "color width×height   |   " + str(resolute.color_width()) + " * " + str(resolute.color_height())
    depth_resolution = "depth width×height   |   " + str(resolute.depth_width()) + " * " + str(resolute.depth_height())

    print(
          "| " + color_resolution + " " * (star_count - len(color_resolution) - 3) + "|\n" +
          "-" * star_count + "\n"
          "| " + depth_resolution + " " * (star_count - len(depth_resolution) - 3) + "|\n" +
          "=" * star_count
          )
    return resolute.color_width(), resolute.color_height(), resolute.depth_width(), resolute.depth_height()