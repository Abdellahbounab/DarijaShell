
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

int main()
{
	int i;
	char *line;
	char **cmd;
	t_cmd *command;
	t_cmd *cmd_tmp;
	t_cmd *cmd_tmp2;
	t_file *tmp;
	// int status;
	// char *str;
	t_env *env;

	env = malloc(sizeof(t_env));
	env->key = "arg";
	env->value = "Makefile";
	env->next = malloc(sizeof(t_env));
	env->next->key = "arg2";
	env->next->value = "file2";
	env->next->next = NULL;
	while (1)
	{
		line = readline("minishell-$ ");
		add_history(line);
		if (ft_strcmp("h", line) == 0)
		{
			rl_redisplay();
			continue;
		}
		// str = filter(line, env);
		cmd = split_cmd(line);
		i = 0;
		// while (cmd && cmd[i])
		// {
		// 	printf("|%s|\t", cmd[i]);
		// 	i++;
		// }
		// printf("\n");
		// command = create_cmd(cmd, env);
		command = parse_cmds(cmd, env);
		// printf("filelename: %s\ntype:%d\n", command->files->name, command->files->type);
		// cmd_tmp = command;
		// while (cmd_tmp)
		// {
		// 	while (cmd_tmp && cmd_tmp->files)
		// 	{
		// 		printf("filelename: %s\ntype:%d\n", cmd_tmp->files->name, cmd_tmp->files->type);
		// 		cmd_tmp->files = cmd_tmp->files->next;
		// 	}
		// 	printf("args: ");
		// 	i = 0;
		// 	while (cmd_tmp && cmd_tmp->args && cmd_tmp->args[i])
		// 		printf("%s\t", cmd_tmp->args[i++]);
		// 	printf("\n\n______________________\n\n");
		// 	cmd_tmp = cmd_tmp->next;
		// }
		free(line);
		line = NULL;
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
		while (cmd_tmp)
		{
			while (cmd_tmp && cmd_tmp->files)
			{
				printf("filelename: %s\ntype:%d\n", cmd_tmp->files->name, cmd_tmp->files->type);
				free(cmd_tmp->files->name);
				tmp = cmd_tmp->files->next;
				free(cmd_tmp->files);
				cmd_tmp->files = tmp;
			}
			// free(cmd_tmp->files);
			printf("args: ");
			i = 0;
			while (cmd_tmp && cmd_tmp->args && cmd_tmp->args[i])
			{
				printf("%s\t", cmd_tmp->args[i]);
				free(cmd_tmp->args[i++]);
			}
			free(cmd_tmp->args);
			cmd_tmp2 = cmd_tmp->next;
			free(cmd_tmp);
			cmd_tmp = NULL;
			printf("\n\n______________________\n\n");
			cmd_tmp = cmd_tmp2;
		}
		// system("leaks a.out");
		// free(cmd_->files);
		// command = create_cmd_linked_list(cmd);
		// print_cmd(command);
	}
}
