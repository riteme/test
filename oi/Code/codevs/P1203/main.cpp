#include <cmath>
#include <iostream>

using namespace std;

const double EPSILON=1e-8;

int main() {
    ios::sync_with_stdio(false);

    double f1,f2;
    cin>>f1>>f2;
    cout<<(fabs(f1-f2)<=EPSILON?"yes":"no");

    return 0;
}  // function main
