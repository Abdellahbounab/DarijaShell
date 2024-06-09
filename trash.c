/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trash.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 11:21:18 by achakkaf          #+#    #+#             */
/*   Updated: 2024/06/09 11:54:42 by achakkaf         ###   ########.fr       */
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


// static int	cwords(const char *s)
// {
// 	int	i;
// 	int	count;
// 	int	inword;

// 	i = 0;
// 	inword = 1;
// 	count = 0;
// 	while (s[i])
// 	{
// 		while ((s[i] == TAB || s[i] == SPACE ) && s[i])
// 			i++;
// 		while ((s[i] != TAB || s[i] != SPACE ) && s[i])
// 		{
// 			if (inword)
// 			{
// 				count++;
// 				inword = 0;
// 			}
// 			i++;
// 		}
// 		inword = 1;
// 	}
// 	return (count);
// }

// static char	*mysubstr(const char *s, int start, int len)
// {
// 	int		i;
// 	char	*str;

// 	i = 0;
// 	str = malloc(sizeof(char) * (len + 1));
// 	if (str)
// 	{
// 		while (i < len)
// 		{
// 			str[i] = s[start + i];
// 			i++;
// 		}
// 		str[i] = '\0';
// 	}
// 	return (str);
// }

// static char	**ft_free(char **strings, int i)
// {
// 	int	j;

// 	j = 0;
// 	if (strings)
// 	{
// 		while (j <= i)
// 		{
// 			free(strings[j]);
// 			j++;
// 		}
// 		free(strings);
// 	}
// 	return (NULL);
// }

// static char	**splitp1(char **strings, const char *s)
// {
// 	int		i;
// 	int		j;
// 	int		s_i;

// 	s_i = 0;
// 	i = 0;
// 	strings = malloc(sizeof(char *) * (cwords(s) + 1));
// 	while (s[i] && strings)
// 	{
// 		while ((s[i] == TAB || s[i] == SPACE ) && s[i])
// 			i++;
// 		j = i;
// 		if (!s[i])
// 			break ;
// 		while ((s[i] != TAB || s[i] != SPACE ) && s[i])
// 			i++;
// 		strings[s_i] = mysubstr(s, j, i - j);
// 		if (!(strings[s_i]))
// 			return (ft_free(strings, s_i));
// 		s_i++;
// 	}
// 	if (strings)
// 		strings[s_i] = NULL;
// 	return (strings);
// }

// char	**split_by_space_tab(const char *s)
// {
// 	char	**strings;

// 	strings = NULL;
// 	if (!s)
// 		return (NULL);
// 	strings = splitp1(strings, s);
// 	return (strings);
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

// char *single_quote(char *part, t_parsing_info *info)
// {
// 	info->end++;
// 	info->start = info->end;
// 	while (part[info->end] && part[info->end] != '\'')
// 	{
// 		if (part[info->end] == '$')
// 			info->var_from = SINGLE_Q;
// 		info->end++;
// 	}
// 	return (ft_substr(part, info->start, info->end++ - info->start));
// }

// int check_next(char *str, char *line)
// {
// 	if (str == NULL || ft_strcmp(str, "|") == GOOD)
// 	{
// 		ft_putstr_fd("parse error near '", STDERR_FILENO);
// 		ft_putstr_fd(str, STDERR_FILENO);
// 		write(STDERR_FILENO, "'\n", 2);
// 		return (ERROR);
// 	}
// 	if (ft_strcmp(str, ">") == 0 || ft_strcmp(str, ">>") == 0 || ft_strcmp(str, "<") == 0 || ft_strcmp(str, "<<") == 0)
// 	{
// 		ft_putstr_fd("syntax error near unexpected token '", STDERR_FILENO);
// 		ft_putstr_fd(str, STDERR_FILENO);
// 		write(STDERR_FILENO, "'\n", 2);
// 		return (ERROR);
// 	}
// 	// if (ft_strchr(str, SPACE) || ft_strchr(str, TAB) || line[0] == '\0')
// 	// {
// 	// 	ft_putstr_fd("ambiguous redirect\n", STDERR_FILENO);
// 	// 	return (ERROR);
// 	// }
// 	return (GOOD);
// }

