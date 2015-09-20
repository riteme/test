#include <iostream>

using namespace std;

int main(/*int argc, char *argv[]*/) {
    constexpr int MONEY_EACH_MONTH = 300;

    int cnt = 1;
    int money = 0;
    int bank = 0;
    int budget;

    while (cnt <= 12) {
        cin >> budget;

        money += MONEY_EACH_MONTH;
        int rest = money - budget;

        if (rest < 0) {
            cout << '-' << cnt << endl;
            return 0;
        }

        bank += rest / 100 * 100;
        money -= rest / 100 * 100;
        money -= budget;

        cnt++;
    }  // while

    int final = money + bank + bank / 5;
    cout << final << endl;

    return 0;
}  // function main
