import zmq
import time
import cv2
# from random import randint

cxt = zmq.Context()
sender = cxt.socket(zmq.PUSH)
sender.bind("tcp://127.0.0.1:5555")

# wait for consumers connected to publisher
# time.sleep(10)

while True:
        # ch = 0xFF & cv2.waitKey(1)
        # if ch == 97:  # A
        #     sender.send(str(time.time()))
        # elif ch == 27:   # ESC
        #     break
        time.sleep(0.5)
        # sender.send_string(str(time.time()))
        sender.send_string("abc")
        # sender.send_pyobj([int(time.time())])
