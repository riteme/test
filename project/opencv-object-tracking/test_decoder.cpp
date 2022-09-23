#include <fstream>
#include <iostream>

#include "decoder.hpp"

int main() {
    std::ifstream f("horse.mp4");
    std::istreambuf_iterator<char> beg(f), end;
    std::string data(beg, end);
    Decoder decoder(data);

    cv::Mat frame;
    while (decoder.read(frame)) {
        cv::imshow("Show", frame);
        cv::waitKey(10);
    }

    return 0;
}
