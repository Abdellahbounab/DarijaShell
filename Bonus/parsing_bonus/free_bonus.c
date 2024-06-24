/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:22:05 by achakkaf          #+#    #+#             */
/*   Updated: 2024/06/24 11:40:43 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

void free_cmd(t_cmd *cmd)
{
	t_cmd *cmd_tmp;
	t_file *tmp_file;

	while (cmd)
	{
		free_array(&cmd->args);
		while (cmd->files)
		{
			free_array(&cmd->files->name);
			tmp_file = cmd->files->next;
			free(cmd->files);
			cmd->files = tmp_file;
		}
		cmd_tmp = cmd->next;
		free(cmd);
		cmd = cmd_tmp;
	}
}

void free_array(char ***array)
{
	int size;

	size = 0;
	if (array && *array)
	{
		while ((*array)[size])
			free((*array)[size++]);
		free((*array));
		*array = NULL;
	}
}

int array_size(char **array)
{
	int size;

	size = 0;
	while (array && array[size])
		size++;
	return (size);
}
