#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

typedef string SequenceType;

list<SequenceType> SearchSequence(int length, const vector<char> &elements);
void Search(int length, const vector<char> &elements, int depth,
            list<SequenceType> &result, SequenceType &tmp);
bool IsVaild(const SequenceType &seq);

int main(/*int argc, char *argv[]*/) {
    ios::sync_with_stdio(false);

    int n;
    cin >> n;

    vector<char> elements = { 'A', 'B', 'C' };
    auto result = SearchSequence(n, elements);

    for (auto &e : result) { cout << e << '\n'; }  // foreach in result
    cout << result.size() << endl;

    return 0;
}  // function main

auto SearchSequence(int length, const vector<char> &elements)
    -> list<SequenceType> {
    list<SequenceType> result;
    SequenceType tmp;

    tmp.reserve(length);

    Search(length, elements, 0, result, tmp);

    return result;
}

void Search(int length, const vector<char> &elements, int depth,
            list<SequenceType> &result, SequenceType &tmp) {
    if (depth == length) {
        if (IsVaild(tmp)) { result.push_back(tmp); }
        return;
    }

    for (int i = 0; i < elements.size(); i++) {
        tmp += elements[i];

        Search(length, elements, depth + 1, result, tmp);

        tmp.pop_back();
    }  // for
}

bool IsVaild(const SequenceType &seq) {
    for (auto beg = seq.begin(); beg < seq.end() - 3; beg++) {
        if (std::equal(beg, beg + 2, beg + 2)) { return false; }
    }  // for

    return true;
}
