/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tooles.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:23:00 by achakkaf          #+#    #+#             */
/*   Updated: 2024/06/10 16:01:51 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int set_default(t_cmd **cmd, int *status)
{
	*cmd = malloc(sizeof(t_cmd));
	if (*cmd == NULL)
		return (ERROR);
	(*cmd)->args = NULL;
	(*cmd)->path = NULL;
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
	int i;

	i = 0;
	file = malloc(sizeof(t_file));
	if (file == NULL)
		return (ERROR);
	if (type != here_doc)
		tmp = parsing_extend_var(line[info->cmd_i], info->env, info->cmd->status);
	else
		tmp = line[info->cmd_i];
	file->type = type;
	file->name = parsing_split(tmp);
	if (type != here_doc)
		free(tmp);
	while (file->name && file->name[i])
	{
		tmp = file->name[i];
		file->name[i] = filter(file->name[i]);
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

int check_next(char *str, char *line)
{
	if (str == NULL || ft_strcmp(str, "|") == GOOD)
	{
		ft_putstr_fd("syntax error \n", STDERR_FILENO);
		// ft_putstr_fd(str, STDERR_FILENO);
		// write(STDERR_FILENO, "'\n", 2);
		return (ERROR);
	}
	if (ft_strcmp(str, ">") == 0 || ft_strcmp(str, ">>") == 0 || ft_strcmp(str, "<") == 0 || ft_strcmp(str, "<<") == 0)
	{
		ft_putstr_fd("syntax error \n", STDERR_FILENO);
		// ft_putstr_fd(str, STDERR_FILENO);
		// write(STDERR_FILENO, "'\n", 2);
		return (ERROR);
	}
	return (GOOD);
}

