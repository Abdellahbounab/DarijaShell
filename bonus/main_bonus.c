/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounab <abounab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:19:56 by abounab           #+#    #+#             */
/*   Updated: 2024/07/06 20:44:50 by abounab          ###   ########.fr       */
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

// all have to be grouped in a single function 
		/*
			1.where first have to trim the first priority
			2.second have to split it using &&, || : t_bonus*
			3.check on syntax errors to announce on each splitted t_bonus* avoid anything in (priority)
			4.split the result by | into t_bonus*->t_cmds*
			5.check on redirections, heredoc and assign to cmds->files
			6.if there is any priority inside splitted cmds , recursive to 1

			7.when t_cmds*->t_bonus* = NULL as the smallest piece of the cmds and priorities , going we send the first t_bonus * to excutions
		

			in excution:
			1. check on heredocs and open them
				going through all the linked list
			2.pipe the cmds that would contain the next since it means piped ones
			3.redirect input and output files
			4.excute the smallest cmds while going back to its parents and so on
			5.first parents are t_bonus* (parent)-> t_cmd* (would contain pipe and redirections)-> t_bonus* (would contain && || relations)-> t_cmd*(smallest cmds)


		*/



t_bonus	*create_bonus(char **tokens)
{
	t_bonus *node;

	if (tokens)
	{
		node = ft_calloc(1, sizeof(t_bonus));
		if (!node)
			return (0);
		node->cmdline = tokens;
		return (node);
	}
	return (0);
}


int	ft_minishell(t_bonus *bonus, t_env *env)
{
	t_bonus *cpy;

	cpy = bonus;
	// it will only trim this case (echo hey), if there is other things than just priority , it wont be trimmed
	ft_bonustrim(bonus->cmdline); // trim the cmdline in bonus->cmdline depends on first '()' and fill the bonus->args
	/*
		if (check_f_l(line_s) == GOOD)
			{
				printf("YOU CAN REMOVE PARO\n");
				bonus->cmdline = remove_f_l(line_s);
			}
	*/
	ft_bonussplit(bonus); // split bonus->args depends on || && outside of  (), and fill the bonus->t_cmd->bonus
	while (cpy)
	{
		// parsing function have to be modified where it would ignore the priorities and anything inside the ()
		// after it would split the cmdline by | and use all the elements inside the bonus->command
		// after if found priorities it would cpy it from '(' to ')' in the command->bonus->cmdline
		// exsample bonus.cmdline :((cat) && echo hello ) > out | echo hey
						// (cat && echo hello ) > out 
								// -> args : NULL
								// -> bonus.cmdline : (cat && echo hello ) => ft_minishell()
								// -> files OUTFILE out
						// echo hey
								// ->args : echo , hey
		bonus->command = parsing(bonus->cmdline, env, &status);
		// redirections would be stored in bonus->t_cmd->files
		// bonus->t_cmd->bonus
		if (bonus->command && status)
			status = 0;
		excution(bonus->command, &env);
		cpy = cpy->next_bonus;
	}
}



int main(int ac, char **av, char **envp)
{
	char *line;
	t_bonus *bonus;
	t_env *env;

	(void)av;
	(void)ac;
	// atexit(leaks);
	
	if (!get_env(&env, envp))
		return (ft_perror("minishell :", "error env", 127));//we have to return the error message too
	while (1)
	{
		ft_signals(1);
		bonus->cmdline = readline("minishell-$ ");
		if (!bonus->cmdline)
			return (free_env(&env), status);
		add_history(bonus->cmdline);

		// bonus->cmdline = line;
		ft_minishell(bonus, env);
		free_cmd(bonus->command);
		// leaks();
	}
	free_env(&env);
}



/*

	struct bonus_excute{
		enum relation = {AND, OR, NONE};
		char *str;
		struct bonus_excute *next;
	};

	1- getting input from user : cat Makefile | wc -l && ((das || export av=hello) && echo $av) | cat
	1 - and check token errors
		 (ls -l && echo hi) > wc | echo hello
			ls -l && echo hi
				ls -l
				echo hi
		
	2- checking if simple command !(&&, ||) OUTSIDE PRIORITIES
		2.1-if yes -> 4
		2.2-if no (contain &&, ||) -> 3
	3- separate ||, && OUTSIDE priorities -> 4
	4- check if | pipe OUTSIDE PRIORITY
	4- check on file redirections 
		4.1- if yes -> separate | -> fork for each + 2
		4.2- if no -> 5
	5- check if () priorities
		5.1- if yes -> trim first () -> 2
		5.2- if no -> 6
	6- excute each .


	cat Makefile | wc -l && ((das || export av=hello) && echo $av) | cat
	struct t_bonus{
		enum type relation{AND, OR, NONE}; NONE
		char *cmdline; "((das || export av=hello) && echo $av) > out | cat << eof"
		t_command *cmd;
			arg:	((das || export av=hello) && echo $av > outfile)
					files = OUTFILE - out
					t_bonus * (separated priorities) : (das || export av=hello) && echo $av
														t_bonus : (das || export av=hello) ,type AND
																t_bonus* :das || export av=hello , type OR
																		t_cmd :arg :das
																				files
																				t_bonus = null
																			
																		t_cmd :arg :export av=hello
																				files
																				t_bonus = null
																		
														t_bonus : echo $av
																t_cmd = arg _ echo $av
																		t_bonus = null
			arg:	cat
					files = HEREDOC - eof
					t_bonus *
		t_bonus *next;
	};

	t_cmd {
		*t_bonus
	}







	repeating algorithm with the command :
	cat Makefile | wc -l && ((das || export av=hello)&& echo $av) | cat
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