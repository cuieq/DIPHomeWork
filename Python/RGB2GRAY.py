#!/usr/bin/env python
# encoding: utf-8

import cv2
import DIP

# 读取图像
img_rgb = cv2.imread('photo.jpg')
# 输出原始图像
cv2.imshow('origin', img_rgb)
# 分别采用两种算法进行转换
img_gray1 = DIP.RGB2GRAY1(img_rgb)
img_gray2 = DIP.RGB2GRAY2(img_rgb)
# 输出两种结果
cv2.imshow('grayscale1', img_gray1)
cv2.imshow('grayscale2', img_gray2)
cv2.waitKey(0)
