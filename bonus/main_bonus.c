/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 11:49:17 by achakkaf          #+#    #+#             */
/*   Updated: 2024/07/02 15:56:49 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "parsing/parsing_bonus.h"
// #include "env/env.h"
// #include "excution/excution.h"

void print_cmd(t_cmd *command)
{
	t_cmd *cmd_tmp;
	t_file *tmp_file;
	int j;
	int i;

	cmd_tmp = command;
	if (cmd_tmp)
		tmp_file = cmd_tmp->files;
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

// void leaks(){system("leaks minishell");}

int main(int ac, char **av, char **envp)
{
	char *line;
	t_cmd *command;
	// t_env *env;

	(void)av;
	(void)ac;
	(void)envp;

	while (1)
	{
		line = readline("minishell-$ ");
		add_history(line);
		// command = parsing(line, NULL, &status);
		char *tmp;
		tmp = wildcard(line);
		printf("%s\n", tmp);
		free(tmp);
		// free_cmd(command);
		// leaks();
	}
	// free_env(&env);
}

// exception export = when using export it doesnt expand and only would be get as it is parsed : ex="'*'"  => env | grep ex => ex='*'
// for variable: if "'*'" or '"*"' it doesnt expand (between two ' " + next to a ' or " just by one char") while using arg

// anything else it does expand when inside at least one ' or " with all commands
// and does expand when it is used not inside any single or double quote everywhere