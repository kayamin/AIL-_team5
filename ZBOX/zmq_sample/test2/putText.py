import numpy as np
import cv2

frame_count = 0
img = cv2.imread("Lenna.png")
height, width = img.shape[:2]
img = cv2.putText(img, "%03d" % frame_count, (0, height), cv2.FONT_HERSHEY_PLAIN, 2, (255, 255, 255), 3)
cv2.imshow("", img)
cv2.waitKey(0)
cv2.destroyAllWindows()
