# import zmq
import cv2
import struct
import numpy as np
import matplotlib.pyplot as plt
import time
#%matplotlib inline

cap = cv2.VideoCapture(0)

#publish
# ctx = zmq.Context()
# sock = ctx.socket(zmq.REQ)
# sock.bind("tcp://127.0.0.1:5555")
#sock = ctx.socket(zmq.PAIR)
#sock.bind("tcp://*:5555")

# try:
#     height = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))
#     width = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
#     ndim = 3
    
#     frame_count = 0

#     # img = org_img

#     print("Started Sending")
#     while cap.isOpened():
#         ret, frame = cap.read()
#         # img = cv2.putText(frame, "%03d" % frame_count, (0, height), cv2.FONT_HERSHEY_PLAIN, 2, (255, 255, 255))
#         # img = cv2.flip(img, 0)
#         data = [ np.array([frame_count]), np.array( [height] ), np.array( [width] ), np.array( [ndim] ), frame.data ]
#         sock.send_multipart(data)
#         print("Sended %03d" % frame_count)
#         frame_count += 1
#         time.sleep(3)
# except:
#     sock.close()

frame_count = 0
result = -1
period = 10

print("Started Sending")
while cap.isOpened():
    try:
        # tmp = np.random.randint(2)
        ret, frame = cap.read()
        if not ret:
            break
        # print("{0:03d}: {1}".format(frame_count, tmp))
        # If Sending Trigger activated
        if frame_count % period == -1 % period:
            # img = cv2.putText(img, "%03d" % frame_count, (0, height), cv2.FONT_HERSHEY_PLAIN, 2, (255, 255, 255))
            cv2.imwrite("hub.png", frame)
            with open("new_image.txt", "w") as f:
                print("1", file=f)
        
        # See if Reply has come
        with open("estimated.txt", "r") as f:
            s = int(f.readline().strip())
            if s:
                result = int(f.readline().strip())
                if result < 0:
                    print("Unable to predict menu")
                else:
                    menu = "PUSH_UP" if result == 0 else "SIT_UP"
                    print("{0:03d}: {1}".format(frame_count, menu))
                    frame = cv2.putText(frame, menu, (50, 100), cv2.FONT_HERSHEY_PLAIN, 5, (0, 0, 255), 5)
        if result < 0:
            with open("estimated.txt", "w") as f:
                print("0", file=f)
        #cv2.imshow("", frame)
        #cv2.waitKey(1)
        frame_count += 1
        time.sleep(.01)
    except KeyboardInterrupt:
        # Interrupted, initialize files
        with open("new_image.txt", "w") as f:
            print("0", file=f)
        with open("estimated.txt", "w") as f:
            print("0\n-1", file=f)
        quit()
    except ValueError:
        with open("new_image.txt", "w") as f:
            print("0", file=f)
        with open("estimated.txt", "w") as f:
            print("0\n-1", file=f)
