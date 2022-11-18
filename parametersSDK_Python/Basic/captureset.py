#!/usr/bin/python
# -*- coding: utf-8 -*-
import cv2
import numpy as np
import open3d as o3d
from Basic import caminfo
from Util import auxiliary


class CaptureFunction(caminfo.GetCameraInfo):
    def __init__(self, ip):
        super(CaptureFunction, self).__init__(ip)

    def capture_color_map(self, name="colormap"):
        color_map = self.device.capture_color()
        color_name = name + ".png"
        cv2.imwrite(color_name, color_map.data())

    def capture_depth_map(self, name="depthmap"):
        depth_map = self.device.capture_depth()
        depth_name = name + ".tiff"
        cv2.imwrite(depth_name, depth_map.data())

    def capture_point_xyz_map(self, name="pointxyz"):
        point_xyz = self.device.capture_point_xyz()
        point_xyz_data = point_xyz.data()

        point_cloud_xyz = o3d.geometry.PointCloud()
        points_xyz = np.zeros((point_xyz.width() * point_xyz.height(), 3), dtype=np.float64)

        pos = 0
        for dd in np.nditer(point_xyz_data):
            points_xyz[int(pos / 3)][int(pos % 3)] = 0.001 * dd
            pos = pos + 1

        point_cloud_xyz.points = o3d.utility.Vector3dVector(points_xyz)
        o3d.visualization.draw_geometries([point_cloud_xyz])

        file_name = name + ".ply"
        o3d.io.write_point_cloud(file_name, point_cloud_xyz)

    def capture_point_xyz_color_map(self, name="colorpointxyz"):
        color = self.device.capture_color()
        color_data = color.data()

        point_xyz = self.device.capture_point_xyz()

        points_xyz = np.zeros((point_xyz.width() * point_xyz.height(), 3), dtype=np.float64)

        point_cloud_xyz_rgb = o3d.geometry.PointCloud()
        point_cloud_xyz_rgb.points = o3d.utility.Vector3dVector(points_xyz)
        points_rgb = np.zeros((point_xyz.width() * point_xyz.height(), 3), dtype=np.float64)

        pos = 0
        for dd in np.nditer(color_data):
            points_rgb[int(pos / 3)][int(2 - (pos % 3))] = dd / 255
            pos = pos + 1

        file_name = name + ".ply"
        point_cloud_xyz_rgb.colors = o3d.utility.Vector3dVector(points_rgb)
        o3d.visualization.draw_geometries([point_cloud_xyz_rgb])
        o3d.io.write_point_cloud(file_name, point_cloud_xyz_rgb)


if __name__ == '__main__':
    a = CaptureFunction("192.168.20.234")
    a.capture_depth_map()
    a.capture_color_map()
    a.capture_point_xyz_map()
    a.capture_point_xyz_color_map()
