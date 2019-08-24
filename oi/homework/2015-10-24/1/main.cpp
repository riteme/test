#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Task {
    int ID;
    float Time;
    // float WaitedTime;

    bool operator<(const Task &lhs) const { return Time < lhs.Time; }
};  // struct Task

int main(/*int argc, char *argv[]*/) {
    int n;
    cin >> n;

    vector<Task> tasks;

    for (int i = 1; i <= n; i++) {
        Task tmp;
        tmp.ID = i;
        cin >> tmp.Time;

        tasks.push_back(tmp);
    }  // for

    std::sort(tasks.begin(), tasks.end());

    float used = 0.0f;
    float sum = 0.0f;
    for (int i = 0; i < n; i++) {
        used += tasks[i].Time;
        sum += used;
    }  // for

    printf("%.2f\n", sum / n);

    return 0;
}  // function main
