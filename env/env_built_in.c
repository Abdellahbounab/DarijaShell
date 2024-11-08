/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_built_in.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounab <abounab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 10:17:33 by achakkaf          #+#    #+#             */
/*   Updated: 2024/07/16 11:21:52 by abounab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/parsing.h"
#include "env.h"

int	free_env(t_env **env)
{
	if (env && !*env)
		return (0);
	else
	{
		env_unset(env, (*env)->key);
		return (free_env(env));
	}
}

int	env_size(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

int	env_update(t_env **lst, char *key, char *newval, char newtype)
{
	t_env	*cpy;

	if (!lst && !*lst)
		return (0);
	cpy = env_getkey(*lst, key);
	if (cpy)
	{
		free(cpy->value);
		cpy->value = ft_strdup(newval);
		cpy->type = newtype;
		if (!cpy->value)
			return (0);
		return (1);
	}
	return (0);
}

static void	handle_unset(t_env *cpy, t_env **lst, char *key)
{
	t_env	*prev;

	if (cpy && !ft_strncmp((cpy)->key, key, ft_strlen((cpy)->key)))
	{
		prev = cpy->next;
		free(cpy->key);
		free(cpy->value);
		free(cpy);
		*lst = prev;
	}
	else
	{
		while (cpy && ft_strcmp(cpy->key, key))
		{
			prev = cpy;
			cpy = cpy->next;
		}
		prev->next = cpy->next;
		free(cpy->key);
		free(cpy->value);
		free(cpy);
	}
}

int	env_unset(t_env **lst, char *key)
{
	t_env	*cpy;

	if (!lst)
		return (0);
	if (env_getkey(*lst, key))
	{
		cpy = *lst;
		handle_unset(cpy, lst, key);
		return (1);
	}
	return (0);
}
