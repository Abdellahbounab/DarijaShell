/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 22:34:42 by Achakkaf          #+#    #+#             */
/*   Updated: 2024/05/28 12:14:49 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void error(char *error_message)
{
	write(STDERR_FILENO, error_message, ft_strlen(error_message));
	exit(1);
}

char *path_(char *p, char *command, int i)
{
	char **all_paths;
	char *path;
	char *tmp;

	all_paths = ft_split(p, ':');
	while (all_paths[i])
	{
		path = ft_strjoin(all_paths[i], "/");
		free(all_paths[i]);
		tmp = path;
		path = ft_strjoin(path, command);
		free(tmp);
		if (access(path, X_OK) == 0)
		{
			while (all_paths[i])
				free(all_paths[++i]);
			free(all_paths);
			return (path);
		}
		free(path);
		path = NULL;
		i++;
	}
	free(all_paths);
	return (NULL);
}

char *find_path(char *command, char **env)
{
	char *p;
	char *path;
	int i;
	int j;

	i = 0;
	j = 0;
	path = "PATH=";
	while (env[i])
	{
		while (env[i][j] == path[j] && path[j])
			j++;
		if (path[j] == '\0')
			break;
		i++;
	}
	p = env[i];
	p += j;
	return (path_(p, command, 0));
}

void exec_command(char **cmd, char **env)
{
	char *cmd_path;
	// char **cmd;

	// cmd = split_cmd(command);
	cmd_path = find_path(cmd[0], env);
	execve(cmd_path, cmd, env);
	error("command not found\n");
}

void redirection(int new_fd, int old_fd)
{
	int check;

	check = dup2(new_fd, old_fd);
	if (check < 0)
		error("I can't redirect\n");
}
