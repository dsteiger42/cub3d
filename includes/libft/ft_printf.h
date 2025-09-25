/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarlos- <scarlos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 12:57:39 by scarlos-          #+#    #+#             */
/*   Updated: 2025/09/25 12:57:41 by scarlos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>
# include <stdint.h>

int	ft_base_ul(unsigned long long nbr, char *base);
int	ft_base_u(unsigned int nbr, char *base);
int	ft_base(int nbr, char *base);
int	ft_printf(const char *str, ...);

#endif
