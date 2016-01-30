#include <cstdlib>
#include <string>
#include <vector>
#include <thread>

using namespace std;

void ping(const string &ip){
    string command = "ping -i 0.2 ";
    command += ip;
    system(command.data());
}

int main(int argc, char *argv[]){
    int num = atoi(argv[1]);

    vector<thread> threads(num);
    for(auto &t:threads){
	t = thread(ping, "192.168.6.51");
    }

    for(auto &t:threads){
	t.join();
    }
}
