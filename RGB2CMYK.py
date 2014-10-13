#!/usr/bin/env python
# encoding: utf-8

from numpy import *
import DIP
import cv2
import Image

# 读取图像
img_rgb = cv2.imread('photo.jpg')
# 显示原始图像
cv2.imshow('Origin Image',img_rgb)
# 分离RGB通道
rgb_b, rgb_g, rgb_r = cv2.split(img_rgb)
# RGB色彩空间转换为CMY色彩空间
cmy_c, cmy_m, cmy_y = DIP.RGB2CMY(rgb_r, rgb_g, rgb_b)
# CMY色彩空间转换为CMYK色彩空间
cmyk_c, cmyk_m, cmyk_y, cmyk_k = DIP.CMY2CMYK(cmy_c, cmy_m, cmy_y)
# 构建各通道图像
c = Image.fromarray(uint8(cmyk_c*255))
m = Image.fromarray(uint8(cmyk_m*255))
y = Image.fromarray(uint8(cmyk_y*255))
k = Image.fromarray(uint8(cmyk_k*255))
# 合并４个通道
cmyk = Image.merge('CMYK',(c,m,y,k))
# 显示CMYK图像
cmyk.show()
# 输出通道验证
print cmyk.getbands()
cv2.waitKey(0)
