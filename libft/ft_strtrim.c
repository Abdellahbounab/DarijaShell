/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Achakkaf <zizcarschak1@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 12:15:35 by Achakkaf          #+#    #+#             */
/*   Updated: 2023/12/21 09:46:50 by Achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	fist_part(char const *s1, char const *set, int i)
{
	int	j;

	j = 0;
	while (s1[i])
	{
		if (s1[i] == set[j])
			j = 0;
		else
		{
			if (s1[i] != set[j] && !set[j])
				break ;
			j++;
			continue ;
		}
		i++;
	}
	return (i);
}

static int	last_part(char const *s1, char const *set, int slen)
{
	int	j;

	j = 0;
	while (slen)
	{
		if (s1[slen] == set[j])
			j = 0;
		else
		{
			if (s1[slen] != set[j] && !set[j])
				break ;
			j++;
			continue ;
		}
		slen--;
	}
	return (slen);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s;
	int		i;
	int		slen;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	slen = ft_strlen(s1);
	i = fist_part(s1, set, i);
	slen = last_part(s1, set, slen);
	s = ft_substr(s1, i, slen - i + 1);
	return (s);
}
