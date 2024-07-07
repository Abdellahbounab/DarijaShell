/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounab <abounab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:30:27 by achakkaf          #+#    #+#             */
/*   Updated: 2024/07/07 12:33:49 by abounab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef TYPES_BONUS_H
#define TYPES_BONUS_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <dirent.h>
#include <stdbool.h>

#include <signal.h>
// #include <readline/chardefs.h>

#include "../libft/libft.h"

#define ERROR -1
#define GOOD 0

#define SINGLE_Q 39
#define DOUBLE_Q 34
#define WITHOUT 32

#ifndef TAB
#define TAB 9
#endif

#ifndef SPACE
#define SPACE 32
#endif

int status;

typedef enum s_type
{
	INFILE = O_RDONLY,
	OUFILE = O_CREAT | O_TRUNC | O_WRONLY,
	APPEND = O_CREAT | O_WRONLY | O_APPEND,
	HERE_DOC_SIMPLE = 4,
	HERE_DOC_SPECIAL = 5,
} t_type;

typedef struct s_env
{
	char *key;
	char *value;
	char type;
	struct s_env *next;
} t_env;

typedef struct s_file
{
	char **name;
	t_type type;
	struct s_file *next;
} t_file;

typedef enum s_relation
{
	AND,
	OR,
	NONE,
} t_relation;

// yellow
typedef struct s_cmd
{
	char **args;
	int *status;
	t_file *files;
	struct s_cmd *next;
	struct s_bonus *bonus;
} t_cmd;

// new enum t_relation + t_bonus + t_cmd{ + t_bonus*}

// red
typedef struct s_bonus{
	char *line;
	char  **cmdline;
	t_relation relation;
	t_cmd *command;
	struct s_bonus *next;
}t_bonus;


typedef struct s_excute
{
	char *cmd;
	char **arguments;
	int infile;
	int outfile;
	int pid;
	struct s_excute *next;
} t_excute;

// the above struct is made for bonus part
typedef struct s_info
{
	int start;
	int end;
	int cmd_i;
	int file;
	int dollar;
	int var_from;
	t_env *env;
	t_cmd *cmd;
} t_info;



t_bonus	*create_bonus(char **tokens);
int	ft_minishell(t_bonus *bonus, t_env **env);
int	excution(t_bonus *bonus, t_env **env, int flag);

#endif