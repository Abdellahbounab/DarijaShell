/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounab <abounab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:04:39 by abounab           #+#    #+#             */
/*   Updated: 2024/05/31 17:16:40 by abounab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	env_addback(t_env **lst, t_env *new)
{
	t_env *cpy;

	cpy = *lst;
	if (lst)
	{
		if (!*lst)
			*lst = new;
		else
		{
			while (cpy && cpy->next)
				cpy = cpy->next;
			cpy->next = new;
		}
	}
}

static t_env	*create_env(char *key, char **value)
{
	t_env	*node;
	int		counter;
	char	*tmp;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	node->value = 0;
	counter = 0;
	while (value && value[counter])
	{
		tmp = node->value;
		if (counter)
		{
			node->value = ft_strjoin(tmp, "=");
			free(tmp);
			tmp = node->value;
		}
		node->value = ft_strjoin(tmp, *value);
		value++;
		counter++;
		free(tmp);
	}
	printf("%s=%s\n", node->key, node->value);
	node->next = NULL;
	return (node);
}

int	get_env(t_env **env, char **envp)
{
	t_env *cpy;
	char **line_env;

	while (envp && *envp)
	{
		line_env = ft_split(*envp, '=');
		if (!line_env)
			return (0); // have to free the nodes
		cpy = create_env(line_env[0], line_env + 1);
		if (!cpy)
			return (0); // have to free the nodes
		if (*env)
			env_addback(env, cpy);
		else
			*env = cpy;
		envp++;
		free(line_env);
	}
	return 1;
}