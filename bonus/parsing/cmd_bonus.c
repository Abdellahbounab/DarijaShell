/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:21:34 by achakkaf          #+#    #+#             */
/*   Updated: 2024/07/08 12:33:10 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

static int input_files(char **line, t_cmd *cmd, t_info *info)
{
	int erro;

	erro = GOOD;
	if (ft_strcmp(line[info->cmd_i], "<") == 0)
	{
		info->file = 1;
		if (check_next(line[++(info->cmd_i)], cmd->status) == ERROR)
			erro = ERROR;
		if (create_files(cmd, line, info, INFILE) == ERROR)
			erro = ERROR;
	}
	else if (ft_strcmp(line[info->cmd_i], "<<") == 0)
	{
		info->file = 1;
		if (check_next(line[++(info->cmd_i)], cmd->status) == ERROR)
			erro = ERROR;
		if (create_files(cmd, line, info, HERE_DOC_SIMPLE) == ERROR)
			erro = ERROR;
	}
	if (erro == ERROR)
		free_cmd(cmd);
	return (erro);
}

static int output_files(char **line, t_cmd *cmd, t_info *info)
{
	int erro;

	erro = GOOD;
	if (ft_strcmp(line[info->cmd_i], ">") == 0)
	{
		info->file = 1;
		if (check_next(line[++(info->cmd_i)], cmd->status) == ERROR)
			erro = ERROR;
		if (create_files(cmd, line, info, OUFILE) == ERROR)
			erro = ERROR;
	}
	else if (ft_strcmp(line[info->cmd_i], ">>") == 0)
	{
		info->file = 1;
		if (check_next(line[++(info->cmd_i)], cmd->status) == ERROR)
			erro = ERROR;

		if (create_files(cmd, line, info, APPEND) == ERROR)
			erro = ERROR;
	}
	if (erro == ERROR)
		free_cmd(cmd);
	return (erro);
}

static int take_place(char **tokens, t_cmd *cmd, t_info *info)
{
	char *tmp;
	char *strwild;
	char **split;
	int i;
	int expend;

	expend = 0;
	strwild = NULL;
	i = 0, split = NULL;
	if (info->file == 0 && output_files(tokens, cmd, info) == ERROR)
		return (ERROR);
	if (info->file == 0)
	{
		tmp = parsing_extend_var(tokens[info->cmd_i], info->env, info->cmd->status, &expend);
		if (cmd->args == NULL || info->cmd_i > 1 || ft_strcmp(cmd->args[info->cmd_i - 1], "export") != 0)
		{
			if (tmp && expend == 1)
				strwild = var_wildcard(tmp);
			else if (tmp && ft_strchr(tmp, '*'))
				strwild = wildcard(tmp);
			else
				strwild = ft_strdup(tmp);
		}
		else
			strwild = ft_strdup(tmp);
		if (expend == 1)
		{
			split = ft_split(strwild, SPACE);
			free(tmp), i = 0;
			free(strwild);
			if (split == NULL)
				return (ERROR);
			while (split[i])
			{
				cmd->args = append_array(cmd->args, split[i]);
				free(split[i++]);
			}
			free(split[i]);
			free(split);
		}
		else
		{
			split = parsing_split(strwild);
			free(tmp), i = 0;
			free(strwild);
			if (split == NULL)
				return (GOOD);
			while (split[i])
			{
				tmp = ft_filter(split[i]);
				cmd->args = append_array(cmd->args, tmp);
				free(tmp);
				free(split[i++]);
			}
			free(split[i]);
			free(split);
		}
	}
	return (GOOD);
}

static t_cmd *create_cmd(char **tokens, t_info *info, int *status)
{
	t_cmd *cmd;

	info->file = 0;
	if (set_default(&cmd, status) == ERROR)
		return (NULL);
	info->cmd = cmd;
	while (tokens[info->cmd_i])
	{
		if (ft_strcmp(tokens[info->cmd_i], "|") == 0)
		{
			if (ft_strcmp(tokens[0], "|") == 0 || tokens[info->cmd_i + 1] == NULL || ft_strcmp(tokens[++(info->cmd_i)], "|") == 0)
			{
				ft_putstr_fd("syntax error\n", STDERR_FILENO);
				*status = 1;
				free_cmd(cmd);
				return (NULL);
			}
			break;
		}
		if (info->file == 0 && (input_files(tokens, cmd, info) == ERROR || take_place(tokens, cmd, info) == ERROR))
			return (NULL);
		info->file = 0;
		(info->cmd_i)++;
	}
	return (cmd);
}

t_cmd *parse_cmds(char **tokens, t_env *env, int *status)
{
	t_info *info;
	t_cmd *cmd;
	t_cmd *tmp;

	if (tokens == NULL)
		return (NULL);
	info = malloc(sizeof(t_info));
	if (info == NULL)
		return (NULL);
	info->cmd_i = 0;
	info->env = env;
	cmd = create_cmd(tokens, info, status);
	while (cmd && tokens && tokens[info->cmd_i])
	{
		tmp = create_cmd(tokens, info, status);
		if (tmp)
			add_back_cmd(cmd, tmp);
		else
		{
			free_cmd(cmd);
			free(info);
			return (NULL);
		}
	}
	free(info);
	return (cmd);
}
