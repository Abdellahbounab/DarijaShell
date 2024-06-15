
#include "types.h"

int main(int ac, char **av, char **env)
{
	// int fd = open("out", O_CREAT | O_WRONLY, 0740);
	int fd[2];

	pipe(fd);
	printf("this on is here\n");
	dup2(fd[0], STDIN_FILENO); // (fd, stdout)
	// while(1);
	// close(fd);
	write(fd[1], "hello world\n", 13);
	char str[13];
	read(0, str, 13);
	printf("str :%s\n", str);
}
