#!/usr/bin/env python
# encoding: utf-8

import cv2
import DIP

img = cv2.imread('photo.jpg')
cv2.imshow("Origin Image",img)
histImg_r,histImg_g,histImg_b = DIP.HistDraw(img)
cv2.imshow('Origin Red',histImg_r)
cv2.imshow('Origin Green',histImg_g)
cv2.imshow('Origin Blue',histImg_b)
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
equalized_img = cv2.merge((equalized_b,equalized_g,equalized_r))
cv2.imshow("Equalized Image",equalized_img)
cv2.waitKey(0)
