/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 12:50:04 by achakkaf          #+#    #+#             */
/*   Updated: 2024/07/15 10:58:53 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char *extand_file_name(char **tokens, t_info *info, int *is_expend, t_type type)
{
	char *strwild;
	char *tmp;

	strwild = NULL;
	if (type != HERE_DOC_SIMPLE)
	{
		tmp = parsing_extend_var(tokens[info->cmd_i], info->env, is_expend);
		strwild = star_magic(tmp, *is_expend, info->env);
		free(tmp);
	}
	else
		strwild = tokens[info->cmd_i];
	return (strwild);
}

static void set_type(t_file *file, int type)
{
	char *tmp;

	tmp = NULL;
	if (file->name && type == HERE_DOC_SIMPLE && (ft_strchr(file->name[0], '\'') || ft_strchr(file->name[0], '"')))
	{
		file->type = HERE_DOC_SPECIAL;
		tmp = file->name[0];
		file->name[0] = ft_filter(file->name[0]);
		free(tmp);
	}
	else if (type == HERE_DOC_SIMPLE)
		file->type = HERE_DOC_SIMPLE;
	else
		file->type = type;
}

// static void filter_filenames(t_file *file)
// {
// 	int i;
// 	char *tmp;

// 	i = 0;
// 	while (file->name && file->name[i])
// 	{
// 		tmp = file->name[i];
// 		file->name[i] = ft_filter(file->name[i]);
// 		free(tmp);
// 		i++;
// 	}
// }

int create_files(t_cmd *cmd, char **tokens, t_info *info, t_type type)
{
	t_file *file;
	int is_expend;
	char *strwild;

	strwild = NULL;
	is_expend = 0;
	file = ft_calloc(1, sizeof(t_file));
	if (file == NULL)
		return (ERROR);
	strwild = extand_file_name(tokens, info, &is_expend, type);
	if (is_expend == 1)
		file->name = ft_split(strwild, SPACE);
	else
		file->name = parsing_split(strwild);
	if (type != HERE_DOC_SIMPLE)
		free(strwild);
	set_type(file, type);
	// filter_filenames(file);
	add_back_file(cmd, file);
	return (GOOD);
}
