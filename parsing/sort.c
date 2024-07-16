/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achakkaf <achakkaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:45:12 by achakkaf          #+#    #+#             */
/*   Updated: 2024/07/16 10:23:52 by achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	swap_str(char **stra, char **strb)
{
	char	*tmp;

	tmp = *stra;
	*stra = *strb;
	*strb = tmp;
}

void	sort_by_name(char **array)
{
	int	i;
	int	j;

	j = 0;
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
