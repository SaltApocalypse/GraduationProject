#include <boost/asio.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include <ctime>

using boost::asio::ip::tcp;

int main(int argc, char *argv[])
{
    if (argc < 3 || argc > 4)
    {
        std::cerr << "Usage: client <IP> <port> [name]\n";
        return 1;
    }

    try
    {
        boost::asio::io_context io_context;

        tcp::resolver resolver(io_context);
        tcp::resolver::results_type endpoints = resolver.resolve(argv[1], argv[2]);

        tcp::socket socket(io_context);
        boost::asio::connect(socket, endpoints);

        std::string name = (argc == 4) ? argv[3] : socket.remote_endpoint().address().to_string();

        while (true)
        {
            auto now = std::chrono::system_clock::now();
            std::time_t now_time = std::chrono::system_clock::to_time_t(now);
            std::string message = name + ": " + std::ctime(&now_time);

            boost::asio::write(socket, boost::asio::buffer(message));

            std::this_thread::sleep_for(std::chrono::seconds(5));
        }
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}