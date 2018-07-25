/**
 * Author: Andrei Heidelbacher
 * Task: ICC
 * Verif
 */

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

    const char OUT_FILE[] = "icc.out";

    int main() {
      ifstream out(OUT_FILE);
      string score = "";
      getline(out, score);
  cout << score;
  return 0;
}
