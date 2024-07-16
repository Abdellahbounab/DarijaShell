/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:41:58 by achakkaf          #+#    #+#             */
/*   Updated: 2024/07/16 09:50:50 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	input_files(char **tokens, t_cmd *cmd, t_info *info)
{
	int	erro;

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

static int	output_files(char **tokens, t_cmd *cmd, t_info *info)
{
	int	erro;

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

int	take_files(char **tokens, t_cmd *cmd, t_info *info)
{
	if (info->file == 0 && input_files(tokens, cmd, info) == ERROR)
		return (ERROR);
	if (info->file == 0 && output_files(tokens, cmd, info) == ERROR)
		return (ERROR);
	return (GOOD);
}

char	**get_files(t_env *env, int dot)
{
	DIR				*dir;
	struct dirent	*file;
	char			**filenames;
	char			*pwd;

	pwd = env_getval(env, "PWD");
	dir = opendir(pwd);
	filenames = NULL;
	if (dir == NULL)
		return (NULL);
	file = readdir(dir);
	while (file && dot == 0)
	{
		if (file->d_name[0] != '.')
			filenames = append_array(filenames, file->d_name);
		file = readdir(dir);
	}
	while (file && dot == 1)
	{
		filenames = append_array(filenames, file->d_name);
		file = readdir(dir);
	}
	closedir(dir);
	return (filenames);
}

bool	match_(char *filename, const char *pattern)
{
	bool	is_single_q;
	bool	is_double_q;

	is_double_q = false;
	is_single_q = false;
	while (*filename && *pattern)
	{
		if (!is_single_q && !is_double_q)
		{
			if (handle_quotes(&pattern, &is_single_q, &is_double_q))
				continue ;
			if (*pattern == '*')
			{
				if (handle_wildcard(&filename, &pattern))
					return (true);
				return (false);
			}
		}
		else if (handle_quotes(&pattern, &is_single_q, &is_double_q))
			continue ;
		if (!match_chars(&filename, &pattern))
			return (false);
	}
	skip_star(&pattern);
	return (*pattern == '\0' && *filename == '\0');
}
