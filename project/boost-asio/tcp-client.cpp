#include <iostream>
#include <exception>
#include <boost/array.hpp>
#include <boost/asio.hpp>

using namespace std;
using namespace boost;
using namespace boost::asio::ip;

int main(int argc, char *argv[]) {
    try {
        asio::io_service io;

        if (argc < 3) {
            cerr << "Usage: " << argv[0] << " [ADDRESS] [HOST]" << endl;
        }

        tcp::resolver resolver(io);
        tcp::resolver::query query({ argv[1], argv[2] }, "daytime");
        tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
        tcp::socket socket(io);
        asio::connect(socket, endpoint_iterator);

        while (true) {
            boost::array<char, 1024> buffer;
            system::error_code error;

            size_t length = socket.read_some(asio::buffer(buffer), error);

            if (error == asio::error::eof) {
                break;
            } else if (error) {
                throw system::system_error(error);
            }

            cout.write(buffer.data(), length);
        }  // while
    } catch (const std::exception &ex) {
        cerr << ex.what() << endl;
    }

    return 0;
}  // function main
