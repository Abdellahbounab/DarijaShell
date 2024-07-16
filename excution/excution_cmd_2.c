/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excution_cmd_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 10:38:49 by achakkaf          #+#    #+#             */
/*   Updated: 2024/07/16 10:35:04 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "excution.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int is_directory(const char *path) {
   struct stat stats;
   if (stat(path, &stats) != 0)
	   return (0);
   return (S_ISDIR(stats.st_mode));
}

int is_file(const char *path) {
   struct stat stats;
   if (stat(path, &stats) != 0)
	   return (0);
   return (S_ISREG(stats.st_mode));
}


char **get_cmdarg(char **argv)
{
	char **arr;
	int i;

	i = 0;
	arr = ft_calloc(array_size(argv) + 2, sizeof(char *));
	if (!arr)
		return (NULL);
	arr[i++] = ft_strdup("/bin/bash");
	while (argv[i - 1])
	{
		arr[i] = ft_strdup(argv[i - 1]);
		if (!arr[i])
			return (free_array(&arr), NULL);
		i++;
	}
	return (arr);
}

char *get_commands(char **argv, char ***cmd_argv, char **paths)
{
	char	*cmd;
	char	*tmp;

	cmd = NULL;
	if (argv)
	{
		if (argv[0] && is_builtin(argv[0]))
			return (free_array(&paths), *cmd_argv = argv + 1, ft_strdup(argv[0]));
		if (argv[0] && is_file(argv[0]))
		{
			if (argv[0][0] == '.' && argv[0][ft_strlen(argv[0]) - 1] == 'h' && argv[0][ft_strlen(argv[0]) - 2] == 's')
			{
				*cmd_argv = get_cmdarg(argv);
				return (free_array(&paths), ft_strdup("/bin/bash"));
			}
			return (*cmd_argv = argv, free_array(&paths), ft_strdup(argv[0]));
		}
		else if (argv[0] && ft_strchr(argv[0], '/'))
		{
			if (is_directory(argv[0]))
				return (free_array(&paths), ft_perror(argv[0], ": is a directory", 126), NULL);
			return (free_array(&paths), ft_perror(argv[0], ": No such file or directory", 127), NULL);
		}
		else if (argv[0] && argv[0][0] != '/' && argv[0][0] != '.')
		{
			cmd = ft_strjoin("/", argv[0]);
			if (!cmd)
				return (free_array(&paths), NULL);//error
			if (paths)
			{
				if (get_path(cmd, paths) >= 0)
				{
					tmp = cmd;
					cmd = ft_strjoin(paths[get_path(cmd, paths)], tmp);
					free(tmp);
					if (cmd)
						return (*cmd_argv = argv, free_array(&paths), cmd);
					return (free_array(&paths), NULL); //error 
				}
				free(cmd);
				return (*cmd_argv = argv, free_array(&paths), ft_strdup(argv[0]));
			}
			free(cmd);
			return (ft_perror(argv[0], ": No such file or directory", 127), NULL);
		}
		return (*cmd_argv = argv, free_array(&paths), ft_strdup(argv[0]));
	}
	return (free_array(&paths), ft_perror(argv[0], ": command not found", 1), NULL);
}

int	waitprocess(t_excute *cmds)
{
	t_excute	*tmp;

	
	while (cmds)
	{
		if (cmds->pid)
		{
			if (cmds->pid)
				waitpid(cmds->pid, &g_status, 0);
			if (WIFSIGNALED(g_status))
				g_status = WTERMSIG(g_status) + 128;
			else
				g_status = WEXITSTATUS(g_status);
			cmd_free_node(cmds);
		}
		tmp = cmds->next;
		free(cmds);
		cmds = tmp;
	}
	return (1);
}
