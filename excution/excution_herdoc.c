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

int	open_heredoc(t_file *file, int outfile, t_env **env)
{
	char	*line;
	char	*tmp;

	write(STDOUT_FILENO, "> ", 2);
	line = get_next_line(STDIN_FILENO);
	while (line && !status && ft_strncmp(line, file->name[0], ft_strlen(line) - 1))
	{
		tmp = line;
		// check if it is allowed to expand it or not depends
		if (file->type == HERE_DOC_SIMPLE)
		{
			line = parsing_extend_var(line, *env, NULL);
			free(tmp);
		}
		if (outfile != -1)
			write(outfile, line, ft_strlen(line));
		free(line);
		write(STDOUT_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO);
	}
	// if (!line && status != 1)
	// 	write(STDERR_FILENO, "warning : here-document delimited by end-of-file\n", 49);
	if (outfile != -1)
		close(outfile);
	free(line);
	return (1);
}

int	heredoc_management(t_file	*files, t_excute *node, t_env **env)
{
	int	heredoc_postion;
	int	i;
	int fd[2];
	
	i = 0;
	fd[1] = -1;
	heredoc_postion = last_file_position(files, HERE_DOC_SIMPLE) - 1;
	while (heredoc_postion >= 0 && files && !status)
	{
		if (i == heredoc_postion && (files->type == HERE_DOC_SIMPLE || files->type == HERE_DOC_SPECIAL))
		{
			if (pipe(fd) < 0)
				return (printf("%s\n", strerror(errno)), -1); //error handling
			dup2(fd[0], node->infile);
			close(fd[0]);
		}
		if ((files->type == HERE_DOC_SIMPLE || files->type == HERE_DOC_SPECIAL) && files->name)
		{
			open_heredoc(files, fd[1], env);
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
		if (!heredoc_management(command->files, node, env))
			return (cmd_free(&cmds), NULL);
		cmd_addback(&cmds, node);
		command = command->next;
	}
	return (cmds);
}
