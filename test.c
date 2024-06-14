
#include "types.h"

int main(int ac, char **av, char **env)
{
	int fd = open("out", O_CREAT | O_WRONLY, 0740);
	printf("this on is here\n");
	dup2(fd, STDOUT_FILENO); // (fd, stdout)
	// while(1);
	close(fd);
	printf("dup2 in child tester 522522\n");
}
