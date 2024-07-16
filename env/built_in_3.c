/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 09:56:25 by achakkaf          #+#    #+#             */
/*   Updated: 2024/07/16 10:34:41 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "../parsing/parsing.h"
#include "../excution/excution.h"
#include "../types.h"

static void check_newline(t_excute *cmd, int *i, char *flag)
{
	int j;

	j = 0;
	while (cmd->arguments && cmd->arguments[*i])
	{
		if (cmd->arguments[*i][0] == '-')
		{
			j = 1;
			while (cmd->arguments[*i][j] && cmd->arguments[*i][j] == 'n')
				j++;
			if (!cmd->arguments[*i][j] && cmd->arguments[*i][j - 1] != '-')
			{
				(*i)++;
				*flag = 0;
			}
			else
				break;
		}
		else
			break;
	}
}

int builtin_echo(t_excute *cmd)
{
	char flag;
	int i;

	i = 0;
	flag = '\n';
	check_newline(cmd, &i, &flag);
	while (cmd->arguments && cmd->arguments[i])
	{
		write(STDOUT_FILENO, cmd->arguments[i], ft_strlen(cmd->arguments[i]));
		if (cmd->arguments[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	write(STDOUT_FILENO, &flag, 1);
	exit(0);
}

static void cd_home(t_env **env, t_excute *cmds)
{
	if (cmds->arguments[0] && ft_strcmp(cmds->arguments[0], "~"))
	{
		if (chdir(cmds->arguments[0]) < 0)
		{
			perror(cmds->arguments[0]);
			g_status = 1;
			// ft_perror(NULL, "minishell: ", 0);
		}
	}
	else
	{
		if (env_getval(*env, "HOME"))
		{
			if (chdir(env_getval(*env, "HOME")))
			{
				perror(env_getval(*env, "HOME"));
				g_status = 1;
			}
		}
		else
		{
			g_status = 1;
			write(STDERR_FILENO, "minishell: cd: HOME not set\n", 28);
		}
	}
}

int builtin_cd(t_env **env, t_excute *cmds)
{
	char str[100];
	char *current;

	if (env) // funciton that would check the existance of the path
	{
		current = getcwd(str, 100);
		cd_home(env, cmds);
		if (env_getkey(*env, "HOME"))
		{
			if (env_getkey(*env, "PWD"))
				env_export(env, "PWD", getcwd(str, 100), 0);
			if (env_getkey(*env, "OLDPWD"))
				env_export(env, "OLDPWD", current, 0);
		}
		return 1;
	}
	else
		return (0);
}
