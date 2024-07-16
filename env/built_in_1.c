/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 19:16:19 by abounab           #+#    #+#             */
/*   Updated: 2024/07/16 10:34:11 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "../parsing/parsing.h"
#include "../excution/excution.h"
#include "../types.h"

/*
◦ echo with option -n *
◦ cd with only a relative or absolute path
◦ pwd with no options *
◦ export with no options (when no arg can display the envs) *
◦ unset with no options *
◦ env with no options or arguments *
◦ exit with no options *
*/

int is_builtin(char *cmd)
{
	if (cmd)
	{
		if (!ft_strcmp(cmd, "echo"))
			return (1);
		else if (!ft_strcmp(cmd, "cd"))
			return (1);
		else if (!ft_strcmp(cmd, "pwd"))
			return (1);
		else if (!ft_strcmp(cmd, "export"))
			return (1);
		else if (!ft_strcmp(cmd, "unset"))
			return (1);
		else if (!ft_strcmp(cmd, "env"))
			return (1);
		else if (!ft_strcmp(cmd, "exit"))
			return (1);
	}
	return (0);
}

int builtin_pwd(t_env **env)
{
	char str[100];
	char *pwd;

	if (env)
	{
		pwd = getcwd(str, 100);
		if (env_getkey(*env, "PWD"))
			env_export(env, "PWD", pwd, 1);
		write(STDOUT_FILENO, pwd, ft_strlen(pwd));
		write(STDOUT_FILENO, "\n", 1);
		exit(0);
	}
	exit(1);
}

int builtin_unset(t_env **env, t_excute *cmds)
{
	int i;

	i = 0;
	while (cmds->arguments && cmds->arguments[i])
	{
		if (!cmds->arguments[i] || check_name(cmds->arguments[i]) < 0)
			return (write(STDERR_FILENO, "unset : not a valid identifier\n", 31), g_status = 1, 0);
		env_unset(env, cmds->arguments[i++]);
	}
	return (1);
}

int env_export(t_env **lst, char *key, char *val, char type)
{
	t_env *newnode;

	if (!lst)
		return 0;
	if (env_getkey(*lst, key))
	{
		if (val && env_update(lst, key, val))
			return 1;
		return 0;
	}
	newnode = ft_calloc(1, sizeof(t_env));
	if (!newnode)
		return 0;
	newnode->key = ft_strdup(key);
	newnode->value = ft_strdup(val);
	newnode->type = type;
	if (!*lst)
		return (*lst = newnode, 1);
	else if (env_addback(lst, newnode))
		return 1;
	return 0;
}
