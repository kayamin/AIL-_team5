#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
// #include <opencv_lib.hpp>
#include "zmq.hpp"
#include <iostream>

void my_free(void *data, void *hint)
{
        free(data);
}

int main(int argc, char *argv[]) {
        {
                //画像読み込み
                cv::Mat image = cv::imread("Lenna.png", CV_LOAD_IMAGE_COLOR);

                int32_t  info[3];
                info[0] = (int32_t)image.rows;
                info[1] = (int32_t)image.cols;
                info[2] = (int32_t)image.type();

                // ZMQの設定
                zmq::context_t context(1);
                zmq::socket_t socket(context, ZMQ_REQ);
                socket.connect("tcp://localhost:11000");

	    // ヘッダーの生成（height, width, type)
	    for (int i = 0; i < 3; i++) {
	      zmq::message_t msg((void*)&info[i], sizeof(int32_t), NULL);
	      //送信（通信が確立するまで待つ）
	      socket.send(msg, ZMQ_SNDMORE);
	    }

	  // 画像のデータをvoid型としてコピー
void* data = malloc(image.total() * image.elemSize());
memcpy(data, image.data, image.total() * image.elemSize());

// 実際にデータを送る
zmq::message_t msg2(data, image.total() * image.elemSize(), my_free, NULL);
socket.send(msg2);
}

        {
	  // ZMQの設定
	  zmq::context_t context(1);
	  zmq::socket_t socket(context, ZMQ_REP);
	  socket.bind("tcp://*:11001");

	  int cnt = 0;
	  int rows, cols, type;
	  cv::Mat img;
	  void *data;

	  zmq::message_t rcv_msg;

	  //heightの受信
	  socket.recv(&rcv_msg, 0);
	  rows = *(int*)rcv_msg.data();

	  //widthの受信
	  socket.recv(&rcv_msg, 0);
	  cols = *(int*)rcv_msg.data();

	  //chの受信
	  socket.recv(&rcv_msg, 0);
	  type = *(int*)rcv_msg.data();

	  //データの受信
	  socket.recv(&rcv_msg, 0);
	  data = (void*)rcv_msg.data();
	  // printf("rows=%d, cols=%d type=%d\n", rows, cols, type);
	  std::cout << "rows=" << rows << ", cols=" << cols << ", type=" << type << std::endl;

	  if (type == 2) {
	    img = cv::Mat(rows, cols, CV_8UC1, data);
	  }
	  else {
	    img = cv::Mat(rows, cols, CV_8UC3, data);
	  }

	  cv::imshow("receive_image", img);
	  cv::waitKey(0);
	}

return 0;
}
