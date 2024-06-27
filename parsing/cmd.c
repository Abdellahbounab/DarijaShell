/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounab <abounab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:21:34 by achakkaf          #+#    #+#             */
/*   Updated: 2024/06/27 19:41:52 by abounab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int input_files(char **line, t_cmd *cmd, t_info *info)
{
	int status;

	status = GOOD;
	if (ft_strcmp(line[info->cmd_i], "<") == 0)
	{
		info->file = 1;
		if (check_next(line[++(info->cmd_i)]) == ERROR)
			status = ERROR;
		if (create_files(cmd, line, info, INFILE) == ERROR)
			status = ERROR;
	}
	else if (ft_strcmp(line[info->cmd_i], "<<") == 0)
	{
		info->file = 1;
		if (check_next(line[++(info->cmd_i)]) == ERROR)
			status = ERROR;
		if (create_files(cmd, line, info, HERE_DOC) == ERROR)
			status = ERROR;
	}
	if (status == ERROR)
		free_cmd(cmd);
	return (status);
}

static int output_files(char **line, t_cmd *cmd, t_info *info)
{
	int status;

	status = GOOD;
	if (ft_strcmp(line[info->cmd_i], ">") == 0)
	{
		info->file = 1;
		if (check_next(line[++(info->cmd_i)]) == ERROR)
			status = ERROR;
		if (create_files(cmd, line, info, OUFILE) == ERROR)
			status = ERROR;
	}
	else if (ft_strcmp(line[info->cmd_i], ">>") == 0)
	{
		info->file = 1;
		if (check_next(line[++(info->cmd_i)]) == ERROR)
			status = ERROR;

		if (create_files(cmd, line, info, APPEND) == ERROR)
			status = ERROR;
	}
	if (status == ERROR)
		free_cmd(cmd);
	return (status);
}

static int take_place(char **tokens, t_cmd *cmd, t_info *info)
{
	char *tmp;
	char **split;
	int i;

	i = 0, split = NULL;
	if (info->file == 0 && output_files(tokens, cmd, info) == ERROR)
		return (ERROR);
	if (info->file == 0)
	{
		tmp = parsing_extend_var(tokens[info->cmd_i], info->env, info->cmd->status);
		split = parsing_split(tmp);
		free(tmp), i = 0;
		if (split == NULL)
			return (GOOD);
		while (split[i])
		{
			tmp = filter(split[i]);
			cmd->args = append_array(cmd->args, tmp);
			free(tmp);
			free(split[i++]);
		}
		free(split[i]);
		free(split);
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
				ft_putstr_fd("syntax error0 \n", STDERR_FILENO);
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

	if (tokens == NULL)
		return (NULL);
	info = malloc(sizeof(t_info));
	if (info == NULL)
		return (NULL);
	info->cmd_i = 0;
	info->env = env;
	cmd = create_cmd(tokens, info, status);
	while (cmd && tokens && tokens[info->cmd_i])
		add_back_cmd(cmd, create_cmd(tokens, info, status));
	free(info);
	return (cmd);
}
