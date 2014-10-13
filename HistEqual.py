#!/usr/bin/env python
# encoding: utf-8

import cv2
import DIP

# 读取图像
img = cv2.imread('photo.jpg')
# 显示原始图像
cv2.imshow("Origin Image",img)
# 获取原始图像三个通道直方图并显示
histImg_r,histImg_g,histImg_b = DIP.HistDraw(img)
cv2.imshow('Origin Red',histImg_r)
cv2.imshow('Origin Green',histImg_g)
cv2.imshow('Origin Blue',histImg_b)
# 分离通道并分别进行处理并计算和显示三个通道直方图
b,g,r = cv2.split(img)
equalized_b = DIP.HistEqualize(b)
equalized_g = DIP.HistEqualize(g)
equalized_r = DIP.HistEqualize(r)
equalized_b_hist = DIP.HistImgCalc(equalized_b,(255,0,0))
equalized_g_hist = DIP.HistImgCalc(equalized_g,(0,255,0))
equalized_r_hist = DIP.HistImgCalc(equalized_r,(0,0,255))
cv2.imshow('Equalized Blue',equalized_b_hist)
cv2.imshow('Equalized Green',equalized_g_hist)
cv2.imshow('Equalized Red',equalized_r_hist)
# 合并直方图均衡后的三个通道并显示结果
equalized_img = cv2.merge((equalized_b,equalized_g,equalized_r))
cv2.imshow("Equalized Image",equalized_img)
cv2.waitKey(0)
