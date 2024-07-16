/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excution_files.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounab <abounab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 10:35:10 by achakkaf          #+#    #+#             */
/*   Updated: 2024/07/16 11:44:45 by abounab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "excution.h"

int	last_file_position(t_file *files, t_type t)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (files)
	{
		if (files->type == HERE_DOC_SIMPLE || files->type == HERE_DOC_SPECIAL
			|| files->type == HERE_DOC_USED)
			i++;
		else if (files->type == t)
			j++;
		files = files->next;
	}
	if (t == HERE_DOC_SIMPLE || t == HERE_DOC_SPECIAL
		|| files->type == HERE_DOC_USED)
		return (i);
	return (j);
}

int	files_update(t_file *files, t_excute *cmds)
{
	int	fd;

	fd = cmds->outfile;
	while (files)
	{
		if (!files->name || files->name[1])
			return (ft_perror("minishell:", " ambiguous redirect", 1));
		if (files->type == OUFILE || files->type == APPEND)
		{
			fd = open(files->name[0], files->type, 0720);
			if (fd < 0)
				return (ft_perror(NULL, files->name[0], 0), fd);
			dup2(fd, cmds->outfile);
			close(fd);
		}
		else if (files->type == INFILE || files->type == HERE_DOC_USED)
		{
			fd = open(files->name[0], INFILE);
			if (fd < 0)
				return (ft_perror(NULL, files->name[0], 0), fd);
			dup2(fd, cmds->infile);
			close(fd);
		}
		files = files->next;
	}
	return (1);
}

int	get_path(char *cmd, char **paths)
{
	int		i;
	char	*tmp;

	i = 0;
	while (cmd && paths && paths[i])
	{
		tmp = ft_strjoin(paths[i], cmd);
		if (!tmp)
			return (0);
		if (access(tmp, X_OK) != -1)
			return (free(tmp), i);
		free(tmp);
		i++;
	}
	return (-1);
}

int	redirection_update(t_cmd *command, t_excute **head, t_env **env)
{
	int			pid;
	t_excute	*cmds;
	int			i;

	cmds = *head;
	i = 0;
	while (command && cmds)
	{
		if (!command->next && !(*head)->next && command->args
			&& special_builtin(command->args[0], command->args[1]))
			child_excution(command, cmds, env, 0);
		else
		{
			pid = fork();
			ft_signals(pid);
			if (!pid)
				return (close_other(*head, i), 
					child_excution(command, cmds, env, 1));
			if (pid && pid != -1)
				cmds->pid = pid;
			else
				return (g_status = 1, printf("%s\n", strerror(errno)));
		}
		cmds = cmds->next;
		command = command->next;
		i++;
	}
	return (close_other(*head, -1), 1);
}
