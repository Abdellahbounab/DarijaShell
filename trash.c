/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trash.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 11:21:18 by achakkaf          #+#    #+#             */
/*   Updated: 2024/06/06 15:52:18 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "parsing.h"

// [< , Makefile]                                           ->      filenames[Makefile]
// [<, Makefile, >, output, cat, -e, >, ou ] 				->		filesnames:[Makefile, output, ou], input: Makefile, ouput: ou
// [<, 'Makefile', >, "out"put, cat, -e, >, ou ]			->		filesnames:[Makefile, output, ou], input: Makefile, ouput: ou
// $arg=Make, [<, '$argfile', >, "out"put, cat, -e, >, ou ] ->		filesnames:[Makefile, output, ou], input: Makefile, ouput: ou

// int set_default(t_cmd **cmd)
// {
// 	*cmd = malloc(sizeof(t_cmd));
// 	if (*cmd == NULL)
// 		return (ERROR);
// 	(*cmd)->args = NULL;
// 	(*cmd)->files = NULL;
// 	(*cmd)->next = NULL;
// 	(*cmd)->path = NULL;
// 	(*cmd)->status = NULL;
// 	return (GOOD);
// }

// int check_next(char *str, char *line)
// {
// 	if (str == NULL)
// 	{
// 		ft_putstr_fd("parse error near '", STDERR_FILENO);
// 		ft_putstr_fd(line, STDERR_FILENO);
// 		write(STDERR_FILENO, "'\n", 2);
// 		return (ERROR);
// 	}
// 	return (GOOD);
// }

// int create_files(t_cmd *cmd, char **line, t_env *env, int i, t_type type)
// {
// 	t_file *file;
// 	t_file *tmp_file;
// 	file = malloc(sizeof(t_file));
// 	if (file == NULL)
// 		return (ERROR);
// 	file->name = filter(line[i], env);
// 	file->type = type;
// 	file->next = NULL;
// 	if (cmd->files == NULL)
// 		cmd->files = file;
// 	else
// 	{
// 		tmp_file = cmd->files;
// 		while (tmp_file->next)
// 			tmp_file = tmp_file->next;
// 		tmp_file->next = file;
// 	}
// 	return (GOOD);
// }

// t_cmd *create_cmd(char **line, t_env *env, int *i)
// {
// 	t_cmd *cmd;
// 	char *tmp;

// 	if (line == NULL || set_default(&cmd) == ERROR)
// 		return (NULL);
// 	while (line[*i])
// 	{
// 		if (ft_strcmp(line[*i], "|") == 0)
// 		{
// 			if (check_next(line[++(*i)], "|") == ERROR)
// 				return (NULL);
// 			break;
// 		}
// 		else if (ft_strcmp(line[*i], "<") == 0)
// 		{
// 			if (check_next(line[++(*i)], "<") == ERROR)
// 				//leaks
// 				return (NULL); 
// 			create_files(cmd, line, env, *i, infile);
// 		}
// 		else if (ft_strcmp(line[*i], ">") == 0)
// 		{
// 			if (check_next(line[++(*i)], ">") == ERROR)
// 				return (NULL);
// 			create_files(cmd, line, env, *i, oufile);
// 		}
// 		else if (ft_strcmp(line[*i], ">>") == 0)
// 		{
// 			if (check_next(line[++(*i)], ">>") == ERROR)
// 				return (NULL);
// 			create_files(cmd, line, env, *i, append);
// 		}
// 		else if (ft_strcmp(line[*i], "<<") == 0)
// 		{
// 			if (check_next(line[++(*i)], "<<") == ERROR)
// 				return (NULL);
// 			create_files(cmd, line, env, *i, here_doc);
// 		}
// 		else
// 		{
// 			tmp = filter(line[*i], env);
// 			cmd->args = append_array(cmd->args, tmp);
// 			free(tmp);
// 		}
// 		(*i)++;
// 	}
// 	return (cmd);
// }

// char *var_value(char *line, int *start, int *end, t_env *env)
// {
// 	char *string;
// 	char *var;
// 	char *tmp;
// 	char *value;
// 	t_env *tmp_env;

// 	string = ft_substr(line, *start, *end - *start);
// 	value = NULL;
// 	while (line[*end] == '$')
// 	{
// 		(*end)++;
// 		*start = *end;
// 		while (line[*end] && (ft_isalpha(line[*end]) == GOOD || ft_isdigit(line[*end]) == GOOD || line[*end] == '_'))
// 			(*end)++;
// 		var = ft_substr(line, *start, *end - *start);
// 		tmp_env = env;
// 		while (tmp_env)
// 		{
// 			if (ft_strcmp(tmp_env->key, var) == GOOD)
// 			{
// 				tmp = string;
// 				string = ft_strjoin(string, tmp_env->value);
// 				free(tmp);
// 				break;
// 			}
// 			tmp_env = tmp_env->next;
// 		}
// 		tmp = value;
// 		value = ft_strjoin(value, string);
// 		free(tmp);
// 		free(var);
// 		var = NULL;
// 		free(string);
// 		string = NULL;
// 	}
// 	*start = *end;
// 	return (value);
// }

// char *filter(char *line, t_env *env)
// {
// 	int start;
// 	int end;
// 	char *tmp;
// 	char *tmp_free;
// 	char *tmp_free2;
// 	char *token;
// 	char *var_string;
// 	char *string;
// 	char **var_split;

// 	end = 0;
// 	token = NULL;
// 	var_string = NULL;
// 	string = NULL;
// 	while (line && line[end])
// 	{
// 		if (line[end] == '\'')
// 		{
// 			end++;
// 			start = end;
// 			while (line[end] && line[end] != '\'')
// 				end++;
// 			tmp = ft_substr(line, start, end++ - start);
// 		}
// 		else if (line[end] == '"')
// 		{
// 			end++;
// 			start = end;
// 			while (line[end] && line[end] != '"')
// 			{
// 				if (line[end] == '$')
// 				{
// 					tmp_free = var_string;
// 					var_string = var_value(line, &start, &end, env);
// 					var_string = ft_strjoin(tmp_free, var_string);
// 					free(tmp_free);
// 				}
// 				else
// 					end++;
// 			}
// 			string = ft_substr(line, start, end++ - start);
// 			tmp = ft_strjoin(var_string, string);
// 			free(string);
// 			string = NULL;
// 			free(var_string);
// 			var_string = NULL;
// 		}
// 		else
// 		{
// 			start = end;
// 			while (line[end] && line[end] != '"' && line[end] != '\'')
// 			{
// 				if (line[end] == '$')
// 					var_string = var_value(line, &start, &end, env);
// 				else
// 					end++;
// 			}
// 			string = ft_substr(line, start, end - start);
// 			tmp = ft_strjoin(var_string, string);
// 			free(string);
// 			string = NULL;
// 			free(var_string);
// 			var_string = NULL;
// 		}
// 		tmp_free = token;
// 		token = ft_strjoin(token, tmp);
// 		free(tmp_free);
// 		free(tmp);
// 		tmp = NULL;
// 	}
// 	return (token);
// }

// void add_back(t_cmd *head, t_cmd *next_command)
// {
// 	t_cmd *tmp;

// 	if (head == NULL)
// 		head = next_command;
// 	else
// 	{
// 		tmp = head;
// 		while (tmp->next)
// 			tmp = tmp->next;
// 		tmp->next = next_command;
// 	}
// }

// t_cmd *parse_cmds(char **split_cmd, t_env *env)
// {
// 	int i;
// 	t_cmd *cmd;

// 	i = 0;
// 	cmd = create_cmd(split_cmd, env, &i);
// 	if (cmd == NULL)
// 		return (NULL);
// 	while (cmd && split_cmd && split_cmd[i])
// 	{
// 		add_back(cmd, create_cmd(split_cmd, env, &i));
// 	}
// 	return (cmd);
// }


// done
//  char *without_quote(char *part, t_parsing_info *info)
//  {
//  	char *var_value;
//  	char *before_var;
//  	char *tmp;
// 	var_value = NULL;
// 	before_var = NULL;
// 	info->start = info->end;
// 	while (part[info->end] && part[info->end] != '"' && part[info->end] != '\'')
// 	{
// 		if (part[info->end] == '$')
// 		{
// 			before_var = ft_substr(part, info->start, info->end - info->start);
// 			tmp = before_var;
// 			before_var = ft_strjoin(var_value, before_var);
// 			free(tmp);
// 			free(var_value);
// 			var_value = var_extand(part, info);
// 			tmp = var_value;
// 			var_value = ft_strjoin(before_var, var_value);
// 			free(tmp);
// 			free(before_var);
// 		}
// 		else
// 			info->end++;
// 	}
// 	tmp = ft_substr(part, info->start, info->end - info->start);
// 	before_var = ft_strjoin(var_value, tmp);
// 	free(tmp);
// 	free(var_value);
// 	return (before_var);
// }