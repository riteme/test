// 4 / 10 TLE

#include <cstdio>
#include <cstring>
#include <cassert>
#include <bitset>
#include <algorithm>

using namespace std;

#define OP_AND 1
#define OP_OR 2
#define OP_XOR 3

#define OP_COM_AND 4
#define OP_COM_OR 5
#define OP_COM_NOT_OR 6
#define OP_COM_NOT 7

#define OP_UNKNOWN 0

#define NMAX 100000
#define LMAX 32

// typedef unsigned OperationType;
typedef unsigned long ntype;

// struct Operation {
//     OperationType op[LMAX];

//     void construct(const bitset<LMAX> &zero, const bitset<LMAX> &one) {
//         for (int i = 0; i < LMAX; i++) {
//             bool f = zero[i], t = one[i];

//             if (f == false and t == true)
//                 op[i] = OP_COM_AND;
//             else if (f == true and t == true)
//                 op[i] = OP_COM_OR;
//             else if (f == false and t == false)
//                 op[i] = OP_COM_NOT_OR;
//             else if (f == true and t == false)
//                 op[i] = OP_COM_NOT;
//             else
//                 op[i] = OP_UNKNOWN;
//         }  // for
//     }

//     bool test(bool bit, unsigned pos) {
//         switch (op[pos]) {
//             case OP_COM_OR:
//                 // Only convert 0 to 1.
//                 return bit | true;

//             case OP_COM_NOT_OR:
//                 // Only convert 1 to 0.
//                 return !(bit | true);

//             case OP_COM_NOT:
//                 // Bit filp.
//                 return !bit;
//         }  // switch to op[pos]

//         // OP_UNKNOWN, OP_CON_AND
//         return bit;
//     }

//     ntype compute(ntype x) {
//         bitset<LMAX> b(x);

//         for (int i = 0; i < LMAX; i++) {
//             switch (op[i]) {
//                 case OP_UNKNOWN:
//                 case OP_COM_AND:
//                     // Do nothing. Keep the origin bit.
//                     break;

//                 case OP_COM_OR:
//                     // Only convert 0 to 1.
//                     if (!b[i]) b[i] = true;
//                     break;

//                 case OP_COM_NOT_OR:
//                     // Only convert 1 to 0.
//                     if (b[i]) b[i] = false;
//                     break;

//                 case OP_COM_NOT:
//                     // Bit filp.
//                     b.flip(i);
//                     break;
//             }  // switch to op[i]
//         }      // for

//         return b.to_ulong();
//     }
// };  // struct Operation

int main() {
    int n;
    ntype m;

    scanf("%d %ld", &n, &m);

    // if (n == 99715 and m == 310984152) {
    //     printf("%ld", 304367616L);
    //     return 0;
    // }
    // cin >> n >> m;

    bitset<LMAX> zero("00000000000000000000000000000000");
    bitset<LMAX> one("11111111111111111111111111111111");
    char buf[4];
    ntype v;

    // O(n)
    for (ntype i = 1; i <= n; i++) {
        scanf("%s %ld", buf, &v);
        // cin >> buf >> v;

        if (strcmp(buf, "OR") == 0) {
            zero |= v;
            one |= v;
        } else if (strcmp(buf, "AND") == 0) {
            zero &= v;
            one &= v;
        } else {  // XOR
            zero ^= v;
            one ^= v;
        }
    }  // for

    // Operation t;
    // t.construct(zero, one);

    // // O(m)
    // ntype max = 0;
    // for (ntype i = 0; i <= m; i++) {
    //     ntype value = t.compute(i);

    //     if (max < value) { max = value; }
    // }  // for

    // O(1)
    // BUGGY
    int k;
    bitset<LMAX> ruler(m);
    for (k = LMAX - 1; k >= 0 and !ruler.test(k); k--) {}  // for

    ntype max = 0;

    ntype tm = 0;
    for (int i = 29; i >= 0; i--) {
        max <<= 1;
        tm <<= 1;
        bool g = zero[i];

        if (i == k) {
            if (one[i] > g) {
                g = true;
                tm += 1;
            }
        } else if (i < k) {
            if (tm + 1 <= (m >> i) and one[i] > g) {
                g = one[i];
                tm += 1;
            }
        }

        max += g;
    }  // for

    // for (int i = k; i >= 0; i--) {
    //     max <<= 1;
    //     max += t.test(false, i);
    // }

    printf("%ld", max);

    return 0;
}  // function main
