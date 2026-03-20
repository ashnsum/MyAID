#pragma once

#include <boost/asio.hpp>
#include <boost/asio/awaitable.hpp>
#include <boost/asio/strand.hpp>
#include <memory>
#include <string>
#include <iostream>
#include <queue>
#include <functional>

class HttpListener {
private:
    boost::asio::io_context& io_context_;
    boost::asio::ip::tcp::acceptor acceptor_;
    boost::asio::strand<boost::asio::io_context::executor_type> strand_;
    std::queue<std::string> response_queue_;
    bool sending_ = false;
    std::string ip_;
    int port_;

    void sendNextResponse(boost::asio::ip::tcp::socket& socket);

public:
    HttpListener(boost::asio::io_context& io_context, const std::string& ip = "127.0.0.1", int port = 8080);
    void run();

private:
    boost::asio::awaitable<void> listen();
    boost::asio::awaitable<void> restHandler(const std::string& request, std::function<void(std::string)> callback);
};

HttpListener::HttpListener(boost::asio::io_context& io_context, const std::string& ip, int port)
    : io_context_(io_context), acceptor_(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::make_address(ip), port)), strand_(boost::asio::make_strand(io_context)), ip_(ip), port_(port) {}

void HttpListener::run() {
    boost::asio::co_spawn(io_context_, listen(), boost::asio::detached);
}

boost::asio::awaitable<void> HttpListener::listen() {
    auto socket = co_await acceptor_.async_accept(boost::asio::use_awaitable);

    for (;;) {
        try {
            boost::asio::streambuf buffer;
            co_await boost::asio::async_read_until(socket, buffer, "\r\n\r\n", boost::asio::use_awaitable);
            std::string request(boost::asio::buffer_cast<const char*>(buffer.data()), buffer.size());

            // Spawn restHandler asynchronously with callback
            auto response_callback = [this, &socket](std::string response) {
                boost::asio::post(strand_, [this, response = std::move(response), &socket]() {
                    response_queue_.push(std::move(response));
                    if (!sending_) {
                        sending_ = true;
                        sendNextResponse(socket);
                    }
                });
            };
            boost::asio::co_spawn(io_context_, restHandler(request, std::move(response_callback)), boost::asio::detached);

            buffer.consume(buffer.size());
        } catch (const boost::system::system_error& e) {
            if (e.code() == boost::asio::error::eof) break;
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
    socket.close();
}

void HttpListener::sendNextResponse(boost::asio::ip::tcp::socket& socket) {
    if (response_queue_.empty()) {
        sending_ = false;
        return;
    }
    std::string response = std::move(response_queue_.front());
    response_queue_.pop();

    boost::asio::async_write(socket, boost::asio::buffer(response),
        boost::asio::bind_executor(strand_, [this, &socket](boost::system::error_code ec, std::size_t) {
            if (!ec) {
                sendNextResponse(socket);
            } else {
                std::cerr << "Send error: " << ec.message() << std::endl;
            }
        }));
}

boost::asio::awaitable<void> HttpListener::restHandler(const std::string& request, std::function<void(std::string)> callback) {
    // Simulate async processing (e.g., I/O or computation)
    // In real code, this could co_await other async operations
    std::string response = "HTTP/1.1 200 OK\r\nContent-Length: 13\r\n\r\nHello, Async!";
    callback(std::move(response));
    co_return;
}



httpListener::Run() {
    if (listen(serverSocket, 5) == -1) {
        throw std::runtime_error("Failed to listen on socket");
    }
    while (true) {
        int clientSocket = accept(serverSocket, nullptr, nullptr);
        if (clientSocket == -1) {
            throw std::runtime_error("Failed to accept connection");
        }
        HandleRequest(clientSocket);
        SendResponse();
        close(clientSocket);
    }
}

httpListener::httpListener(std::shared_ptr<boost::asio::io_context> io_context) : ip("127.0.0.1"), port(8080), io_context(io_context) 
{ 
    setup(); 
}

httpListener::~httpListener() {}