// char *dollar_name(char *string, t_parsing_info *info, char *var_name)
// {
// 	char *before_dollar;
// 	char *tmp;

// 	info->end++;
// 	before_dollar = ft_substr(string, info->start, info->end - info->start);
// 	printf("before_dollar1:%s\n", before_dollar);
// 	tmp = before_dollar;
// 	before_dollar = ft_strjoin(var_name, before_dollar);
// 	printf("before_dollar2:%s\n", before_dollar);
// 	free(tmp);
// 	free(var_name);
// 	info->start = info->end;
// 	return (before_dollar);
// }

// char *double_quote(char *part, t_parsing_info *info)
// {
// 	char *var_value;
// 	char *string;
// 	char *tmp;

// 	string = NULL;
// 	var_value = NULL;
// 	info->start = info->end;
// 	while (part[info->end] && part[info->end] != '"')
// 	{
// 		if (part[info->end] == '$')
// 		{
// 			if (info->dollar == DOUBLE_Q)
// 				var_value = dollar_sign(part, info, var_value);
// 			else
// 				var_value = dollar_name(part, info, var_value);
// 		}
// 		else
// 			info->end++;
// 	}
// 	tmp = ft_substr(part, info->start, info->end - info->start);
// 	string = ft_strjoin(var_value, tmp);
// 	free(tmp);
// 	free(var_value);
// 	return (string);
// }

// // int args(char *part, t_parsing_info *info)
// // {
// // 	char *var_name;
// // 	char *var_value;
// // 	char **value_split;
// // 	char *tmp;

// // 	tmp = ft_substr(part, info->start, info->end - info->start);	
// // 	var_name = get_var_name(part, info);
// // 	var_value = get_var_value(info->env, var_name);
// // 	free(var_name);
// // 	value_split = split_by_space_tab(var_value);
// // 	if (value_split == NULL)
// // 		return (ERROR);
// // 	var_name = value_split[0];
// // 	value_split[0] = ft_strjoin(value_split[0] , tmp);
// // 	free(var_name);
	
// // 	return (GOOD);
// // }

// char *without_quote(char *part, t_parsing_info *info)
// {
// 	char *var_value;
// 	char *string;
// 	char *tmp;

// 	string = NULL;
// 	var_value = NULL;
// 	info->start = info->end;
// 	while (part[info->end] && (part[info->end] != '"' && part[info->end] != '\''))
// 	{
// 		if (part[info->end] == '$')
// 		{
// 			info->var_from = WITHOUT;
// 			// if (info->dollar == WITHOUT)
// 			// {
// 			// 	args(part, info);
// 			// }
// 			var_value = dollar_name(part, info, var_value);
// 		}
// 		else
// 			info->end++;
// 	}
// 	tmp = ft_substr(part, info->start, info->end - info->start);
// 	string = ft_strjoin(var_value, tmp);
// 	free(tmp);
// 	free(var_value);
// 	return (string);
// }

// char *filter(char *part, t_parsing_info *info)
// {
// 	char *tmp;
// 	char *tmp_free;
// 	char *token;

// 	info->end = 0;
// 	token = NULL;
// 	while (part && part[info->end])
// 	{
// 		if (part[info->end] == '\'')
// 			tmp = single_quote(part, info);
// 		else if (part[info->end] == '"')
// 		{
// 			info->end++;
// 			tmp = double_quote(part, info);
// 			info->end++;
// 		}
// 		else
// 			tmp = without_quote(part, info);
// 		tmp_free = token;
// 		token = ft_strjoin(token, tmp);
// 		free(tmp_free);
// 		free(tmp);
// 		tmp = NULL;
// 	}
// 	return (token);
// }

