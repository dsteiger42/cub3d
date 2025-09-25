/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlos- <scarlos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 12:55:54 by scarlos-          #+#    #+#             */
/*   Updated: 2025/09/25 12:55:56 by scarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*templst;

	if (*lst != NULL)
	{
		templst = *lst;
		while (templst->next != NULL)
			templst = templst->next;
		templst->next = new;
	}
	else
		*lst = new;
}
