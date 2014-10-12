#!/usr/bin/env python
# encoding: utf-8

import cv2
import DIP

img_rgb = cv2.imread('photo.jpg')
cv2.imshow('origin', img_rgb)
img_gray1 = DIP.RGB2GRAY1(img_rgb)
img_gray2 = DIP.RGB2GRAY2(img_rgb)
cv2.imshow('grayscale1', img_gray1)
cv2.imshow('grayscale2', img_gray2)
cv2.waitKey(0)
