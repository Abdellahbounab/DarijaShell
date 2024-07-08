/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:21:34 by achakkaf          #+#    #+#             */
/*   Updated: 2024/07/08 15:53:45 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int input_files(char **tokens, t_cmd *cmd, t_info *info)
{
	int erro;

	erro = GOOD;
	if (ft_strcmp(tokens[info->cmd_i], "<") == 0)
	{
		info->file = 1;
		if (check_next(tokens[++(info->cmd_i)]) == ERROR)
			erro = ERROR;
		if (create_files(cmd, tokens, info, INFILE) == ERROR)
			erro = ERROR;
	}
	else if (ft_strcmp(tokens[info->cmd_i], "<<") == 0)
	{
		info->file = 1;
		if (check_next(tokens[++(info->cmd_i)]) == ERROR)
			erro = ERROR;
		if (create_files(cmd, tokens, info, HERE_DOC_SIMPLE) == ERROR)
			erro = ERROR;
	}
	if (erro == ERROR)
		free_cmd(cmd);
	return (erro);
}

static int output_files(char **tokens, t_cmd *cmd, t_info *info)
{
	int erro;

	erro = GOOD;
	if (ft_strcmp(tokens[info->cmd_i], ">") == 0)
	{
		info->file = 1;
		if (check_next(tokens[++(info->cmd_i)]) == ERROR)
			erro = ERROR;
		if (create_files(cmd, tokens, info, OUFILE) == ERROR)
			erro = ERROR;
	}
	else if (ft_strcmp(tokens[info->cmd_i], ">>") == 0)
	{
		info->file = 1;
		if (check_next(tokens[++(info->cmd_i)]) == ERROR)
			erro = ERROR;

		if (create_files(cmd, tokens, info, APPEND) == ERROR)
			erro = ERROR;
	}
	if (erro == ERROR)
		free_cmd(cmd);
	return (erro);
}

static int take_files(char **tokens, t_cmd *cmd, t_info *info)
{
	if (info->file == 0 && input_files(tokens, cmd, info) == ERROR)
		return (ERROR);
	if (info->file == 0 && output_files(tokens, cmd, info) == ERROR)
		return (ERROR);
	return (GOOD);
}

// maybe there is leaks in line
static int var_parsing(t_cmd *cmd, char *var_value)
{
	int i;
	char **split;

	i = 0;
	split = ft_split(var_value, SPACE);
	free(var_value);
	if (split == NULL)
		return (ERROR);
	while (split[i])
	{
		cmd->args = append_array(cmd->args, split[i]);
		free(split[i++]);
	}
	free(split[i]);
	free(split);
	return (GOOD);
}

// maybe there is leaks in line
static int normal_parsing(t_cmd *cmd, char *line)
{
	char **split;
	int i;

	i = 0;
	split = parsing_split(line);
	free(line);
	if (split == NULL)
		return (ERROR);
	while (split[i])
	{
		line = ft_filter(split[i]);
		cmd->args = append_array(cmd->args, line);
		free(line);
		free(split[i++]);
	}
	free(split[i]);
	free(split);
	return (GOOD);
}

char *star_magic(char *token, int is_expend, t_env *env)
{
	char *strwild;
	
	strwild = NULL;
	if (token && is_expend == 1)
		strwild = var_wildcard(token, env);
	else if (token && ft_strchr(token, '*'))
		strwild = wildcard(token, env);
	else
		strwild = ft_strdup(token);
	return (strwild);
}

static int meaning(char **tokens, t_cmd *cmd, t_info *info)
{
	char *tmp;
	int is_expend;
	char *strwild;

	is_expend = 0;
	if (info->file == 0)
	{
		tmp = parsing_extend_var(tokens[info->cmd_i], info->env, &is_expend);
		if (cmd->args == NULL || info->cmd_i > 1 || ft_strcmp(cmd->args[info->cmd_i - 1], "export") != 0)
			strwild = star_magic(tmp, is_expend, info->env);
		else
			strwild = ft_strdup(tmp);
		free(tmp);
		if (is_expend == 1)
			return (var_parsing(cmd, strwild));
		else
			return (normal_parsing(cmd, strwild));
	}
	return (GOOD);
}

static int pipe_checker(t_cmd *cmd, char **tokens, t_info *info)
{
	if (!ft_strcmp(tokens[0], "|") || !tokens[info->cmd_i + 1] || !ft_strcmp(tokens[++(info->cmd_i)], "|"))
	{
		ft_putstr_fd("syntax error\n", STDERR_FILENO);
		status = 1;
		free_cmd(cmd);
		return (ERROR);
	}
	return (GOOD);
}

static t_cmd *create_cmd(char **tokens, t_info *info)
{
	t_cmd *cmd;

	info->file = 0;
	cmd = ft_calloc(1, sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	info->cmd = cmd;
	while (tokens[info->cmd_i])
	{
		if (ft_strcmp(tokens[info->cmd_i], "|") == 0)
		{
			if (pipe_checker(cmd, tokens, info) == ERROR)
				return (NULL);
			status = 0;
			break;
		}
		if (take_files(tokens, cmd, info) == ERROR || meaning(tokens, cmd, info) == ERROR)
			return (NULL);
		info->file = 0;
		(info->cmd_i)++;
	}
	return (cmd);
}

static void add_back_cmd(t_cmd *head, t_cmd *next_command)
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

t_cmd *parse_cmds(char **tokens, t_env *env)
{
	t_info *info;
	t_cmd *cmd;
	t_cmd *tmp;

	if (tokens == NULL)
		return (NULL);
	info = ft_calloc(1, sizeof(t_info));
	if (info == NULL)
		return (NULL);
	info->cmd_i = 0;
	info->env = env;
	cmd = create_cmd(tokens, info);
	while (cmd && tokens && tokens[info->cmd_i])
	{
		tmp = create_cmd(tokens, info);
		if (tmp == NULL)
		{
			free_cmd(cmd);
			free(info);
			return (NULL);
		}
		add_back_cmd(cmd, tmp);
	}
	free(info);
	return (cmd);
}
