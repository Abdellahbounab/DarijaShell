/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Achakkaf <zizcarschak1@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 19:56:22 by Achakkaf          #+#    #+#             */
/*   Updated: 2023/12/23 09:41:49 by Achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sptr;
	size_t	i;
	size_t	slen;

	i = 0;
	sptr = NULL;
	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (start > slen)
		len = 0;
	else if (len > slen - start)
		len = slen - start;
	sptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!sptr)
		return (NULL);
	while (i < len && s[start + i])
	{
		sptr[i] = s[start + i];
		i++;
	}
	sptr[i] = '\0';
	return (sptr);
}
