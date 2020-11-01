#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
	for (int i = 0; i < 2; i++) {
		fork();
		printf("-\n");
	}
	wait(NULL);
	wait(NULL);
	return 0;
}
