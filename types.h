/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:30:27 by achakkaf          #+#    #+#             */
/*   Updated: 2024/07/16 10:33:23 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>
# include <signal.h>
# include <dirent.h>
# include <stdbool.h>
# include "libft/libft.h"

# define ERROR -1
# define GOOD 0

# define SINGLE_Q 39
# define DOUBLE_Q 34
# define WITHOUT 32

# ifndef TAB
#  define TAB 9
# endif

# ifndef SPACE
#  define SPACE 32
# endif

int	g_status;

typedef enum s_type
{
	INFILE = O_RDONLY,
	OUFILE = O_CREAT | O_TRUNC | O_WRONLY,
	APPEND = O_CREAT | O_WRONLY | O_APPEND,
	HERE_DOC_USED = 6,
	HERE_DOC_SIMPLE = 4,
	HERE_DOC_SPECIAL = 5,
}	t_type;

typedef struct s_env
{
	char			*key;
	char			*value;
	char			type;
	struct s_env	*next;
}	t_env;

typedef struct s_file
{
	char			**name;
	t_type			type;
	struct s_file	*next;
}	t_file;

typedef struct s_cmd
{
	char			**args;
	t_file			*files;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_info
{
	int		start;
	int		end;
	int		cmd_i;
	int		file;
	t_env	*env;
	t_cmd	*cmd;
}	t_info;

typedef struct s_excute
{
	char			*cmd;
	char			**arguments;
	int				infile;
	int				outfile;
	int				pid;
	struct s_excute	*next;
}	t_excute;

#endif
