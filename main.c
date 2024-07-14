/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounab <abounab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 11:49:17 by achakkaf          #+#    #+#             */
/*   Updated: 2024/07/14 22:45:03 by abounab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing/parsing.h"
#include "env/env.h"
#include "excution/excution.h"

void print_cmd(t_cmd *command)
{
	t_cmd *cmd_tmp;
	t_file *tmp_file;
	int j;
	int i;

	cmd_tmp = command;
	if (cmd_tmp)
		tmp_file = cmd_tmp->files;
	if (cmd_tmp == NULL)
		printf("command is NULL\n");
	while (cmd_tmp)
	{
		tmp_file = cmd_tmp->files;
		if (tmp_file == NULL)
			printf("file in command is NULL\n");
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
}

void leaks(){system("leaks -q minishell");}


// exit handle of trimming exit "     42" //DONE
// heredoc have to handle the "delimiter" between "" or ''
// have to handle the relative path since i changed in code
int main(int ac, char **av, char **envp)
{
	char *line;
	t_cmd *command;
	t_env *env;

	(void)av;
	(void)ac;
	// atexit(leaks);
	if (!get_env(&env, envp))
		return (ft_perror("minishell :", "error env", 127));//we have to return the error message too
	while (1)
	{
		ft_signals(1);
		line = readline("minishell-$ ");
		if (!line)
			return (free_env(&env), status);
		add_history(line);
		command = parsing(line, env);
		if (command && status)
			status = 0;
		excution(command, &env);
		free_cmd(command);
	}
	free_env(&env);
}
