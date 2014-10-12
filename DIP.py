#!/usr/bin/env python
# encoding: utf-8

from numpy import *
import cv2

def RGB2CMY(rgb_r, rgb_g, rgb_b):
    byteMat = ones(rgb_r.shape) * 255
    cmy_c = byteMat - rgb_r
    cmy_m = byteMat - rgb_g
    cmy_y = byteMat - rgb_b

    return cmy_c,cmy_m,cmy_y

def CMY2CMYK(cmy_c,cmy_m,cmy_y):
    cmyk_k = ones(cmy_c.shape) * 255
    cmyk_k = fmin(cmyk_k, fmin(cmy_c, fmin(cmy_m, cmy_y)))

    denom = (ones(cmy_c.shape) * 255 - cmyk_k) + ones(cmy_c.shape) * spacing(1)
    cmyk_c = (cmy_c - cmyk_k) / denom
    cmyk_m = (cmy_m - cmyk_k) / denom
    cmyk_y = (cmy_y - cmyk_k) / denom
    cmyk_k = cmyk_k / 255.0
    return cmyk_c,cmyk_m,cmyk_y,cmyk_k

def RGB2GRAY1(img_rgb):
    rgb_b,rgb_g,rgb_r = cv2.split(img_rgb)
    img_gray = rgb_r*0.299 + rgb_g*0.587 + rgb_b*0.114
    return img_gray/255

def RGB2GRAY2(img_rgb):
    rgb_b,rgb_g,rgb_r = cv2.split(img_rgb)
    img_gray = fmax(rgb_r, rgb_g, rgb_b)
    return img_gray

def binary(img_gray,threshold):
    img_bin = zeros(img_gray.shape)
    for row in range(img_gray.shape[0]):
        for col in range(img_gray.shape[1]):
            if img_gray[row][col] > threshold / 255.0 :
                img_bin[row][col] = 255
    return img_bin

def HistImgCalc(img_channel,color):
    hist = cv2.calcHist(img_channel,[0],None,[256],[0.0,255.0])
    minVal,maxVal,minLoc,maxLoc = cv2.minMaxLoc(hist)
    histImgChannel = zeros([256,256,3])
    peak = int(0.9*256)
    for h in range(256):
        intensity = int(hist[h]*peak/maxVal)
        cv2.line(histImgChannel,(h,256),(h,256-intensity),color)
    return histImgChannel
def HistDraw(img):
    b,g,r = cv2.split(img)
    print b.shape
    HistImg_r = HistImgCalc(r,(0,0,255))
    HistImg_g = HistImgCalc(g,(0,255,0))
    HistImg_b = HistImgCalc(b,(255,0,0))
    return HistImg_r,HistImg_g,HistImg_b

def HistCum(histImgChannel):
    cumSum = zeros(histImgChannel.shape)
    sumTmp = 0
    for i in range(histImgChannel.shape[0]):
       sumTmp += histImgChannel[i]
       cumSum[i] = sumTmp
    return cumSum

def HistEqualize(imgChannel):
    hist = cv2.calcHist(imgChannel,[0],None,[256],[0.0,255.0])
    histCum = HistCum(hist)
    histCumMask = ma.masked_equal(histCum,0)
    histCumMask = (histCumMask - histCumMask.min())*255/(histCumMask.max()-histCumMask.min())#等同于前面介绍的lut[i] = int(255.0 *p[i])公式
    histCum = ma.filled(histCumMask,0).astype('uint8') #将掩模处理掉的元素补为0
    result = histCum[imgChannel]
    return result
