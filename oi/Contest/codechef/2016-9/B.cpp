#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define NMAX 12345

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        char buffer[NMAX + 10];
        scanf("%s", buffer);
        int n = strlen(buffer);

        int left = 0, right = n - 1;
        bool found = true;
        while (left <= right) {
            if (!found)
                break;

            if (left != right) {
                if (buffer[left] == '.' && buffer[right] == '.')
                    buffer[left] = buffer[right] = 'a';
                else if (buffer[left] == '.')
                    buffer[left] = buffer[right];
                else if (buffer[right] == '.')
                    buffer[right] = buffer[left];
                else if (buffer[left] != buffer[right])
                    found = false;
            } else if (buffer[left] == '.')
                buffer[left] = 'a';

            left++, right--;
        }  // while

        if (!found)
            puts("-1");
        else
            puts(buffer);
    }  // while

    return 0;
}  // function main
