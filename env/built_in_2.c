/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounab <abounab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 09:23:59 by achakkaf          #+#    #+#             */
/*   Updated: 2024/07/15 14:45:54 by abounab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "../parsing/parsing.h"
#include "../excution/excution.h"
#include "../types.h"

static void print_env(t_env *env, int flag)
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

int builtin_env(t_env *env, int flag)
{
    int counter;

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

int until_char(char *str, char c)
{
	int i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == c)
			return i;
		i++;
	}
	return (-1);
}

int builtin_export(t_env **env, t_excute *cmds)
{
    int i;
    // char **arr;
	char *key;
    char *str;
    char type;

    i = 0;
    type = 0;
	str = NULL;
    if (cmds->arguments && !cmds->arguments[0])
        return (builtin_env(*env, 1));
    while (cmds->arguments && cmds->arguments[i])
    {
		if (until_char(cmds->arguments[i], '=') < 0)
		{
			key = ft_strdup(cmds->arguments[i]);
			type = 1;
		}
		else
			key = ft_substr(cmds->arguments[i], 0, until_char(cmds->arguments[i], '='));
        if (!key || check_name(key) < 0)
            return (free(key), write(STDERR_FILENO, "export : not a valid identifier\n", 32), status = 1, 0);
		if (!type)
			str = ft_strdup(cmds->arguments[i] + until_char(cmds->arguments[i], '=') + 1);
        env_export(env, key, str, type);
		free(key);
        free(str);
		str = NULL;
        i++;
    }
    return (1);
}

int is_numerique(char *str)
{
    int i;
    int len;

    i = 0;
    if (str)
        len = ft_strlen(str);
    if (str[i] == '-' || str[i] == '+')
        i++;
    while (str && str[i] && !ft_isdigit(str[i]))
        i++;
    if (str && len == i)
        return 1;
    return 0;
}

int builtin_exit(t_env **env, t_excute *cmds)
{
    int num;
	char	*arg;

    num = status;
	arg = NULL;
    if (cmds->arguments)
    {
        if (cmds->arguments[0])
		{
			arg = ft_strtrim(cmds->arguments[0], " \t");
			if (arg)
           		num = ft_atoi(arg);
		}
        if (arg && !is_numerique(arg))
            ft_perror("exit : ", "numeric argument required", 255);
        if (cmds->arguments[0] && cmds->arguments[1])
        {
            status = 1;
            return (write(STDERR_FILENO, "exit: too many arguments\n", 25));
        }
    }
    free_env(env);
    write(STDIN_FILENO, "exit\n", 5);
    exit(num);
}
