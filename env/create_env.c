/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounab <abounab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:04:39 by abounab           #+#    #+#             */
/*   Updated: 2024/07/15 10:28:56 by abounab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "../parsing/parsing.h"

// int	env_read(t_env *env)// to debug
// {
// 	while (env)
// 	{
// 		printf("%s=%s\n", env->key, env->value);
// 		env = env->next;
// 	}
// 	return (1);
// }


char *env_getval(t_env *lst, char *key)
{
	if (lst && env_getkey(lst, key))
		return (env_getkey(lst, key)->value);
	return 0;
}

t_env *env_getkey(t_env *lst, char *key)
{
	t_env *cpy;

	if (!lst)
		return (0);
	cpy = lst;
	while (cpy)
	{
		if (cpy->key && key && !ft_strcmp(cpy->key, key))
			return cpy;
		cpy = cpy->next;
	}
	return cpy;
}

int env_addback(t_env **lst, t_env *newnode)
{
	t_env *cpy;

	cpy = *lst;
	if (lst)
	{
		if (!*lst)
			*lst = newnode;
		else
		{
			while (cpy && cpy->next)
				cpy = cpy->next;
			cpy->next = newnode;
		}
		return 1;
	}
	return 0;
}

char *join_strs(char **value)
{
	char *saver;
	int counter;
	char *tmp;

	counter = 0;
	saver = ft_strdup("");
	while (value && value[counter])
	{
		tmp = saver;
		if (counter)
		{
			saver = ft_strjoin(tmp, "=");
			free(tmp);
			tmp = saver;
		}
		saver = ft_strjoin(tmp, value[counter]);
		counter++;
		free(tmp);
	}
	return (saver);
}

int get_env(t_env **env, char **envp)
{
	char *value;
	char **line_env;

	while (envp && *envp)
	{
		line_env = ft_split(*envp, '=');
		if (!line_env)
			return (free_env(env)); // have to free the nodes
		value = join_strs(line_env + 1);
		if (!value)
			return (free_env(env)); // have to free the nodes
		env_export(env, *line_env, value, 0);
		free_array(&line_env);
		free(value);
		envp++;
	}
	if (env_getkey(*env, "_") || !env_getkey(*env, "SHLVL"))
		value = ft_itoa(1);
	else
		value = ft_itoa(ft_atoi(env_getval(*env, "SHLVL")) + 1);
	env_export(env, "SHLVL", value, 0);
	free(value);
	env_unset(env, "_");
	return 1;
}
