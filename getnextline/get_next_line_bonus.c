/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounab <abounab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 13:44:03 by abounab           #+#    #+#             */
/*   Updated: 2024/07/16 11:50:53 by abounab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	until_line(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

char	*ft_read_buff(int fd, char *str)
{
	char	buff[1];
	int		count;
	char	*tmp;

	count = 1;
	while (count)
	{
		tmp = str;
		count = read(fd, buff, 1);
		if (count < 0)
			return (free(str), NULL);
		buff[count] = 0;
		str = ft_strjoin(tmp, buff);
		free(tmp);
		if (!str)
			return (0);
		if (until_line(buff) < ft_strlen(buff))
			break ;
		buff[0] = 0;
	}
	return (str);
}

char	*ft_get_line(char *str)
{
	size_t	len;
	char	*cpy;

	if (!*str)
		return (0);
	len = until_line(str) + 1;
	if (str[until_line(str)])
		len++;
	cpy = (char *)malloc(sizeof(char) * len);
	if (!cpy)
		return (0);
	return (ft_strlcpy(cpy, str, len), cpy);
}

char	*ft_update(char *str)
{
	char	*cpy;

	if (!str[until_line(str)])
		return (0);
	cpy = ft_strdup(str + until_line(str) + 1);
	if (!cpy)
		return (0);
	return (cpy);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*str[10240];
	char		*tmp;

	if (fd < 0 || read(fd, 0, 0) < 0)
		return (free(str[fd]), str[fd] = NULL, NULL);
	tmp = ft_read_buff(fd, str[fd]);
	if (!tmp)
		return (str[fd] = NULL, NULL);
	line = ft_get_line(tmp);
	str[fd] = ft_update(tmp);
	free(tmp);
	tmp = NULL;
	if (!line)
		return (free(str[fd]), str[fd] = NULL, NULL);
	return (line);
}
