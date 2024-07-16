/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tooles.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:23:00 by achakkaf          #+#    #+#             */
/*   Updated: 2024/07/16 10:33:59 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	add_back_file(t_cmd *cmd, t_file *file)
{
	t_file	*tmp_file;

	file->next = NULL;
	if (cmd->files == NULL)
		cmd->files = file;
	else
	{
		tmp_file = cmd->files;
		while (tmp_file->next)
			tmp_file = tmp_file->next;
		tmp_file->next = file;
	}
}

int	check_next(char *str)
{
	if (str == NULL || ft_strcmp(str, "|") == GOOD)
	{
		ft_putstr_fd("syntax error\n", STDERR_FILENO);
		g_status = 1;
		return (ERROR);
	}
	if (ft_strcmp(str, ">") == 0 || ft_strcmp(str, ">>") == 0 \
	|| ft_strcmp(str, "<") == 0 || ft_strcmp(str, "<<") == 0)
	{
		ft_putstr_fd("syntax error\n", STDERR_FILENO);
		g_status = 1;
		return (ERROR);
	}
	return (GOOD);
}

void	add_back_cmd(t_cmd *head, t_cmd *next_command)
{
	t_cmd	*tmp;

	if (head == NULL)
		head = next_command;
	else
	{
		tmp = head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = next_command;
	}
}

int	pipe_checker(t_cmd *cmd, char **tokens, t_info *info)
{
	if (!ft_strcmp(tokens[0], "|") || !tokens[info->cmd_i + 1] \
		|| !ft_strcmp(tokens[++(info->cmd_i)], "|"))
	{
		ft_putstr_fd("syntax error\n", STDERR_FILENO);
		g_status = 1;
		free_cmd(cmd);
		return (ERROR);
	}
	return (GOOD);
}

char	*star_magic(char *token, int is_expend, t_env *env)
{
	char	*strwild;

	strwild = NULL;
	if (token && is_expend == 1)
		strwild = var_wildcard(token, env);
	else if (token && ft_strchr(token, '*'))
		strwild = wildcard(token, env);
	else
		strwild = ft_strdup(token);
	return (strwild);
}
