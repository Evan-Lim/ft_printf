/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elim-hon <elim-hon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 08:17:14 by elim-hon          #+#    #+#             */
/*   Updated: 2026/09/24 08:42:06 by elim-hon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_putchar_count(char c)
{
	return ((int)write(1, &c, 1));
}

int	ft_printf_putstr_count(const char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i])
		i++;
	write(1, s, i);
	return (i);
}

int	ft_printf_pad(int width, char c)
{
	int	i;

	i = 0;
	while (i < width)
	{
		write(1, &c, 1);
		i++;
	}
	return (i);
}
