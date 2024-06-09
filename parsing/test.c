
#include "parsing.h"

// void print_cmd(t_command *command)
// {
// 	int i;
// 	while (command)
// 	{
// 		printf("path:%s\n", command->path);
// 		printf("input_file:%s\n", command->input_files);
// 		printf("appand:%d\n", command->append);
// 		printf("output_file:%s\n", command->output_files);
// 		printf("heredoc:%d\n", command->heredoc);
// 		printf("limitor:%s\n", command->limitor);
// 		i = 0;
// 		printf("args:\t");
// 		while (command->args && command->args[i] != NULL)
// 			printf("\e[32m%s\t\e[0m", command->args[i++]);
// 		command = command->next;
// 		printf("\n------------------next_command--------------\n");
// 	}
// }

// space, tab, newline, ‘|’, ‘&’, ‘;’, ‘(’, ‘)’.
int main()
{
	int i;
	char *line;
	char **cmd;
	t_cmd *command;
	t_cmd *cmd_tmp;
	t_cmd *cmd_tmp2;
	t_file *tmp;
	int status;
	// char *str;
	t_env *env;

	status = 0;
	env = malloc(sizeof(t_env));
	env->key = "arg";
	env->value = "ls -la";
	env->next = malloc(sizeof(t_env));
	env->next->key = "arg2";
	env->next->value = "s -l";
	env->next->next = NULL;
	while (1)
	{
		line = readline("minishell-$ ");
		add_history(line);
		if (line[0] == 'e' && line[1] == 'x'&& line[2] == 'i' && line[3] == 't')
			exit(0);
		cmd = split_cmd(line);
		free(line);
		line = NULL;
		command = parse_cmds(cmd, env, &status);
		i = 0;
		while (cmd && cmd[i])
		{
			printf("|%s|\t", cmd[i]);
			free(cmd[i]);
			i++;
		}
		free(cmd);
		cmd = NULL;

		printf("\n");

		cmd_tmp = command;
		tmp = NULL;
		int j;

		while (cmd_tmp)
		{
			while (cmd_tmp && cmd_tmp->files)
			{
				j = 0;
				printf("filenames: \t");
				while (cmd_tmp->files->name && cmd_tmp->files->name[j])
				{
					printf("|%s|\t", cmd_tmp->files->name[j]);
					free(cmd_tmp->files->name[j++]);
				}
				if (cmd_tmp->files->name)
					free(cmd_tmp->files->name[j]);
				printf("type:%d\n", cmd_tmp->files->type);
				free(cmd_tmp->files->name);
				tmp = cmd_tmp->files->next;
				free(cmd_tmp->files);
				cmd_tmp->files = tmp;
			}
			printf("args: ");
			i = 0;
			while (cmd_tmp && cmd_tmp->args && cmd_tmp->args[i])
			{
				printf("|%s|\t", cmd_tmp->args[i]);
				free(cmd_tmp->args[i++]);
			}
			free(cmd_tmp->args);
			cmd_tmp2 = cmd_tmp->next;
			free(cmd_tmp);
			cmd_tmp = NULL;
			printf("\n\n______________________\n\n");
			cmd_tmp = cmd_tmp2;
		}
		free(cmd_tmp);
		// system("leaks a.out");
	}
}

// int main()
// {
// 	char *args[3] = {"ls", "-las", NULL};

// 	int pid;

// 	pid = fork();
// 		if (pid == 0)
// 	{
// 		execv("/bin/ls", args);
// 	}
// 	wait(NULL);

// }
