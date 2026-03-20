
class RestHandler {
public:
    RestHandler(std::shared_ptr<boost::asio::io_context> io_context);
    RestHandler();
    void setup();
    void start();
    void stop();
    boost::asio::awaitable<http::response> handleRequest(http::request request);
    ~RestHandler();
private:
    std::shared_ptr<boost::asio::io_context> io_context;
};
