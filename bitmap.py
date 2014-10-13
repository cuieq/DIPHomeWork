#!/usr/bin/env python
# encoding: utf-8

import cv2
import DIP

img = cv2.imread('photo.jpg')
cv2.imwrite('bitmap.bmp',img)
