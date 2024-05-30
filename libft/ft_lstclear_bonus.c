/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Achakkaf <zizcarschak1@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 15:49:07 by Achakkaf          #+#    #+#             */
/*   Updated: 2023/12/23 09:37:24 by Achakkaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*ptr;
	t_list	*next;

	if (!lst || !(*lst) || !del)
		return ;
	ptr = *lst;
	while (ptr != NULL)
	{
		next = ptr->next;
		del(ptr->content);
		free(ptr);
		ptr = next;
	}
	*lst = NULL;
}
