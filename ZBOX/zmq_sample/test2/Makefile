CV_FLG := `pkg-config --cflags opencv` `pkg-config --libs opencv`
ZMQ_FLG := -lzmq

main: pull.cpp
	g++ pull.cpp -std=c++11 $(ZMQ_FLG) $(CV_FLG)
