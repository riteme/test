#include "testlib.h"

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    double score = ouf.readDouble();
    ouf.readLine();
    ouf.readEof();
    quitp(score);

    return 0;
}  // function main
