
#include "parsing.h"

int main(int ac, char **av, char **env)
{
	int i;
	char *line;
	char **cmd;
	t_command	*command;
	t_env		*environmenet;

	environmenet = NULL;
	get_env(&environmenet, env); //get all env available
	// t_env *tester = env_getkey(environmenet, av[1]); // to get an env depends of its value
	// printf("unset : %d\n", env_unset(&environmenet, av[1])); // to unset a variable in the env
	// env_update(&environmenet, "USER", av[2]);
	// set_signals();//to set the signlas needed
	// env_read(environmenet);
	while (1)
	{
		line = readline("minishell-$ ");
		add_history(line);
		cmd = split_cmd(line);
		command = create_cmd_linked_list(cmd);
		// while (command)
		// {
		// 	printf("append:%d\ninput:%s\noutput:%s\npath:%s\n", command->append, command->input_files, command->output_files, command->path);
		// 	printf("limitor:%s\nheredoc:%d\n", command->limitor, command->heredoc);
		// 	i = 0;
		// 	while (command->args && command->args[i] != NULL)
		// 		printf("|%s|\n", command->args[i++]);
		// 	command = command->next;
		// }
		if (command){
			printf("command->args[0] : %s\n", command->args[0]);
			if (!ft_strcmp(command->args[0], "unset"))
				env_unset(&environmenet, command->args[1]);
			else if (!ft_strcmp(command->args[0], "export"))
				env_export(&environmenet, command->args[1], command->args[2]);
			else if (!ft_strcmp(command->args[0], "env"))
				env_read(environmenet);
		}
	}
	// char *str = malloc (0);
	// int fd;
	// fd = open("parsing.h", O_CREAT | O_RDWR, 0644);
	// dup2(fd, 0);
	// exec_command(NULL, NULL);
	// if (str == NULL)
	// {	printf("sdfds\n");
	// 	return(1);}
}
