/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excution_cmd_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 10:38:49 by achakkaf          #+#    #+#             */
/*   Updated: 2024/07/09 10:39:18 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "excution.h"

char *get_commands(char **argv, char ***cmd_argv, char **paths)
{
	char	*cmd;
	char	*tmp;

	cmd = NULL;
	if (argv)
	{
		if (argv[0] && !ft_strncmp(argv[0], "/", 1) && is_absolutecmd(argv[0]))
			return (*cmd_argv = argv, free_array(&paths), ft_strdup(argv[0]));
		else if (argv[0] && !ft_strncmp(argv[0], "/", 1))
			return (free_array(&paths), ft_perror(argv[0], ": no such file or directory", 127), NULL);
		if (argv[0] && is_builtin(argv[0]))
			return (free_array(&paths), *cmd_argv = argv + 1, ft_strdup(argv[0]));
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
		free_array(&paths);
		if (!ft_strncmp("./", argv[0], 2))
		{
			if (access(argv[0], X_OK) != -1)
				return (*cmd_argv = argv, ft_strdup(argv[0]));
			return (free_array(&paths), ft_perror(NULL, argv[0] , 0), NULL);
		}
		// return (free_array(&paths), ft_perror(argv[0], ": no such file or directory", 127), NULL);
		return (*cmd_argv = argv, ft_strdup(argv[0]));
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
