/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tooles_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:23:00 by achakkaf          #+#    #+#             */
/*   Updated: 2024/07/04 12:44:04 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

int set_default(t_cmd **cmd, int *status)
{
	*cmd = malloc(sizeof(t_cmd));
	if (*cmd == NULL)
		return (ERROR);
	(*cmd)->args = NULL;
	(*cmd)->status = status;
	(*cmd)->files = NULL;
	(*cmd)->next = NULL;
	return (GOOD);
}

void add_back_file(t_cmd *cmd, t_file *file)
{
	t_file *tmp_file;

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

int create_files(t_cmd *cmd, char **line, t_info *info, t_type type)
{
	t_file *file;
	char *tmp;
	char *strwild;
	int i;

	i = 0;
	strwild = NULL;
	file = malloc(sizeof(t_file));
	if (file == NULL)
		return (ERROR);
	if (type != HERE_DOC_SIMPLE)
	{
		tmp = parsing_extend_var(line[info->cmd_i], info->env, info->cmd->status);
		if (tmp && ft_strchr(tmp, ' '))
			strwild = var_wildcard(tmp);
		else if (tmp && ft_strchr(tmp, '*'))
			strwild = wildcard(tmp);
		else
			strwild = ft_strdup(tmp);
	}
	else
		strwild = line[info->cmd_i];
	file->name = parsing_split(strwild);
	if (type != HERE_DOC_SIMPLE)
	{
		free(tmp);
		free(strwild);
	}
	if (file->name && type == HERE_DOC_SIMPLE && (ft_strchr(file->name[i], '\'') || ft_strchr(file->name[i], '"')))
		file->type = HERE_DOC_SPECIAL;
	else if (type == HERE_DOC_SIMPLE)
		file->type = HERE_DOC_SIMPLE;
	else
		file->type = type;
	while (file->name && file->name[i])
	{
		tmp = file->name[i];
		file->name[i] = ft_filter(file->name[i]);
		free(tmp);
		i++;
	}
	add_back_file(cmd, file);
	return (GOOD);
}

void add_back_cmd(t_cmd *head, t_cmd *next_command)
{
	t_cmd *tmp;

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

int check_next(char *str, int *status)
{
	if (str == NULL || ft_strcmp(str, "|") == GOOD)
	{
		ft_putstr_fd("syntax error\n", STDERR_FILENO);
		*status = 1;
		return (ERROR);
	}
	if (ft_strcmp(str, ">") == 0 || ft_strcmp(str, ">>") == 0 || ft_strcmp(str, "<") == 0 || ft_strcmp(str, "<<") == 0)
	{
		ft_putstr_fd("syntax error\n", STDERR_FILENO);
		*status = 1;
		return (ERROR);
	}
	return (GOOD);
}
