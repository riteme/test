#include <iostream>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std;
using namespace boost;

#ifdef __UNIX__
typedef boost::posix_time::milliseconds milliseconds;
#endif  // IFDEF __UNIX__

int main() {
    asio::io_service io;

    asio::deadline_timer t(io, milliseconds(1000));
    t.async_wait([&t](const system::system_error &) {
        cout << "Hello, world!";
        t.expires_at(t.expires_at() + milliseconds(1000));
    });

    io.run();

    return 0;
}  // function main
