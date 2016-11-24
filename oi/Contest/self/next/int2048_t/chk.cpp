#include "testlib.h"

#include <cmath>

#include <string>

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    int score = ouf.readInt();
    std::string message = ouf.readLine();
    ouf.readEof();

    if (score == 10)
        quitf(_ok, message.data());
    else
        quitp(score / 10.0, message.data());

    return 0;
}
