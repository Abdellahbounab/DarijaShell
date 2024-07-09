/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:41:58 by achakkaf          #+#    #+#             */
/*   Updated: 2024/07/09 11:43:59 by achakkaf         ###   ########.fr       */
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

int take_files(char **tokens, t_cmd *cmd, t_info *info)
{
	if (info->file == 0 && input_files(tokens, cmd, info) == ERROR)
		return (ERROR);
	if (info->file == 0 && output_files(tokens, cmd, info) == ERROR)
		return (ERROR);
	return (GOOD);
}

char **get_files(t_env *env)
{
	DIR *dir;
	struct dirent *file;
	char **filenames;
	char *pwd;

	pwd = env_getval(env, "PWD");
	dir = opendir(pwd);
	filenames = NULL;
	if (dir == NULL)
		return (NULL);
	file = readdir(dir);
	while (file)
	{
		if (file->d_name[0] != '.')
			filenames = append_array(filenames, file->d_name);
		file = readdir(dir);
	}
	closedir(dir);
	return (filenames);
}