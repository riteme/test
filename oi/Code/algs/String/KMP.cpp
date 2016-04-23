#include <iostream>
#include <string>
#include <vector>

using namespace std;

void ComputePrefixArray(const string &pattern, vector<int> &prefix) {
    prefix.resize(pattern.size() + 1);
    prefix[0] = prefix[1] = 0;

    for (auto i = 1; i < pattern.size(); i++) {
        int k = prefix[i];
        while (k != 0 && pattern[k] != pattern[i]) {
            k = prefix[k];
        }  // while

        if (pattern[k] == pattern[i]) {
            k++;
        }

        prefix[i + 1] = k;
    }
}

int KmpSearch(const string &pattern, const string &text) {
    vector<int> prefix;
    ComputePrefixArray(pattern, prefix);

    for (auto i : prefix) {
        cout << i << " ";
    }  // foreach in prefix
    cout << endl;

    size_t j = 0;
    for (auto i = 0; i < text.size(); i++) {
        cout << "i = " << i << ", j = " << j << endl;
        while (j != 0 && pattern[j] != text[i]) {
            j = prefix[j];
            cout << "j jumps to " << j << endl;
        }  // while

        if (pattern[j] == text[i]) {
            cout << "matched at text[" << i << "] & pattern[" << j << "]"
                 << endl;
            j++;
        }

        if (j == pattern.size()) {
            return i - j + 1;
        }
    }

    return -1;
}

int main() {
    string pattern;
    cin >> pattern;

    string text;
    while (cin >> text) {
        cout << KmpSearch(pattern, text) << endl;
    }  // while

    return 0;
}  // function main
