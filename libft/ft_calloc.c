/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Achakkaf <zizcarschak1@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 18:13:09 by Achakkaf          #+#    #+#             */
/*   Updated: 2023/12/25 13:16:20 by Achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	i;

	ptr = NULL;
	if (count != 0 && size > (18446744073709551615ULL / count))
		return (NULL);
	ptr = (void *)malloc(count * size);
	i = 0;
	while (i < count * size && ptr)
	{
		((unsigned char *)ptr)[i] = 0;
		i++;
	}
	return (ptr);
}
