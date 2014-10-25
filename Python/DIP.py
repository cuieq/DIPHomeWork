#!/usr/bin/env python
# encoding: utf-8

from numpy import *
import cv2

# 转换RGB色彩空间到CMY色彩空间
def RGB2CMY(rgb_r, rgb_g, rgb_b):
    # 创建全255通道图像
    byteMat = ones(rgb_r.shape) * 255
    cmy_c = byteMat - rgb_r
    cmy_m = byteMat - rgb_g
    cmy_y = byteMat - rgb_b

    return cmy_c,cmy_m,cmy_y

# 转换CMY色彩空间到CMYK色彩空间
def CMY2CMYK(cmy_c,cmy_m,cmy_y):
    #http://zh.wikipedia.org/wiki/印刷四分色模式
    cmyk_k = ones(cmy_c.shape) * 255
    cmyk_k = fmin(cmyk_k, fmin(cmy_c, fmin(cmy_m, cmy_y)))
    denom = (ones(cmy_c.shape) * 255 - cmyk_k) + ones(cmy_c.shape) * spacing(1)
    cmyk_c = (cmy_c - cmyk_k) / denom
    cmyk_m = (cmy_m - cmyk_k) / denom
    cmyk_y = (cmy_y - cmyk_k) / denom
    cmyk_k = cmyk_k / 255.0
    return cmyk_c,cmyk_m,cmyk_y,cmyk_k

# 经验公式
def RGB2GRAY1(img_rgb):
    rgb_b,rgb_g,rgb_r = cv2.split(img_rgb)
    img_gray = rgb_r*0.299 + rgb_g*0.587 + rgb_b*0.114
    return img_gray/255

# 选取三个通道最大值算法
def RGB2GRAY2(img_rgb):
    rgb_b,rgb_g,rgb_r = cv2.split(img_rgb)
    img_gray = fmax(rgb_r, rgb_g, rgb_b)
    return img_gray

# 二值化算法
def binary(img_gray,threshold):
    img_bin = zeros(img_gray.shape)
    for row in range(img_gray.shape[0]):
        for col in range(img_gray.shape[1]):
            if img_gray[row][col] > threshold / 255.0 :
                img_bin[row][col] = 255
    return img_bin

# 计算梯度直方图并可视化
def HistImgCalc(img_channel,color):
    # 计算直方图
    hist = cv2.calcHist(img_channel,[0],None,[256],[0.0,255.0])
    minVal,maxVal,minLoc,maxLoc = cv2.minMaxLoc(hist)
    histImgChannel = zeros([256,256,3])
    # 将峰值设置在90％位置
    peak = int(0.9*256)
    for h in range(256):
        intensity = int(hist[h]*peak/maxVal)
        cv2.line(histImgChannel,(h,256),(h,256-intensity),color)
    return histImgChannel

# 分别计算三个通道直方图并可视化
def HistDraw(img):
    b,g,r = cv2.split(img)
    HistImg_r = HistImgCalc(r,(0,0,255))
    HistImg_g = HistImgCalc(g,(0,255,0))
    HistImg_b = HistImgCalc(b,(255,0,0))
    return HistImg_r,HistImg_g,HistImg_b

# 计算直方图累加矢量
def HistCum(histImgChannel):
    cumSum = zeros(histImgChannel.shape)
    sumTmp = 0
    for i in range(histImgChannel.shape[0]):
       sumTmp += histImgChannel[i]
       cumSum[i] = sumTmp
    return cumSum

# 直方图均衡
def HistEqualize(imgChannel):
    hist = cv2.calcHist(imgChannel,[0],None,[256],[0.0,255.0])
    histCum = HistCum(hist)
    #　掩盖０元素
    histCumMask = ma.masked_equal(histCum,0)
    #　http://en.wikipedia.org/wiki/Histogram_equalization
    histCumMask = (histCumMask - histCumMask.min())*255/(histCumMask.max()-histCumMask.min())
    #　将掩膜处理掉的元素补为0
    histCum = ma.filled(histCumMask,0).astype('uint8')
    result = histCum[imgChannel]
    return result
