
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
		// str = filter(line, env);
		cmd = split_cmd(line);
		i = 0;
		while (cmd && cmd[i])
		{
			printf("|%s|\t", cmd[i]);
			i++;
		}
		printf("\n");
		// command = create_cmd(cmd, env);
		command = parse_cmds(cmd, env);
		// printf("filelename: %s\ntype:%d\n", command->files->name, command->files->type);
		while(command)
		{
			while (command && command->files)
			{
				printf("filelename: %s\ntype:%d\n", command->files->name, command->files->type);
				command->files = command->files->next;
			}
			printf("args: ");
			i = 0;
			while (command && command->args && command->args[i])
				printf("%s\t", command->args[i++]);
			printf("\n\n______________________\n\n");
			command = command->next;
		}

		// i = 0;
		// while (cmd && cmd[i])
		// 	free(cmd[i++]);
		// free(cmd);
		// cmd = NULL;
		// free(line);
		// line = NULL;
		// system("leaks a.out");
		// command = create_cmd_linked_list(cmd);
		// print_cmd(command);
	}
}
