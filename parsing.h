/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:12:12 by achakkaf          #+#    #+#             */
/*   Updated: 2024/05/28 12:19:57 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
#define PARSING_H

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include "mylib/libft.h"

typedef struct s_command
{
	char *cmd;
	char **args;
	char *path;
	int number_input;
	int	*input_fd;
	int *output_fd;
	int *erorr_fd;
	int append;
}	t_command ;

//variables are type string
char	**split_cmd(char *command);
void	exec_command(char **cmd, char **env);
#endif