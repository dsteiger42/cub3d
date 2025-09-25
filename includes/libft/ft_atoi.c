/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 12:54:50 by scarlos-          #+#    #+#             */
/*   Updated: 2025/09/25 13:59:36 by dsteiger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	j;
	int	minus;

	i = 0;
	j = 0;
	minus = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			minus = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		j = (j * 10) + (nptr[i] - '0');
		i++;
	}
	return (j * minus);
}

/*
int	main(void)
{
	char *str = "       123466666666";
	printf("%d\n", ft_atoi(str));
	printf("%d\n", atoi(str));
}*/
