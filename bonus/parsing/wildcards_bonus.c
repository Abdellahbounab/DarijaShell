/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 10:54:21 by achakkaf          #+#    #+#             */
/*   Updated: 2024/07/04 12:40:13 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

/*
• find all the maches files name
• sort them by name
*/

char **get_files(void)
{
	DIR *dir;
	struct dirent *file;
	char **filenames;

	dir = opendir("."); // PWD
	filenames = NULL;
	if (dir == NULL)
		return (NULL);
	file = readdir(dir);
	while (file)
	{
		if (file->d_name[0] != '.')
			filenames = append_array(filenames, file->d_name);
		file = readdir(dir);
	}
	closedir(dir);
	return (filenames);
}

/*
	• *.c: all files end with .c
	• *: all files exept for those who start with .
	• str*: all file that start with str
	• *str*: all file that str part of
	• etc …
*/

bool match(char *filename, const char *pattern)
{
	bool is_single_q;
	bool is_double_q;

	is_single_q = false;
	is_double_q = false;
	while (*filename && *pattern)
	{
		if (!is_single_q && !is_double_q)
		{
			if (*pattern == '"')
			{
				is_double_q = true;
				pattern++;
				continue;
			}
			else if (*pattern == '\'')
			{
				is_single_q = true;
				pattern++;
				continue;
			}
			else if (*pattern == '*')
			{
				while (*(pattern + 1) == '*')
					pattern++;
				if (*(pattern + 1) == '\0')
					return (true);
				while (*filename)
				{
					if (match(filename, pattern + 1))
						return (true);
					filename++;
				}
				return (false);
			}
		}
		if (*pattern == '"')
		{
			is_double_q = false;
			pattern++;
			continue;
		}
		else if (*pattern == '\'')
		{
			is_single_q = false;
			pattern++;
			continue;
		}
		if (*pattern != *filename)
			return (false);
		filename++;
		pattern++;
	}
	while (*pattern == '*')
		pattern++;
	return (*pattern == '\0' && *filename == '\0');
}

void swap_str(char **stra, char **strb)
{
	char *tmp;
	tmp = *stra;
	*stra = *strb;
	*strb = tmp;
}

void sort_by_name(char **array)
{
	int i;
	int j;

	j = 0;
	// print_array(array);
	while (array && array[j + 1])
	{
		i = 0;
		while (array[i + 1])
		{
			if (ft_strcmp(array[i], array[i + 1]) > 0)
				swap_str(&(array[i]), &(array[i + 1]));
			i++;
		}
		j++;
	}
}

char *wildcard(char *pattern)
{
	int i;
	char *result;
	char *tmp;
	char **filenames;

	i = 0;
	result = NULL;
	filenames = get_files();
	sort_by_name(filenames);
	while (filenames && filenames[i])
	{
		if (match(filenames[i], pattern))
		{
			tmp = result;
			result = ft_strjoin(result, filenames[i]);
			free(tmp);
			tmp = result;
			result = ft_strjoin(result, " ");
			free(tmp);
		}
		i++;
	}
	if (result == NULL)
		result = ft_strdup(pattern);
	free_array(&filenames);
	return (result);
}

/*
bash-3.2$ echo " * "
 *
bash-3.2$ echo ' * '
 *
bash-3.2$ echo "' * '"
' * '


*/

char *var_wildcard(char *line)
{
	char **split;
	int i;
	char *result;
	char *tmp_free;
	char *tmp;

	split = ft_split(line, ' ');
	i = 0;
	result = NULL;
	tmp = NULL;
	while (split && split[i])
	{
		if (ft_strchr(split[i], '*'))
			tmp = wildcard(split[i]);
		else
			tmp = ft_strdup(split[i]);
		tmp_free = result;
		result = ft_strjoin(result, tmp);
		free(tmp_free);
		free(tmp);
		tmp_free = result;
		result = ft_strjoin(result, " ");
		free(tmp_free);
		i++;
	}
	free_array(&split);
	return (result);
}
