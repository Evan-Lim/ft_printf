/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_num.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elim-hon <elim-hon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 08:16:59 by elim-hon          #+#    #+#             */
/*   Updated: 2026/09/24 09:01:27 by elim-hon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printf_int(t_ft_printf *p)
{
	long			n;
	int				neg;
	unsigned long	u;

	n = (long)va_arg(p->ap, int);
	neg = 0;
	if (n < 0)
		neg = 1;
	if (neg)
		u = (unsigned long)(-n);
	else
		u = (unsigned long)n;
	ft_printf_number(p, u, neg);
}

void	ft_printf_unsigned(t_ft_printf *p)
{
	unsigned int	n;

	n = va_arg(p->ap, unsigned int);
	ft_printf_number(p, (unsigned long)n, 0);
}

void	ft_printf_hex(t_ft_printf *p)
{
	unsigned int	n;

	n = va_arg(p->ap, unsigned int);
	ft_printf_number(p, (unsigned long)n, 0);
}

void	ft_printf_number(t_ft_printf *p, unsigned long n, int negative)
{
	char	*s;

	s = ft_printf_uitoa_base(n, ft_printf_get_base(p), ft_printf_is_upper(p));
	ft_printf_number_all(p, s, n, negative);
	free(s);
}
