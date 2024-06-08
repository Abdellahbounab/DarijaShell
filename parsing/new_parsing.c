/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 11:15:13 by achakkaf          #+#    #+#             */
/*   Updated: 2024/06/08 12:04:20 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

char *single_quote(char *part, t_parsing_info *info)
{
	info->end++;
	info->start = info->end;
	while (part[info->end] && part[info->end] != '\'')
	{
		if (part[info->end] == '$')
			info->var_from = SINGLE_Q;
		info->end++;
	}
	return (ft_substr(part, info->start, info->end++ - info->start));
}

int check_next(char *str, char *line)
{
	if (str == NULL || ft_strcmp(str, "|") == GOOD)
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

char *dollar_name(char *string, t_parsing_info *info, char *var_name)
{
	char *before_dollar;
	char *tmp;

	before_dollar = ft_substr(string, info->start, info->end - info->start);
	printf("before_dollar1:%s\n", before_dollar);
	tmp = before_dollar;
	before_dollar = ft_strjoin(var_name, before_dollar);
	printf("before_dollar2:%s\n", before_dollar);
	free(tmp);
	free(var_name);
	info->start = info->end;
	// var_value = var_extand(string, info);
	// tmp = var_value;
	// var_value = ft_strjoin(before_dollar, var_value);
	// free(tmp);
	// free(before_dollar);
	return (before_dollar);
}

char *double_quote(char *part, t_parsing_info *info)
{
	char *var_value;
	char *string;
	char *tmp;

	string = NULL;
	var_value = NULL;
	info->start = info->end;
	while (part[info->end] && part[info->end] != '"')
	{
		if (part[info->end] == '$')
		{
			if (info->dollar == DOUBLE_Q)
				var_value = dollar_sign(part, info, var_value);
			else
			{
				info->end++;
				var_value = dollar_name(part, info, var_value);
			}
		}
		else
			info->end++;
	}
	tmp = ft_substr(part, info->start, info->end - info->start);
	string = ft_strjoin(var_value, tmp);
	free(tmp);
	free(var_value);
	return (string);
}

char *without_quote(char *part, t_parsing_info *info)
{
	char *var_value;
	char *string;
	char *tmp;

	string = NULL;
	var_value = NULL;
	info->start = info->end;
	while (part[info->end] && (part[info->end] != '"' && part[info->end] != '\''))
	{
		if (part[info->end] == '$')
		{
			info->var_from = WITHOUT;
			if (info->dollar == WITHOUT)
				var_value = dollar_sign(part, info, var_value);
			else
			{
				info->end++;
				var_value = dollar_name(part, info, var_value);
			}
		}
		else
			info->end++;
	}
	tmp = ft_substr(part, info->start, info->end - info->start);
	string = ft_strjoin(var_value, tmp);
	free(tmp);
	free(var_value);
	return (string);
}

char *filter(char *part, t_parsing_info *info)
{
	char *tmp;
	char *tmp_free;
	char *token;

	info->end = 0;
	token = NULL;
	while (part && part[info->end])
	{
		if (part[info->end] == '\'')
			tmp = single_quote(part, info);
		else if (part[info->end] == '"')
		{
			info->end++;
			tmp = double_quote(part, info);
			info->end++;
		}
		else
			tmp = without_quote(part, info);
		tmp_free = token;
		token = ft_strjoin(token, tmp);
		free(tmp_free);
		free(tmp);
		tmp = NULL;
	}
	return (token);
}

int create_files(t_cmd *cmd, char **line, t_parsing_info *info, t_type type)
{
	t_file *file;
	t_file *tmp_file;

	file = malloc(sizeof(t_file));
	if (file == NULL)
		return (ERROR);
	file->name = filter(line[info->cmd_i], info);
	file->text_type = info->var_from;
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

int output_files(char **line, t_cmd *cmd, t_parsing_info *info)
{
	if (ft_strcmp(line[info->cmd_i], ">") == 0)
	{
		info->file = 1;
		info->dollar = DOUBLE_Q;
		if (check_next(line[++(info->cmd_i)], ">") == ERROR)
			return (ERROR);
		create_files(cmd, line, info, oufile);
	}
	else if (ft_strcmp(line[info->cmd_i], ">>") == 0)
	{
		info->file = 1;
		info->dollar = DOUBLE_Q;
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
		info->dollar = DOUBLE_Q;
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
		if (info->file == 0 && input_files(line, cmd, info) == ERROR)
			return (NULL);
		if (info->file == 0 && output_files(line, cmd, info) == ERROR)
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
	info->var_from = -1;
	info->env = env;
	cmd = create_cmd(split_cmd, info);
	if (cmd == NULL)
		return (NULL);
	while (cmd && split_cmd && split_cmd[info->cmd_i])
		add_back(cmd, create_cmd(split_cmd, info));
	free(info);
	return (cmd);
}
