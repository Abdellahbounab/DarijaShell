/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:12:12 by achakkaf          #+#    #+#             */
/*   Updated: 2024/05/30 15:05:01 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
#define PARSING_H

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include "libft/libft.h"
#include <fcntl.h>

# define ERROR -1
# define GOOD 0
typedef struct s_command
{
	char	*cmd;
	char	**args;
	char	*path;
	int		number_input;
	char	*input_files;
	char	*output_files;
	char 	*error_fd;
	int		append;
}	t_command ;

typedef struct s_env
{
	char *key;
	char *value;
	struct s_env *next;
} t_env;

//variables are type string
char	**split_cmd(char *command);
void	exec_command(char *command, char **env);

#endif