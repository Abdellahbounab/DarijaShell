/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excution_herdoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounab <abounab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 10:30:37 by achakkaf          #+#    #+#             */
/*   Updated: 2024/07/16 15:35:18 by abounab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "excution.h"

static int	update_files(t_file *file, char *name, int fd)
{
	if (file && fd != -1)
	{
		close(fd);
		free_array(&file->name);
		file->type = HERE_DOC_USED;
		file->name = ft_split(name, '\0');
		free(name);
	}
	return (255);
}

static char	*create_name(void)
{
	char		*start;
	char		*num;
	long long	i;

	i = 0;
	while (1)
	{
		num = ft_itoa(i++);
		start = ft_strjoin("/tmp/.", num);
		free(num);
		if (start && access(start, F_OK))
			return (start);
		free(start);
	}
	return (NULL);
}

int	heredoc_traitement(t_file *files, t_env **env, int heredoc_position, int i)
{
	int		pid;
	int		status;
	char	*name;
	int		fd;

	fd = -1;
	if (i == heredoc_position)
	{
		name = create_name();
		fd = open(name, OUFILE, 0770);
		if (fd < 0)
			return (ft_perror(NULL, "Heredoc: ", 0), -1);
	}
	pid = fork();
	if (pid)
	{
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status))
			return (close(fd), 0);
	}
	else if (!pid)
		open_heredoc(files, fd, env);
	else
		return (close(fd), 0);
	return (update_files(files, name, fd));
}

int	heredoc_management(t_file *files, t_env **env)
{
	int		heredoc_postion;
	int		i;
	int		j;

	i = 0;
	heredoc_postion = last_file_position(files, HERE_DOC_SIMPLE) - 1;
	if (heredoc_postion >= 0)
	{
		while (heredoc_postion >= 0 && files)
		{
			if (files->type == HERE_DOC_SIMPLE
				|| files->type == HERE_DOC_SPECIAL)
			{
				j = heredoc_traitement(files, env, heredoc_postion, i);
				if (j != 255)
					return (j);
				i++;
			}
			files = files->next;
		}
	}
	return (1);
}

t_excute	*heredoc_update(t_cmd *command, t_env **env)
{
	t_excute	*cmds;
	t_excute	*node;
	int			fds[2];

	cmds = NULL;
	if (command)
		fds[0] = dup(STDIN_FILENO);
	while (command)
	{
		node = cmd_create(fds[0]);
		if (!node)
			return (cmd_free(&cmds), NULL);
		if (command->next && pipe(fds) != -1)
		{
			dup2(fds[1], node->outfile);
			close(fds[1]);
		}
		cmd_addback(&cmds, node);
		if (!heredoc_management(command->files, env))
			return (close(fds[0]), cmd_free(&cmds), NULL);
		command = command->next;
	}
	return (cmds);
}
