#!/usr/bin/env python
# encoding: utf-8

import DIP
import cv2

img_rgb = cv2.imread('photo.jpg')
rgb_b, rgb_g, rgb_r = cv2.split(img_rgb)
cmy_c, cmy_m, cmy_y = DIP.RGB2CMY(rgb_r, rgb_g, rgb_b)
cmyk_c, cmyk_m, cmyk_y, cmyk_k = DIP.CMY2CMYK(cmy_c, cmy_m, cmy_y)
cmyk = cv2.merge((cmyk_c, cmyk_m, cmyk_y, cmyk_k))
