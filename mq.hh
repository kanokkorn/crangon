/*
 * File: mq.hh
 * Author: kanokkorn kornkankit <kanokorn@outlook.jp>
 */

#ifndef __MQ_H__
#define __MQ_H__

#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <zmq.hpp>
#include <spdlog/spdlog.h>

void send_mq(void) {
  using namespace std::chrono_literals;
  zmq::context_t context{1};
  zmq::socket_t socket{context, zmq::socket_type::rep};
  socket.bind("tcp://*:5555");
  const std::string data{"World"};
  for (;;) {
    zmq::message_t request;
    socket.recv(request, zmq::recv_flags::none);
    std::cout << "Received " << request.to_string() << std::endl;
    std::this_thread::sleep_for(2000ms);
    socket.send(zmq::buffer(data), zmq::send_flags::none);
  }
}

#endif /* __MQ_H__ */
