/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 11:15:13 by achakkaf          #+#    #+#             */
/*   Updated: 2024/06/09 15:49:43 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*						Algorithm of a new parsing
	ar= "s -l"	;	"l"$ar't'a	-> "l"s -l't'a	-> ["l"s -l't'a]	->	[ls -lta]
	ar=			;	"l"$ar't'a	-> "l"'t'a		-> ["l"'t'a]		->	[lta]
	ar= hello	;	$ar			-> hello		-> [hello]			->	[hello]
*/

char *parsing_extend_var(char *string, t_env *env, int *status)
{
	t_parsing_info *info;
	char *tmp;
	char *new_string;
	char *tmp_free;

	if (string == NULL)
		return (NULL);
	new_string = NULL;
	info = malloc(sizeof(t_parsing_info));
	if (info == NULL)
		return (NULL);
	info->end = 0;
	info->start = 0;
	info->env = env;
	tmp = NULL;
	while (string[info->end])
	{
		if (string[info->end] == '\'')
			quote_skip(string, &info->end, '\'');
		if (string[info->end] == '$')
		{
			if (string[info->end + 1] == '?')
			{
				tmp = quation_mark(string, info, tmp, status);
				info->end += 2;
			}
			else 
				tmp = dollar_sign(string, info, tmp);
			info->start = info->end;
		}
		else
			info->end++;
	}
	new_string = ft_substr(string, info->start, info->end - info->start);
	tmp_free = new_string;
	new_string = ft_strjoin(tmp, new_string);
	free(tmp_free);
	free(tmp);
	free(info);
	return (new_string);
}

int blank_quote(char *line, int start, int *end, char ***words_symboles)
{
	while (line[*end] && line[*end] != SPACE && line[*end] != TAB)
	{
		if (line[*end] == '\'')
		{
			if (quote_skip(line, &*end, '\'') == ERROR)
			{
				free_array(words_symboles);
				return (ERROR);
			}
		}
		else if (line[*end] == '"')
		{
			if (quote_skip(line, &*end, '"') == ERROR)
			{
				free_array(words_symboles);
				return (ERROR);
			}
		}
		(*end)++;
	}
	alloc_appand(line, start, *end, words_symboles);
	return (GOOD);
}

char **parsing_split(char *string)
{
	char **words_symboles;
	int start;
	int end;

	end = 0;
	words_symboles = NULL;
	while (string && string[end])
	{
		while (string[end] && (string[end] == SPACE || string[end] == TAB))
			end++;
		start = end;
		if (string[end] || string[end] == '"' || string[end] == '\'')
		{
			if (blank_quote(string, start, &end, &words_symboles))
				return (NULL);
		}
	}
	return (words_symboles);
}

/*-----------------------------------------------------------------------*/

int set_default(t_cmd **cmd, int *status)
{
	*cmd = malloc(sizeof(t_cmd));
	if (*cmd == NULL)
		return (ERROR);
	(*cmd)->args = NULL;
	(*cmd)->files = NULL;
	(*cmd)->next = NULL;
	(*cmd)->path = NULL;
	(*cmd)->status = status;
	return (GOOD);
}

int create_files(t_cmd *cmd, char **line, t_parsing_info *info, t_type type)
{
	t_file *file;
	t_file *tmp_file;
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

t_cmd *create_cmd(char **tokens, t_parsing_info *info, int *status)
{
	t_cmd *cmd;
	char *tmp;
	char **split;
	int i;

	info->file = 0;
	if (tokens == NULL || set_default(&cmd, status) == ERROR)
		return (NULL);
	info->cmd = cmd;
	while (tokens[info->cmd_i])
	{
		if (ft_strcmp(tokens[info->cmd_i], "|") == 0)
		{
			if (tokens[++(info->cmd_i)] == NULL)
			{
				ft_putstr_fd("syntax error near unexpected token `|'\n", STDERR_FILENO);
				return (NULL);
			}
			break;
		}
		if (info->file == 0 && output_files(tokens, cmd, info) == ERROR)
			return (NULL);
		if (info->file == 0 && input_files(tokens, cmd, info) == ERROR)
			return (NULL);
		if (info->file == 0)
		{
			tmp = parsing_extend_var(tokens[info->cmd_i], info->env, info->cmd->status);
			split = parsing_split(tmp);
			free(tmp);
			i = 0;
			while (split && split[i])
			{
				tmp = filter(split[i]);
				cmd->args = append_array(cmd->args, tmp);
				free(tmp);
				free(split[i]);
				i++;
			}
			free(split[i]);
			free(split);
		}
		info->file = 0;
		(info->cmd_i)++;
	}
	return (cmd);
}

t_cmd *parse_cmds(char **split_cmd, t_env *env, int *status)
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
	cmd = create_cmd(split_cmd, info, status);
	if (cmd == NULL)
		return (NULL);
	while (cmd && split_cmd && split_cmd[info->cmd_i])
		add_back(cmd, create_cmd(split_cmd, info, status));
	free(info);
	return (cmd);
}
