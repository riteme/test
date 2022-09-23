#pragma once

#include <string>
#include <fstream>

class Bundle {
public:
    Bundle(const std::string &path) :
        file(path, std::ios::in | std::ios::binary),
        iter(file) {}

    bool read_blob(uint64_t &out_duration_us, std::string &out_blob) {
        if (!file)
            return false;

        union {
            uint8_t data[8];
            uint64_t value;
        } cvt;
        for (size_t i = 0; i < sizeof(cvt); i++) {
            cvt.data[i] = *iter;
            iter++;
        }
        size_t size = cvt.value;
        if (size == 0)
            return false;

        for (size_t i = 0; i < sizeof(cvt); i++) {
            cvt.data[i] = *iter;
            iter++;
        }
        out_duration_us = cvt.value;

        out_blob.clear();
        out_blob.reserve(size);
        for (size_t i = 0; i < size; i++) {
            out_blob.push_back(*iter);
            iter++;
        }
        return true;
    }

private:
    std::ifstream file;
    std::istreambuf_iterator<char> iter;
};
