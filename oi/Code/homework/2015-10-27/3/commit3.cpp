// TLE

#include <cassert>
#include <iostream>
#include <algorithm>
#include <list>

using namespace std;

struct Item {
    Item(int v) : Value(v), Count(1) {}

    int Value;
    int Count;

    bool operator==(const Item &lhs) const { return Value == lhs.Value; }
    bool operator<(const Item &lhs) const { return Value < lhs.Value; }
};  // struct Item

typedef list<Item>::iterator ItemIterator;
typedef list<int>::iterator Iterator;

int main() {
    ios::sync_with_stdio(false);

    int n;
    cin >> n;

    list<Item> countTable;
    list<int> data;
    for (int i = 0; i < n; i++) {
        int v;
        cin >> v;

        ItemIterator iter =
            std::find(countTable.begin(), countTable.end(), Item(v));

        if (iter == countTable.end())
            countTable.push_back(Item(v));
        else
            iter->Count++;

        data.push_back(v);
    }  // for

    countTable.sort();

    int cnt = 0;
    for (Iterator i = data.begin(); i != data.end(); i++) {
        int sum = 0;

        for (ItemIterator beg = countTable.begin(); beg != countTable.end();
             beg++) {
            if (beg->Value == *i) {
                cnt += sum;
                beg->Count--;

                if (beg->Count <= 0) beg = countTable.erase(beg);
            } else
                sum += beg->Count;
        }  // for
    }      // foreach in data

    cout << cnt;

    return 0;
}  // function main
