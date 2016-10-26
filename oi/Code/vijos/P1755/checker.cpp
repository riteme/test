#include <set>
#include <iostream>
#include <algorithm>
#include <initializer_list>

using namespace std;

#define SUDOKU_SIZE 9

bool IsUniqued(const initializer_list<int> &il);
void ReadSudoku(int dataArea[SUDOKU_SIZE][SUDOKU_SIZE]);

int main(/*int argc, char *argv[]*/) {
    cout.sync_with_stdio(false);

    int numberOfSudoku;
    cin >> numberOfSudoku;

    int sudoku[SUDOKU_SIZE][SUDOKU_SIZE];

    for (int cnt = 1; cnt <= numberOfSudoku; cnt++) {
        bool isFailed = false;

        ReadSudoku(sudoku);

        for (int i = 0; i < SUDOKU_SIZE && !isFailed; i++) {
            if (!IsUniqued({ sudoku[i][0], sudoku[i][1], sudoku[i][2], sudoku[i][3], sudoku[i][4],
                             sudoku[i][5], sudoku[i][6], sudoku[i][7], sudoku[i][8] })) {
                isFailed = true;
            }
        }  // for

        for (int j = 0; j < SUDOKU_SIZE && !isFailed; j++) {
            if (!IsUniqued({ sudoku[0][j], sudoku[1][j], sudoku[2][j], sudoku[3][j], sudoku[4][j],
                             sudoku[5][j], sudoku[6][j], sudoku[7][j], sudoku[8][j] })) {
                isFailed = true;
            }
        }  // for

        for (int i = 0; i < SUDOKU_SIZE && !isFailed; i += 3) {
            for (int j = 0; j < SUDOKU_SIZE && !isFailed; j += 3) {
                if (!IsUniqued({ sudoku[i][j], sudoku[i][j + 1], sudoku[i][j + 2], sudoku[i + 1][j],
                                 sudoku[i + 1][j + 1], sudoku[i + 1][j + 2], sudoku[i + 2][j],
                                 sudoku[i + 2][j + 1], sudoku[i + 2][j + 2] })) {
                    isFailed = true;
                }
            }  // for
        }      // for

        if (isFailed) { cout << "Wrong" << endl; } else {
            cout << "Right" << endl;
        }
    }  // for

    return 0;
}  // function main

bool IsUniqued(const initializer_list<int> &il) {
    set<int> numbers;

    numbers.insert(il);

    return numbers.size() == 9;
}

void ReadSudoku(int dataArea[SUDOKU_SIZE][SUDOKU_SIZE]) {
    // i表示竖列，j表示横行
    int tmp;

    for (int i = 0; i < SUDOKU_SIZE; i++) {
        for (int j = 0; j < SUDOKU_SIZE; j++) {
            cin >> tmp;
            dataArea[i][j] = tmp;
        }  // for
    }      // for
}
