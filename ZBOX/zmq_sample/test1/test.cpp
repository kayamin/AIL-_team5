#include <zmq.hpp>
#include <iostream>
#include <string>

int main()
{
  zmq::context_t context(1);
  zmq::socket_t receiver(context, ZMQ_PULL);
  receiver.connect("tcp://127.0.0.1:5555");

  zmq::message_t rcv_msg;
  int time;

  while(1){
    receiver.recv(&rcv_msg, 0);
    std::string smessage(static_cast<char*>(rcv_msg.data()), rcv_msg.size());
    std::cout << smessage << std::endl;
  }
  return 0;
}
  
