/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excution_cmd_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounab <abounab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:19:03 by abounab           #+#    #+#             */
/*   Updated: 2024/07/16 15:50:49 by abounab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "excution.h"

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

char	**get_cmdarg(char **argv)
{
	char	**arr;
	int		i;

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

static void	heredoc_process(t_file *file, int heredocfile,
	t_env **env, char *line)
{
	char	*tmp;

	tmp = line;
	if (file->type == HERE_DOC_SIMPLE)
	{
		line = heredoc_var(line, *env, NULL);
		free(tmp);
	}
	if (heredocfile != -1)
	{
		write(heredocfile, line, ft_strlen(line));
		write(heredocfile, "\n", 1);
	}
	free(line);
	line = NULL;
}

void	open_heredoc(t_file *file, int heredocfile, t_env **env)
{
	char	*line;
	char	*tmp;

	line = NULL;
	signal(SIGINT, SIG_DFL);
	write(STDOUT_FILENO, "> ", 2);
	tmp = get_next_line(STDIN_FILENO);
	if (tmp)
		line = ft_strtrim(tmp, "\n");
	free(tmp);
	while (line && ft_strcmp(line, file->name[0]))
	{
		heredoc_process(file, heredocfile, env, line);
		write(STDOUT_FILENO, "> ", 2);
		tmp = get_next_line(STDIN_FILENO);
		if (tmp)
			line = ft_strtrim(tmp, "\n");
		free(tmp);
	}
	free(line);
	exit(0);
}
