/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:26:43 by achakkaf          #+#    #+#             */
/*   Updated: 2024/06/06 18:28:54 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int set_default(t_cmd **cmd)
{
	*cmd = malloc(sizeof(t_cmd));
	if (*cmd == NULL)
		return (ERROR);
	(*cmd)->args = NULL;
	(*cmd)->files = NULL;
	(*cmd)->next = NULL;
	(*cmd)->path = NULL;
	(*cmd)->status = NULL;
	return (GOOD);
}

int create_files(t_cmd *cmd, char **line, t_parsing_info *info, t_type type)
{
	t_file *file;
	t_file *tmp_file;

	file = malloc(sizeof(t_file));
	if (file == NULL)
		return (ERROR);
	file->name = filter(line[info->cmd_i], info);
	file->type = type;
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
	return (GOOD);
}

void add_back(t_cmd *head, t_cmd *next_command)
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
	if (str == NULL || ft_strcmp(str, "|") == GOOD )
	{
		ft_putstr_fd("parse error near '", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		write(STDERR_FILENO, "'\n", 2);
		return (ERROR);
	}
	if (ft_strcmp(str, ">") == 0 || ft_strcmp(str, ">>") == 0 || ft_strcmp(str, "<") == 0 || ft_strcmp(str, "<<") == 0)
	{
		ft_putstr_fd("syntax error near unexpected token '", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		write(STDERR_FILENO, "'\n", 2);
		return (ERROR);
	}
	// if (ft_strchr(str, SPACE) || ft_strchr(str, TAB) || line[0] == '\0')
	// {
	// 	ft_putstr_fd("ambiguous redirect\n", STDERR_FILENO);
	// 	return (ERROR);
	// }
	return (GOOD);
}

int output_files(char **line, t_cmd *cmd, t_parsing_info *info)
{
	if (ft_strcmp(line[info->cmd_i], ">") == 0)
	{
		info->file = 1;
		if (check_next(line[++(info->cmd_i)], ">") == ERROR)
			return (ERROR);
		create_files(cmd, line, info, oufile);
	}
	else if (ft_strcmp(line[info->cmd_i], ">>") == 0)
	{
		info->file = 1;
		if (check_next(line[++(info->cmd_i)], ">>") == ERROR)
			return (ERROR);
		create_files(cmd, line, info, append);
	}
	return (GOOD);
}

int input_files(char **line, t_cmd *cmd, t_parsing_info *info)
{
	if (ft_strcmp(line[info->cmd_i], "<") == 0)
	{
		info->file = 1;
		if (check_next(line[++(info->cmd_i)], "<") == ERROR)
			return (ERROR);
		create_files(cmd, line, info, infile);
	}
	else if (ft_strcmp(line[info->cmd_i], "<<") == 0)
	{
		info->file = 1;
		if (check_next(line[++(info->cmd_i)], "<<") == ERROR)
			return (ERROR);
		create_files(cmd, line, info, here_doc);
	}
	return (GOOD);
}

t_cmd *create_cmd(char **line, t_parsing_info *info)
{
	t_cmd *cmd;
	char *tmp;

	info->file = 0;
	if (line == NULL || set_default(&cmd) == ERROR)
		return (NULL);
	while (line[info->cmd_i])
	{
		if (ft_strcmp(line[info->cmd_i], "|") == 0)
		{
			if (line[++(info->cmd_i)] == NULL)
			{
				ft_putstr_fd("syntax error near unexpected token `|'\n", STDERR_FILENO);
				return (NULL);
			}
			break;
		}
		if (info->file == 0 && output_files(line, cmd, info) == ERROR)
			return (NULL);
		if (info->file == 0 && input_files(line, cmd, info) == ERROR)
			return (NULL);
		if (info->file == 0)
		{
			tmp = filter(line[info->cmd_i], info);
			cmd->args = append_array(cmd->args, tmp);
			free(tmp);
		}
		info->file = 0;
		(info->cmd_i)++;
	}
	return (cmd);
}

t_cmd *parse_cmds(char **split_cmd, t_env *env)
{
	t_parsing_info *info;
	t_cmd *cmd;

	if (split_cmd == NULL)
		return (NULL);
	info = malloc(sizeof(t_parsing_info));
	if (info == NULL)
		return (NULL);
	info->cmd_i = 0;
	info->env = env;
	cmd = create_cmd(split_cmd, info);
	if (cmd == NULL)
		return (NULL);
	while (cmd && split_cmd && split_cmd[info->cmd_i])
		add_back(cmd, create_cmd(split_cmd, info));
	free(info);
	return (cmd);
}
