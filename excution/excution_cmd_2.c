/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excution_cmd_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounab <abounab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 10:38:49 by achakkaf          #+#    #+#             */
/*   Updated: 2024/07/14 22:41:29 by abounab          ###   ########.fr       */
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

// have to be updated.
char *get_commands(char **argv, char ***cmd_argv, char **paths)
{
	char	*cmd;
	char	*tmp;

	cmd = NULL;
	if (argv)
	{
		if (argv[0] && is_builtin(argv[0]))
			return (free_array(&paths), *cmd_argv = argv + 1, ft_strdup(argv[0]));
		if (is_file(argv[0]))
			return (*cmd_argv = argv, free_array(&paths), ft_strdup(argv[0]));
		else if (is_directory(argv[0]))
			return (free_array(&paths), ft_perror(argv[0], ": is a directory", 126), NULL);
		else
		{
			cmd = ft_strjoin("/", argv[0]);
			if (!cmd)
				return (free_array(&paths), NULL);//error
			if (paths && get_path(cmd, paths) >= 0 )
			{
				tmp = cmd;
				cmd = ft_strjoin(paths[get_path(cmd, paths)], tmp);
				free(tmp);
				if (cmd)
					return (*cmd_argv = argv, free_array(&paths), cmd);
				return (free_array(&paths), NULL); //error 
			}
			free(cmd);
			return (free_array(&paths), ft_perror(argv[0], ": no such file or directory", 127), NULL);
		}
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
				waitpid(cmds->pid, &status, 0);
			if (WIFSIGNALED(status))
				status = WTERMSIG(status) + 128;
			else
				status = WEXITSTATUS(status);
			cmd_free_node(cmds);
		}
		tmp = cmds->next;
		free(cmds);
		cmds = tmp;
	}
	return (1);
}
