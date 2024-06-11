
#include "parsing/parsing.h"
#include "env/env.h"

void print_cmd(t_cmd *command)
{
	t_cmd *cmd_tmp;
	int j;
	int i;

	cmd_tmp = command;
	while (cmd_tmp)
	{
		while (cmd_tmp && cmd_tmp->files)
		{
			j = 0;
			printf("filenames: \t");
			while (cmd_tmp->files->name && cmd_tmp->files->name[j])
				printf("|%s|\t", cmd_tmp->files->name[j++]);
			printf("type:%d\n", cmd_tmp->files->type);
			cmd_tmp->files = cmd_tmp->files->next;
		}
		printf("args: ");
		i = 0;
		while (cmd_tmp && cmd_tmp->args && cmd_tmp->args[i])
			printf("|%s|\t", cmd_tmp->args[i++]);
		cmd_tmp = cmd_tmp->next;
		printf("\n------------------next_command--------------\n");
	}
}

int main()
{
	char *line;
	t_cmd *command;
	int status;
	t_env *env;

	status = 0;
	env = NULL;
	while (1)
	{
		line = readline("minishell-$ ");
		add_history(line);
		if (line[0] == 'e' && line[1] == 'x' && line[2] == 'i' && line[3] == 't')
			exit(0);
		command = parsing(line, env, &status);
		// print_cmd(command);
		// free_cmd(command);
		// system("leaks minishell");
	}
}

