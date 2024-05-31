
#include "parsing.h"

void print_cmd(t_command *command)
{
	int i;
	while (command)
	{
		printf("path:%s\n", command->path);
		printf("input_file:%s\n", command->input_files);
		printf("appand:%d\n", command->append);
		printf("output_file:%s\n", command->output_files);
		printf("heredoc:%d\n", command->heredoc);
		printf("limitor:%s\n", command->limitor);
		i = 0;
		printf("args:\t");
		while (command->args && command->args[i] != NULL)
			printf("\e[32m%s\t\e[0m", command->args[i++]);
		command = command->next;
		printf("\n------------------next_command--------------\n");
	}
}

int main()
{
	// // int pid;
	// // char *env[30] = {
	// //   "PATH=/Applications/Visual Studio Code.app/Contents/Resources/app/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Applications/Visual Studio Code.app/Contents/Resources/app/bin"
	// // , "HOME=/Users/achakkaf"
	// // };
	int i;
	char *line;
	char **cmd;
	t_command *command;
	while (1)
	{
		line = readline("minishell-$ ");
		add_history(line);
		cmd = split_cmd(line);
		i = 0;
		printf("split:\t");
		while (cmd && cmd[i][0] != '\n')
			printf("|%s|\t", cmd[i++]);
		printf("\n");
		command = create_cmd_linked_list(cmd);
		print_cmd(command);
	}
}
