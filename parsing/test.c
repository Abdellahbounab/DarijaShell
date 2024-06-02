
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
	int i;
	char *line;
	char **cmd;
	int status;
	t_command *command;
	char *var;

	while (1)
	{
		line = readline("minishell-$ ");
		add_history(line);
		cmd = split_cmd(line);
		i = 0;
		while (cmd && cmd[i])
		{
			printf("|%s|\t", cmd[i]);
			if (check_name(cmd[i]) == GOOD)
				printf("valid name\n");
			else
				printf("invalid name\n");

			// if (cmd[i][0] == '\'')
			// {
			// 	var = single_q_filter(cmd[i], 1);
			// 	printf("single quote: %s\n", var);
			// 	free(var);
			// }
			i++;
		}
		printf("\n\n______________________\n\n");

		i = 0;
		while (cmd && cmd[i])
			free(cmd[i++]);
		free(cmd);
		cmd = NULL;
		free(line);
		line = NULL;
		system("leaks a.out");
		// command = create_cmd_linked_list(cmd);
		// print_cmd(command);
	}
}
