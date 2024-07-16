/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excution_cmd_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounab <abounab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 10:38:49 by achakkaf          #+#    #+#             */
/*   Updated: 2024/07/16 20:01:38 by abounab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "excution.h"
#include <sys/stat.h>

int	is_directory(const char *path)
{
	struct stat	stats;

	if (!path || stat(path, &stats))
		return (0);
	return (S_ISDIR(stats.st_mode));
}

int	is_file(const char *path)
{
	struct stat	stats;

	if (stat(path, &stats))
		return (0);
	return (S_ISREG(stats.st_mode));
}

static char	*check_file(char **argv, char ***cmd_argv, char **paths)
{
	if ((argv[0][0] == '.' && argv[0][ft_strlen(argv[0]) - 1] == 'h'
		&& argv[0][ft_strlen(argv[0]) - 2] == 's'))
	{
		if (access(argv[0], X_OK) == -1)
			return (free_array(&paths), 
				ft_perror(argv[0], " Permission denied", 126), NULL);
		*cmd_argv = get_cmdarg(argv);
		return (free_array(&paths), ft_strdup("/bin/bash"));
	}
	return (*cmd_argv = argv, free_array(&paths), ft_strdup(argv[0]));
}

static char	*check_normal(char **argv, char ***cmd_argv, char **paths)
{
	char	*cmd;
	char	*tmp;

	cmd = ft_strjoin("/", argv[0]);
	if (!cmd)
		return (free_array(&paths), ft_perror(NULL, "Memory", 0), NULL);
	if (paths)
	{
		if (get_path(cmd, paths) >= 0)
		{
			tmp = cmd;
			cmd = ft_strjoin(paths[get_path(cmd, paths)], tmp);
			free(tmp);
			if (cmd)
				return (*cmd_argv = argv, free_array(&paths), cmd);
			return (free_array(&paths), ft_perror(NULL, "Memory", 0),
				NULL);
		}
		free(cmd);
		return (*cmd_argv = argv, free_array(&paths),
			ft_strdup(argv[0]));
	}
	free(cmd);
	return (ft_perror(argv[0], ": No such file or directory", 127),
		NULL);
}

char	*get_commands(char **argv, char ***cmd_argv, char **paths)
{
	char	*cmd;

	cmd = NULL;
	if (argv)
	{
		if (argv[0] && is_builtin(argv[0]))
			return (free_array(&paths), *cmd_argv = argv + 1,
				ft_strdup(argv[0]));
		if (argv[0] && is_file(argv[0]))
			return (check_file(argv, cmd_argv, paths));
		else if ((argv[0] && ft_strchr(argv[0], '/')) 
			|| (is_directory(argv[0]) && !paths))
		{
			if (is_directory(argv[0]))
				return (free_array(&paths), ft_perror(argv[0],
						": is a directory", 126), NULL);
			return (free_array(&paths), ft_perror(argv[0],
					": No such file or directory", 127), NULL);
		}
		else if (argv[0] && argv[0][0] != '/' && argv[0][0] != '.')
			return (check_normal(argv, cmd_argv, paths));
		return (*cmd_argv = argv, free_array(&paths), ft_strdup(argv[0]));
	}
	return (free_array(&paths), NULL);
}