// int create_files(t_cmd *cmd, char **line, t_parsing_info *info, t_type type)
// {
// 	t_file *file;
// 	t_file *tmp_file;

// 	file = malloc(sizeof(t_file));
// 	if (file == NULL)
// 		return (ERROR);
// 	file->name = filter(line[info->cmd_i], info);
// 	file->text_type = info->var_from;
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

// int output_files(char **line, t_cmd *cmd, t_parsing_info *info)
// {
// 	if (ft_strcmp(line[info->cmd_i], ">") == 0)
// 	{
// 		info->file = 1;
// 		info->dollar = DOUBLE_Q;
// 		if (check_next(line[++(info->cmd_i)], ">") == ERROR)
// 			return (ERROR);
// 		create_files(cmd, line, info, oufile);
// 	}
// 	else if (ft_strcmp(line[info->cmd_i], ">>") == 0)
// 	{
// 		info->file = 1;
// 		info->dollar = DOUBLE_Q;
// 		if (check_next(line[++(info->cmd_i)], ">>") == ERROR)
// 			return (ERROR);
// 		create_files(cmd, line, info, append);
// 	}
// 	return (GOOD);
// }

// int input_files(char **line, t_cmd *cmd, t_parsing_info *info)
// {
// 	if (ft_strcmp(line[info->cmd_i], "<") == 0)
// 	{
// 		info->file = 1;
// 		info->dollar = DOUBLE_Q;
// 		if (check_next(line[++(info->cmd_i)], "<") == ERROR)
// 			return (ERROR);
// 		create_files(cmd, line, info, infile);
// 	}
// 	else if (ft_strcmp(line[info->cmd_i], "<<") == 0)
// 	{
// 		info->file = 1;
// 		if (check_next(line[++(info->cmd_i)], "<<") == ERROR)
// 			return (ERROR);
// 		create_files(cmd, line, info, here_doc);
// 	}
// 	return (GOOD);
// }

// t_cmd *create_cmd(char **line, t_parsing_info *info)
// {
// 	t_cmd *cmd;
// 	char *tmp;

// 	info->file = 0;
// 	if (line == NULL || set_default(&cmd) == ERROR)
// 		return (NULL);
// 	info->cmd = cmd;
// 	while (line[info->cmd_i])
// 	{
// 		if (ft_strcmp(line[info->cmd_i], "|") == 0)
// 		{
// 			if (line[++(info->cmd_i)] == NULL)
// 			{
// 				ft_putstr_fd("syntax error near unexpected token `|'\n", STDERR_FILENO);
// 				return (NULL);
// 			}
// 			break;
// 		}
// 		if (info->file == 0 && input_files(line, cmd, info) == ERROR)
// 			return (NULL);
// 		if (info->file == 0 && output_files(line, cmd, info) == ERROR)
// 			return (NULL);
// 		if (info->file == 0)
// 		{ //$ar:s -l || "l"$ar't'a => args[..., ls, -lta]
// 		  // tmp = filter(line[info->cmd_i], info);
// 		  // cmd->args = append_array(cmd->args, tmp);
// 		  // free(tmp);
// 		}
// 		info->file = 0;
// 		(info->cmd_i)++;
// 	}
// 	return (cmd);
// }

// t_cmd *parse_cmds(char **split_cmd, t_env *env)
// {
// 	t_parsing_info *info;
// 	t_cmd *cmd;

// 	if (split_cmd == NULL)
// 		return (NULL);
// 	info = malloc(sizeof(t_parsing_info));
// 	if (info == NULL)
// 		return (NULL);
// 	info->cmd_i = 0;
// 	info->var_from = -1;
// 	info->env = env;
// 	cmd = create_cmd(split_cmd, info);
// 	if (cmd == NULL)
// 		return (NULL);
// 	while (cmd && split_cmd && split_cmd[info->cmd_i])
// 		add_back(cmd, create_cmd(split_cmd, info));
// 	free(info);
// 	return (cmd);
// }
