#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
	int i = 1;
	pid_t pid = fork();

	// Child
	if (pid == 0) {
		--i;
		printf("I am the child and I will die soon! i=%d\n", i);
		exit(42);
	}

	// Parent
	else {
		int status;
		pid_t ret;

		/* waitpid():
			On success, returns the process ID of the child whose state has changed
			If WNOHANG was specified and one or more child(ren) specified by pid exist, but have not yet changed state, then 0 is returned.
    	On error, -1 is returned.
		*/
		// Use this to check if there are any background process running

		ret = waitpid(-1, &status, WNOHANG);
		printf("Child exited with return code %d; i=%d; ret=%d\n", WEXITSTATUS(status), i, ret);
		// child return code is no longer consistent
		// ret shall print out 0
	}
}
