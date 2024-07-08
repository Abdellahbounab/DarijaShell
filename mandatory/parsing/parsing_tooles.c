/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tooles.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:23:00 by achakkaf          #+#    #+#             */
/*   Updated: 2024/07/08 14:55:01 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "parsing.h"

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
	int expend;

	i = 0;
	expend = 0;
	file = malloc(sizeof(t_file));
	if (file == NULL )
		return (ERROR);
	if (type != HERE_DOC_SIMPLE)
		tmp = parsing_extend_var(line[info->cmd_i], info->env, &expend);
	else
		tmp = line[info->cmd_i];
	if (expend == 1)
		file->name = ft_split(tmp, SPACE);
	else
		file->name = parsing_split(tmp);
	if (type != HERE_DOC_SIMPLE)
		free(tmp);
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



int check_next(char *str)
{
	if (str == NULL || ft_strcmp(str, "|") == GOOD)
	{
		ft_putstr_fd("syntax error\n", STDERR_FILENO);
		status = 1;
		return (ERROR);
	}
	if (ft_strcmp(str, ">") == 0 || ft_strcmp(str, ">>") == 0 || ft_strcmp(str, "<") == 0 || ft_strcmp(str, "<<") == 0)
	{
		ft_putstr_fd("syntax error\n", STDERR_FILENO);
		status = 1;
		return (ERROR);
	}
	return (GOOD);
}

