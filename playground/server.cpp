#include <boost/asio.hpp>
#include <iostream>
#include <thread>
#include <atomic>

using boost::asio::ip::tcp;

void handle_client(tcp::socket socket)
{
    try
    {
        while (true)
        {
            char data[1024];
            boost::system::error_code error;
            size_t length = socket.read_some(boost::asio::buffer(data), error);
            if (error == boost::asio::error::eof)
            {
                break; // Connection closed cleanly by peer.
            }
            else if (error)
            {
                throw boost::system::system_error(error); // Some other error.
            }
            std::cout.write(data, length);
            std::cout << std::endl;
        }
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception in thread: " << e.what() << std::endl;
    }
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cerr << "Usage: server <IP> <port>\n";
        return 1;
    }

    try
    {
        boost::asio::io_context io_context;

        tcp::acceptor acceptor(io_context, tcp::endpoint(boost::asio::ip::make_address(argv[1]), std::stoi(argv[2])));

        std::atomic<int> client_count(0);

        while (client_count < 2)
        {
            tcp::socket socket(io_context);
            acceptor.accept(socket);
            std::thread(handle_client, std::move(socket)).detach();
            client_count++;
        }

        std::cout << "Maximum client limit reached. No more connections will be accepted." << std::endl;
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}