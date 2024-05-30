/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:12:12 by achakkaf          #+#    #+#             */
/*   Updated: 2024/05/30 19:54:07 by achakkaf         ###   ########.fr       */
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
	char	**args;
	char	*path;
	char	*input_files;
	char	*output_files;
	char	*limitor;
	int		append;
	int 	heredoc;
	struct s_command *next;
}	t_command ;

//variables are type string
typedef struct s_env
{
	char *key;
	char *value;
	struct s_env *next;
} t_env;


/// @brief split a line depand to a space or tab or single quote or double quote
/// @return an array of tokans
char	**split_cmd(char *command);

/// @brief create a linked list with command it move to the next command found a pipe
t_command *create_cmd_linked_list(char **split_cmd);

/// @brief it removes the wrong quote like "make""file"-> makefile
char *filtre_quote(char *str);

/// @brief appand and element to end of an array
char **append_array(char **old_array, char *arg);

// void	exec_command(char *command, char **env);
#endif