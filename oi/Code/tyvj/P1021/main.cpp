#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

typedef unsigned long long SizeType;
// typedef long long ValueType;

#define loop(n) for(int __loop__=0;__loop__<n;__loop__++)

int main(int argc, char *argv[]) {
    SizeType length=0;

    unsigned n;
    scanf("%d",&n);

    vector<SizeType> points;
    points.reserve(n);

    SizeType tmp;
    loop(n){
        scanf("%lld",&tmp);
        points.push_back(tmp);
    }

    std::sort(points.begin(),points.end());

    for(unsigned i=n-1;i>=1;i--){
        for(unsigned j=0;j<i;j++){
            length += points[i] - points[j];
        }
    }

    printf("%lld\n", length*2);

    return 0;
}  // function main
