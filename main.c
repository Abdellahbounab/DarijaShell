
#include "parsing/parsing.h"
#include "env/env.h"
#include "excution/excution.h"

void print_cmd(t_cmd *command)
{
	t_cmd *cmd_tmp;
	int j;
	int i;

	cmd_tmp = command;
	t_file *tmp_file;
	while (cmd_tmp)
	{
		tmp_file = cmd_tmp->files;
		while (cmd_tmp && tmp_file)
		{
			j = 0;
			printf("filenames: \t");
			while (tmp_file->name && tmp_file->name[j])
				printf("|%s|\t", tmp_file->name[j++]);
			printf("type:%d\n", tmp_file->type);
			tmp_file = tmp_file->next;
		}
		printf("args: ");
		i = 0;
		while (cmd_tmp && cmd_tmp->args && cmd_tmp->args[i])
			printf("|%s|\t", cmd_tmp->args[i++]);
		cmd_tmp = cmd_tmp->next;
		printf("\n------------------next_command--------------\n");
	}
	cmd_tmp = NULL;
}

void	signal_handler(int sig)
{
	(void) sig;
	status = 130;
	// exit status have to be edited depends on if same process or child process
	// have to handle heredoc signal
	write (STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
}

int	ft_signals(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	return 1;
}

int main(int ac, char **av, char **envp)
{
	char *line;
	t_cmd *command;
	// int status;
	t_env *env;

	(void)av;
	(void)ac;
	if (!get_env(&env, envp))
		return (ft_perror("minishell :", "error env", 127));//we have to return the error message too
	ft_signals();
	while (1)
	{
		line = readline("minishell-$ ");
		if (!line)
			return (free_env(&env));
		add_history(line);
		command = parsing(line, env, &status);
		excution(command, &env, &status);
		free_cmd(command);
	}
}

