/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elim-hon <elim-hon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 08:34:55 by elim-hon          #+#    #+#             */
/*   Updated: 2026/09/24 09:03:50 by elim-hon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_get_base(t_ft_printf *p)
{
	if (p->spec == 'x' || p->spec == 'X')
		return (16);
	return (10);
}

int	ft_printf_is_upper(t_ft_printf *p)
{
	if (p->spec == 'X')
		return (1);
	return (0);
}

int	ft_printf_numlen(unsigned long n, int base)
{
	int	len;

	len = 1;
	while (n >= (unsigned long)base)
	{
		n /= base;
		len++;
	}
	return (len);
}

char	*ft_printf_uitoa_base(unsigned long n, int base, int uppercase)
{
	const char	*digits;
	char		*s;
	int			len;

	digits = "0123456789abcdef";
	if (uppercase)
		digits = "0123456789ABCDEF";
	len = ft_printf_numlen(n, base);
	s = malloc(len + 1);
	if (s == NULL)
		return (NULL);
	s[len] = '\0';
	while (len > 0)
	{
		len--;
		s[len] = digits[n % base];
		n /= base;
	}
	return (s);
}
