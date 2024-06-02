/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounab <abounab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:04:39 by abounab           #+#    #+#             */
/*   Updated: 2024/06/02 14:20:16 by abounab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int	env_update(t_env **lst, char *key, char *newval)
{
	t_env	*cpy;
	
	if (!lst && !*lst)
		return 0;
	cpy = env_getkey(*lst, key);
	if (cpy)
	{
		free(cpy->value);
		cpy->value = ft_strdup(newval);
		if (!cpy->value)
			return 0;
		return 1;
	}
	return 0;
}

int	env_read(t_env *lst)
{
	int	counter;

	counter = 0;
	while (lst)
	{
		printf("%s=%s\n", lst->key, lst->value);
		lst = lst->next;
		counter++;
	}
	return (counter);
}

int	env_export(t_env **lst, char *key, char *val)
{
	t_env *newnode;
	
	if (!lst)
		return 0;
	if (env_getkey(*lst, key))
	{
		if (env_update(lst, key, val))
			return 1;
		return 0;
	}
	newnode = malloc(sizeof(t_env));
	if (!newnode)
		return 0;
	newnode->key = ft_strdup(key);
	newnode->value = ft_strdup(val);
	newnode->next = NULL;
	if (!*lst)
		return (*lst = newnode, 1);
	else if (env_addback(lst, newnode))
		return 1;
	return 0;
}

int	env_unset(t_env **lst, char *key)
{
	t_env	*cpy;
	t_env	*prev;

	if (!lst)
		return 0;
	cpy = *lst;
	if (env_getkey(*lst, key))
	{
		if (cpy && !ft_strcmp(cpy->key, key))
			*lst = cpy->next;
		else
		{
			while (cpy && ft_strcmp(cpy->key, key))
			{
				prev = cpy;
				cpy = cpy->next;
			}
			prev->next = cpy->next;	
		}
		free(cpy);
		return 1;
	}
	return 0;
}

char *env_getval(t_env *lst, char *key)
{
	if (env_getkey(lst, key))
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
		if (!ft_strcmp(cpy->key, key))
			return cpy;
		cpy = cpy->next;
	}
	return cpy;
}


int	env_addback(t_env **lst, t_env *newnode)
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

static char	*join_strs(char **value)
{
	char	*saver;
	int		counter;
	char	*tmp;

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

int	get_env(t_env **env, char **envp)
{
	char *value;
	char **line_env;

	while (envp && *envp)
	{
		line_env = ft_split(*envp, '=');
		if (!line_env)
			return (0); // have to free the nodes
		value = join_strs(line_env + 1);
		if (!value)
			return (0); // have to free the nodes
		env_export(env, *line_env, value);
		free(line_env);
		free(value);
		envp++;
	}
	return 1;
}