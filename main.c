#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

void sighandler (int signo) {
	if (signo == SIGINT) {
		int fd = open ("./log.txt", O_WRONLY | O_CREAT | O_APPEND, 0777);
		char message[] = "Program exited due to SIGINT\n";
		write (fd, message, sizeof(message));
		close(fd);
		exit(0);
	}
	if (signo == SIGUSR1) {
		printf ("Parent process PID: %d\n", getppid());
	}
}

int main() {
	signal (SIGINT, sighandler);
	signal (SIGUSR1, sighandler);
	
	while(1) {
		printf ("Current process PID: %d\n", getpid());
		sleep(1);
	}
	
	return 0;
}

