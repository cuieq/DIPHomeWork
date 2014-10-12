#!/usr/bin/env python
# encoding: utf-8

import cv2
import DIP

def action(x):
    pass

img = cv2.imread('photo.jpg')
cv2.imshow('origin image',img)
cv2.namedWindow('binary')
cv2.createTrackbar('Threshold','binary',0,255,action)
cv2.setTrackbarPos('Threshold','binary',127)
img_gray = DIP.RGB2GRAY1(img)

while(1):
    k = cv2.waitKey(1) & 0xFF
    if k ==27:
        break

    threshold = cv2.getTrackbarPos('Threshold','binary')
    img_bin = DIP.binary(img_gray,threshold)
    cv2.imshow('binary',img_bin)

cv2.waitKey(0)
