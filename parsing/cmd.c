/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:21:34 by achakkaf          #+#    #+#             */
/*   Updated: 2024/07/12 17:07:46 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// maybe there is leaks in line
static int var_parsing(t_cmd *cmd, char *var_value)
{
	int i;
	char **split;

	i = 0;
	split = ft_split(var_value, SPACE);
	free(var_value);
	if (split == NULL)
		return (GOOD);
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
		return (GOOD);
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
// minishell-$ export var="'*'"
// minishell-$ echo $var
// *
// minishell-$ export var="' *' "
// export : not a valid identifier
// minishell-$ export var="' *' "
// export : not a valid identifier
int meaning(char **tokens, t_cmd *cmd, t_info *info)
{
	char *tmp;
	int is_expend;
	char *strwild;
	
	is_expend = 0;
	if (info->file == 0)
	{
		tmp = parsing_extend_var(tokens[info->cmd_i], info->env, &is_expend);
		// printf("tmp:%s is_expend:%d\n", tmp, is_expend);
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
