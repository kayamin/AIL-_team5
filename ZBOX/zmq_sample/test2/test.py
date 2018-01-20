import zmq
import cv2
import struct
import numpy as np
import matplotlib.pyplot as plt
#%matplotlib inline

#receive
# ポート設定
conn_str      = "tcp://*:11000"

# ZMQの設定
ctx = zmq.Context()
sock = ctx.socket(zmq.REP)
sock.bind(conn_str)

# ヘッダーの受信（受信できるまで待つ）
byte_rows, byte_cols, byte_mat_type, data=  sock.recv_multipart()

# ヘッダーを解釈する
rows = struct.unpack('i', byte_rows)
cols = struct.unpack('i', byte_cols)
mat_type = struct.unpack('i', byte_mat_type)

#実際に受信する
if mat_type[0] == 0:
        # Gray Scale
        image = np.frombuffer(data, dtype=np.uint8).reshape((rows[0],cols[0]));
else:
        # BGR Color
        image = np.frombuffer(data, dtype=np.uint8).reshape((rows[0],cols[0],3));

        #受信したデータを表示
        plt.imshow(image)
        plt.show()


        ####
        #ここで処理
        image2 = cv2.flip(image, 0)#flip
        ####

        #publish
        conn_str="tcp://localhost:11001"
        ctx = zmq.Context()
        sock = ctx.socket(zmq.REQ)
        sock.connect(conn_str)

        height, width = image2.shape[:2]
        ndim = image2.ndim

        #pythonからは4つのデータを配列として順次送る
        data = [ np.array( [height] ), np.array( [width] ), np.array( [ndim] ), image2.data ]
        sock.send_multipart(data)

        plt.imshow(image2)
