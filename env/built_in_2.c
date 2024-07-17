/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounab <abounab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 09:23:59 by achakkaf          #+#    #+#             */
/*   Updated: 2024/07/17 21:27:04 by abounab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../excution/excution.h"
#include "../parsing/parsing.h"
#include "env.h"

static void	print_env(t_env *env, int flag)
{
	write(STDOUT_FILENO, env->key, ft_strlen(env->key));
	if ((env->value && flag) || !flag)
		write(STDOUT_FILENO, "=", 1);
	if (env->value && flag)
		write(STDOUT_FILENO, "\"", 1);
	if (env->value)
		write(STDOUT_FILENO, env->value, ft_strlen(env->value));
	if (env->value && flag)
		write(STDOUT_FILENO, "\"", 1);
	write(STDOUT_FILENO, "\n", 1);
}

int	builtin_env(t_env *env, int flag)
{
	int	counter;

	counter = 0;
	if (!env_getkey(env, "PATH"))
		ft_perror("env :", "No such file or directory", 127);
	while (env)
	{
		if (flag)
			write(STDOUT_FILENO, "	declare -x ", 12);
		else
			env_export(&env, "_", "usr/bin/env", 0);
		if ((!flag && !env->type) || flag)
			print_env(env, flag);
		env = env->next;
		counter++;
	}
	env_unset(&env, "_");
	exit(0);
}

static int	until_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

static void	handle_exp_case(char *arg, t_env **env, int type, int *err)
{
	char	*key;
	char	*str;

	str = NULL;
	if (until_char(arg, '=') < 0)
	{
		key = ft_strdup(arg);
		type = 1;
	}
	else
		key = ft_substr(arg, 0, until_char(arg, '='));
	if (!key || !*key || check_name(key) < 0)
	{
		write(STDERR_FILENO, "export : not a valid identifier\n", 32);
		*err = 1;
	}
	else
	{
		if (!type)
			str = ft_strdup(arg + until_char(arg, '=') + 1);
		env_export(env, key, str, type);
	}
	free(key);
	free(str);
	str = NULL;
}

int	builtin_export(t_env **env, t_excute *cmds)
{
	int		i;
	int		err;
	char	type;

	i = 0;
	err = 0;
	if (cmds->arguments && !cmds->arguments[0])
		return (builtin_env(*env, 1));
	while (cmds->arguments && cmds->arguments[i])
	{
		type = 0;
		handle_exp_case(cmds->arguments[i++], env, type, &err);
	}
	g_status = err;
	return (1);
}
