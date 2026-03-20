

#include <iostream>
#include <boost/asio.hpp>
#include "httpListener.h"

int main() {
    std::cout << "Hello Ashok is here with Sumi!" << std::endl;
    boost::asio::io_context io_context;
    HttpListener listener(io_context, "127.0.0.1", 8080);
    listener.run();
    io_context.run();
    return 0;
}