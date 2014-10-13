#!/usr/bin/env python
# encoding: utf-8

import cv2
import DIP

# Trackbar触发函数
def action(x):
    pass

# 读取图像
img = cv2.imread('photo.jpg')
# 输出原始图像
cv2.imshow('origin image',img)
# 创建输出窗口和Trackbar
cv2.namedWindow('binary')
cv2.createTrackbar('Threshold','binary',0,255,action)
# 设置滚动球初始位置(初始阈值)
cv2.setTrackbarPos('Threshold','binary',127)
# 转换为灰度图像
img_gray = DIP.RGB2GRAY1(img)

# 根据轨迹球动态调整阈值输出结果
while(1):
    k = cv2.waitKey(1) & 0xFF
    if k ==27:
        break

    threshold = cv2.getTrackbarPos('Threshold','binary')
    img_bin = DIP.binary(img_gray,threshold)
    cv2.imshow('binary',img_bin)

cv2.waitKey(0)
