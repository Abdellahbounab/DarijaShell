/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_part2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 09:23:59 by achakkaf          #+#    #+#             */
/*   Updated: 2024/07/09 09:27:28 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "../parsing/parsing.h"
#include "../excution/excution.h"
#include "../types.h"

static void print_env(t_env *env, int flag)
{
    write(STDOUT_FILENO, env->key, ft_strlen(env->key));
    write(STDOUT_FILENO, "=", 1);
    if (flag)
        write(STDOUT_FILENO, "\"", 1);
    if (env->value)
        write(STDOUT_FILENO, env->value, ft_strlen(env->value));
    if (flag)
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

int builtin_export(t_env **env, t_excute *cmds)
{
    int i;
    char **arr;
    char *str;
    char type;

    i = 0;
    type = 0;
    if (cmds->arguments && !cmds->arguments[0])
        return (builtin_env(*env, 1));
    while (cmds->arguments && cmds->arguments[i])
    {
        arr = ft_split(cmds->arguments[i], '=');
        if (!arr[0] || check_name(arr[0]) < 0)
            return (write(STDERR_FILENO, "export : not a valid identifier\n", 32), status = 1, 0);
        if (!arr[1] && cmds->arguments[i][ft_strlen(cmds->arguments[i]) - 1] != '=')
            type = 1;
        str = join_strs(arr + 1);
        env_export(env, arr[0], str, type);
        free_array(&arr);
        free(str);
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

    num = 0;
    if (cmds->arguments)
    {
        if (cmds->arguments[0])
            num = ft_atoi(cmds->arguments[0]);
        if (cmds->arguments[0] && !is_numerique(cmds->arguments[0]))
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
