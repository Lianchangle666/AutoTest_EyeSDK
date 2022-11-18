#!/usr/bin/python
# -*- coding: utf-8 -*-
import csv


def get_drive_data():
    csv_reader = csv.reader(open('../log_data_drive.csv', 'r', encoding='utf-8'))
    for i in csv_reader:
        print(i)

get_drive_data()
