/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_num_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elim-hon <elim-hon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 08:26:14 by elim-hon          #+#    #+#             */
/*   Updated: 2026/09/24 09:04:47 by elim-hon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_extra_len(t_ft_printf *p, unsigned long n, int negative)
{
	int	len;

	len = 0;
	if (negative || p->plus || p->space)
		len++;
	if (p->hash && ft_printf_get_base(p) == 16 && n != 0)
		len += 2;
	return (len);
}

void	ft_printf_sign(t_ft_printf *p, int negative)
{
	if (negative)
		p->count += ft_printf_putchar_count('-');
	else if (p->plus)
		p->count += ft_printf_putchar_count('+');
	else if (p->space)
		p->count += ft_printf_putchar_count(' ');
}

void	ft_printf_prefix(t_ft_printf *p, unsigned long n)
{
	if (p->hash == 0 || ft_printf_get_base(p) != 16 || n == 0)
		return ;
	if (p->spec == 'X')
		p->count += ft_printf_putstr_count("0X");
	else
		p->count += ft_printf_putstr_count("0x");
}

void	ft_printf_number_all(t_ft_printf *p, char *s, unsigned long n,
			int negative)
{
	int	digits;
	int	zeros;
	int	total;

	digits = ft_printf_numlen(n, ft_printf_get_base(p));
	if (p->dot && p->precision == 0 && n == 0)
		digits = 0;
	zeros = 0;
	if (p->dot && p->precision > digits)
		zeros = p->precision - digits;
	total = digits + zeros + ft_printf_extra_len(p, n, negative);
	if (!p->minus && !(p->zero && !p->dot))
		p->count += ft_printf_pad(p->width - total, ' ');
	ft_printf_sign(p, negative);
	ft_printf_prefix(p, n);
	if (!p->minus && p->zero && !p->dot)
		p->count += ft_printf_pad(p->width - total, '0');
	p->count += ft_printf_pad(zeros, '0');
	if (digits)
		p->count += ft_printf_putstr_count(s);
	if (p->minus)
		p->count += ft_printf_pad(p->width - total, ' ');
}
