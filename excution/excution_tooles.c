/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excution_tooles.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounab <abounab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 10:26:56 by achakkaf          #+#    #+#             */
/*   Updated: 2024/07/14 21:49:55 by abounab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "excution.h"

int	ft_perror(char *header, char *msg, int err)
{
	if (msg)
	{
		if (err)
		{
			if (header)
				write(STDERR_FILENO, header, ft_strlen(header));
			write(STDERR_FILENO, msg, ft_strlen(msg));
			write(STDERR_FILENO, "\n", 1);
			exit(err);
		}
		else
		{
			perror(msg);
			exit(errno);
		}
	}
	return (0);
}

char **env_to_array(t_env *env)
{
	char	**arr;
	char	*joined;
	int		i;

	i = 0;
	arr = ft_calloc(env_size(env) + 1, sizeof(char *));
	if (!arr)
		return (0);
	while (env)
	{
		joined = ft_strjoin(env->key, "=");
		if (!joined)
			return (free_array(&arr), NULL);
		arr[i] = ft_strjoin(joined, env->value);
		if (!arr[i])
			return (free_array(&arr), NULL);
		free(joined);
		env = env->next;
		i++;
	}
	return arr;
}

int	is_absolutecmd(char *cmd)
{
	int	i;
	char **paths;

	i = 0;
	
	paths = ft_split(getenv("PATH"), ':');
	while (paths && paths[i])
	{
		if (!ft_strncmp(cmd, paths[i], ft_strlen(paths[i])))
		{
			if (access(cmd, F_OK) != -1)
				return (free_array(&paths), 1);
			return (free_array(&paths), 0);
		}
		i++;
	}
	free_array(&paths);
	return (0);
}

int	close_other(t_excute *head, int pos)
{
	int	i;

	i = 0;
	while (head)
	{
		if (i != pos)
		{
			close(head->infile);
			close(head->outfile);
		}
		i++;
		head = head->next;
	}
	return (1);
}
