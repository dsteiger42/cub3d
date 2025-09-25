/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlos- <scarlos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 12:56:03 by scarlos-          #+#    #+#             */
/*   Updated: 2025/09/25 12:56:05 by scarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*templst;
	t_list	*next;

	if (*lst == NULL || del == NULL)
		return ;
	templst = *lst;
	next = NULL;
	while (templst != NULL)
	{
		next = templst->next;
		del(templst->content);
		free(templst);
		templst = next;
	}
	*lst = NULL;
}
