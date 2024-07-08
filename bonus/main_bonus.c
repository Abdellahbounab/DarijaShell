/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:19:56 by abounab           #+#    #+#             */
/*   Updated: 2024/07/08 14:21:28 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing/parsing_bonus.h"
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

void leaks(){system("leaks minishell_bonus");}

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
		command = parsing(line, env, &status);
		if (command && status)
			status = 0;
		excution(command, &env);
		free_cmd(command);
		// leaks();
	}
	free_env(&env);
}



/*

	struct bonus_excute{
		enum relation = {AND, OR, NONE};
		t_cmd *command;
		struct bonus_excute *next;
	};

	1- getting input from user : cat Makefile | wc -l && ((das || export av=hello)&& echo $av) | cat
	2- checking if simple command !(&&, ||) OUTSIDE PRIORITIES
		2.1-if yes -> 4
		2.2-if no -> 3
	3- separate ||, && OUTSIDE priorities -> 4
	4- check if | pipe
		4.1- if yes -> separate | -> fork for each + 2
		4.2- if no -> 5
	5- check if () priorities
		5.1- if yes -> separate first () -> 2
		5.2- if no -> 6
	6- excute each 
	

	repeating algorithm with the command : cat Makefile | wc -l && ((das || export av=hello)&& echo $av) | cat
	2 - 2.2
		3 -  cat Makefile | wc -l
			4 - 4.1 - cat Makefile
					2 - 4 - 5 - 6 - excute
				4.1 - wc -l
					2 - 4 - 5 - 6 - excute
		3 - ((das || export av=hello)&& echo $av) | cat
			4 - 4.1 - ((das || export av=hello)&& echo $av)
				2 - 2.1 - 4 - 4.2 - 5 - 5.1
					5.1 - (das || export av=hello)&& echo $av
						2 - 2.2
							3 - (das || export av=hello)
								4 - 4.2 - 5 - 5.1 - das || export av=hello
											2 - 2.2 - 3 - das
														4 - 4.2 - 5 - 5.2 - 6 - excute
													3 - export av=hello
														4 - 4.2 - 5 - 5.2 - 6 - excute
							3 - echo $av
								4 - 4.2 - 5 - 5.2 - 6 - excute
			4 - 4.1 - cat
					2 - 4 - 4.2 - 5 - 5.2 - 6 - excute

	

*/