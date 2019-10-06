#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

// Example: prevent parent from exiting when child is running

const int WAIT_FOR_ANY_CHILD = -1;

void myExit(const int exitCode) {
	int status;
	int ret = waitpid(WAIT_FOR_ANY_CHILD, &status, WNOHANG);
	if (ret == 0) {
		// there are still child process(es) running
		fprintf(stderr, "Error: active job running\n");
		return;
	}
	else {
		fprintf(stderr, "Child exited with status %d (child PID: %d)\n",
			WEXITSTATUS(status), ret);
		fprintf(stderr, "Bye... exit code: %d\n", exitCode);
		exit(exitCode);
	}
}

int main() {

	const unsigned int sleepTime = 2;
	pid_t pid = fork();

	if (pid == 0) {
		// child process
		printf("I am child. Sleeping for %d seconds\n", sleepTime);
		sleep(sleepTime);
		pid_t childPid = getpid();
		printf("I am child. I will die now. (child PID: %d)\n", childPid);
		exit(50);
	}
	else {
		// parent process
		myExit(0); // will not exit, as child is still running
		sleep(sleepTime + 1);
		myExit(0); // will exit
	}

	return 0;
}
