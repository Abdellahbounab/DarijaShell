/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excution_herdoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 10:30:37 by achakkaf          #+#    #+#             */
/*   Updated: 2024/07/09 10:44:44 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "excution.h"

int	open_heredoc(t_file *file, int hfile, t_env **env)
{
	char	*line;
	char	*tmp;

	line = readline("> ");
	while (line && !status && ft_strcmp(line, file->name[0]))
	{
		tmp = line; 
		if (file->type == HERE_DOC_SIMPLE)
		{
			line = parsing_extend_var(line, *env, NULL);
			free(tmp);
		}
		if (hfile != -1)
		{
			write(hfile, line, ft_strlen(line));
			write(hfile, "\n", 1);
		}
		free(line);
		line = readline("> ");
	}
	free(line);
	return (1);
}

static int update_files(t_file *file, char *name, int fd)
{
	if (file)
	{
		close(fd);
		free_array(&file->name);
		file->type = HERE_DOC_USED;
		file->name = ft_split(name, '\0');
	}
	return (1);
}

static char *create_name(void)
{
	char *start;
	long long i;

	i = 0;
	while (1)
	{
		start = ft_strjoin("/tmp/.", ft_itoa(i++));
		if (start && access(start, F_OK))
			return (start);
		free(start);
	}
	return (NULL);
}

int	heredoc_management(t_file	*files, t_env **env)
{
	int	heredoc_postion;
	int	i;
	int fd;
	char *name;
	
	i = 0;
	fd = -1;
	heredoc_postion = last_file_position(files, HERE_DOC_SIMPLE) - 1;
	while (heredoc_postion >= 0 && files && !status)
	{
		if (files->type == HERE_DOC_SIMPLE || files->type == HERE_DOC_SPECIAL)
		{
	//		if (pipe(fd) < 0)
			if (i == heredoc_postion)
			{
				name = create_name();
				fd = open (name, OUFILE, 0770);
				if (fd < 0)
					return (printf("%s\n", strerror(errno)), -1); //error handling
			}
			open_heredoc(files, fd, env);
			if (fd != -1)
				update_files(files, name, fd);
			if (status)
				return (0);
			i++;
		}
		files = files->next;
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
		if (!heredoc_management(command->files, env))
			return (cmd_free(&cmds), NULL);
		cmd_addback(&cmds, node);
		command = command->next;
	}
	return (cmds);
}
