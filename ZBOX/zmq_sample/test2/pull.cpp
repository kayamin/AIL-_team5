#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "zmq.hpp"
#include <iostream>

void my_free(void *data, void *hint)
{
    free(data);
}

int main(int argc, char *argv[]) {
    // ZMQの設定
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_PAIR);
    socket.connect("tcp://localhost:5555");

    int cnt = 0;
    int prev_frame = -1;
    int frame_count, rows, cols, type;
    cv::Mat img;
    void *data;

    zmq::message_t rcv_msg;

    while (1){
      // frame_count 
      socket.recv(&rcv_msg, 0);
      frame_count = *(int*)rcv_msg.data();
      
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
      std::cout << "frame_count=" << frame_count << ", rows=" << rows << ", cols=" << cols << ", type=" << type << std::endl;

      if (prev_frame == frame_count){
	std::cout << "frame_count invariant" << std::endl;
	continue;
      }
      
      if (type == 2) {
	img = cv::Mat(rows, cols, CV_8UC1, data);
      }
      else {
	img = cv::Mat(rows, cols, CV_8UC3, data);
      }

      prev_frame = frame_count;
      
      cv::imshow("receive_image", img);
      cv::waitKey(100);
    }

        return 0;
}
