import zmq
import cv2
import struct
import numpy as np
import matplotlib.pyplot as plt
import time
#%matplotlib inline

org_img = cv2.imread("./Lenna.png")

#publish
ctx = zmq.Context()
sock = ctx.socket(zmq.PAIR)
sock.bind("tcp://*:5555")

height, width = org_img.shape[:2]
ndim = org_img.ndim

frame_count = 0

# img = org_img

while True:
    img = org_img.copy()
    img = cv2.putText(img, "%03d" % frame_count, (0, height), cv2.FONT_HERSHEY_PLAIN, 2, (255, 255, 255))
    # img = cv2.flip(img, 0)
    data = [ np.array([frame_count]), np.array( [height] ), np.array( [width] ), np.array( [ndim] ), img.data ]
    sock.send_multipart(data)
    frame_count += 1
    time.sleep(3)
