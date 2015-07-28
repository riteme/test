//
// Copyright 2015 riteme
//

#include <cstdlib>
#include <iostream>
#include <boost/filesystem.hpp>

using namespace std;
using namespace boost;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cout << "Too few parameters!\n";
        return EXIT_FAILURE;
    }

    for (int i = 1;
            i != argc;
            ++i) {
        filesystem::path path(argv[i]);

        cout << path << ": ";

        if (filesystem::exists(path)) {
            if (filesystem::is_regular_file(path)) {
                cout << filesystem::file_size(path);
            }  else if (filesystem::is_directory(path)) {
                cout << "It's a directory";
            } else {
                cout << "Unknown...";
            }
        } else {
            cout << "File not found";
        }

        cout << endl;
    }  // for

    return EXIT_SUCCESS;
}  // function main
