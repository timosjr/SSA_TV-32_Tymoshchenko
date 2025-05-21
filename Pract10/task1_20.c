#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define NUM_PROCESSES 5

int main() {
	pid_t pid;
	int i;

	for (i = 0; i < NUM_PROCESSES; ++i) {
		pid = fork();

		if (pid < 0) {
			perror("fork failed");
			exit(EXIT_FAILURE);
		} else if (pid == 0) {
			printf("Proces %d created, PID = %d, PPID = %d\n", i + 1, getpid(), getppid());
			sleep(1);
		} else {
			wait(NULL);
			exit(0);
		}
	}

	printf("Last process (PID = %d) ended\n", getpid());
	return 0;
}
