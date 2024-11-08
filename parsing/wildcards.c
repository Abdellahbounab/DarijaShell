/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 10:54:21 by achakkaf          #+#    #+#             */
/*   Updated: 2024/07/16 10:24:35 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	join_str_space(char **result, char *new_str)
{
	char	*tmp;

	tmp = *result;
	*result = ft_strjoin(*result, new_str);
	free(tmp);
	tmp = *result;
	*result = ft_strjoin(*result, " ");
	free(tmp);
}

char	*wildcard(char *pattern, t_env *env)
{
	int		i;
	char	*result;
	char	**filenames;

	i = 0;
	result = NULL;
	if (pattern[0] == '.')
		filenames = get_files(env, 1);
	else
		filenames = get_files(env, 0);
	sort_by_name(filenames);
	while (filenames && filenames[i])
	{
		if (match_(filenames[i], pattern))
			join_str_space(&result, filenames[i]);
		i++;
	}
	if (result == NULL)
		result = ft_strdup(pattern);
	free_array(&filenames);
	return (result);
}

char	*var_wildcard(char *line, t_env *env)
{
	char	**split;
	int		i;
	char	*result;
	char	*tmp;

	split = ft_split(line, ' ');
	i = 0;
	result = NULL;
	tmp = NULL;
	while (split && split[i])
	{
		if (ft_strchr(split[i], '*'))
			tmp = wildcard(split[i], env);
		else
			tmp = ft_strdup(split[i]);
		join_str_space(&result, tmp);
		free(tmp);
		i++;
	}
	free_array(&split);
	return (result);
}
