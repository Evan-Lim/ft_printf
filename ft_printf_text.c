/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_text.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elim-hon <elim-hon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 08:16:42 by elim-hon          #+#    #+#             */
/*   Updated: 2026/09/24 10:17:20 by elim-hon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printf_char(t_ft_printf *p)
{
	char	c;
	int		w;

	c = (char)va_arg(p->ap, int);
	w = 0;
	if (p->width > 1)
		w = p->width - 1;
	if (!p->minus)
		p->count += ft_printf_pad(w, ' ');
	p->count += ft_printf_putchar_count(c);
	if (p->minus)
		p->count += ft_printf_pad(w, ' ');
}

void	ft_printf_string(t_ft_printf *p)
{
	char	*s;
	int		len;

	s = va_arg(p->ap, char *);
	if (s == NULL)
	{
		if (p->dot && p->precision < 6)
			s = "";
		else
			s = "(null)";
	}
	len = 0;
	while (s[len])
		len++;
	if (p->dot && p->precision < len)
		len = p->precision;
	if (!p->minus)
		p->count += ft_printf_pad(p->width - len, ' ');
	p->count += (int)write(1, s, len);
	if (p->minus)
		p->count += ft_printf_pad(p->width - len, ' ');
}

void	ft_printf_pointer(t_ft_printf *p)
{
	unsigned long	n;
	char			*s;
	int				len;

	n = (unsigned long)va_arg(p->ap, void *);
	if (n == 0)
	{
		len = 5;
		if (!p->minus)
			p->count += ft_printf_pad(p->width - len, ' ');
		p->count += ft_printf_putstr_count("(nil)");
		if (p->minus)
			p->count += ft_printf_pad(p->width - len, ' ');
		return ;
	}
	s = ft_printf_uitoa_base(n, 16, 0);
	len = ft_printf_numlen(n, 16) + 2;
	if (!p->minus)
		p->count += ft_printf_pad(p->width - len, ' ');
	p->count += ft_printf_putstr_count("0x");
	p->count += ft_printf_putstr_count(s);
	if (p->minus)
		p->count += ft_printf_pad(p->width - len, ' ');
	free(s);
}

void	ft_printf_percent(t_ft_printf *p)
{
	p->count += ft_printf_putchar_count('%');
}

/*
void	ft_printf_percent(t_ft_printf *p)
{
	int	w;

	w = 0;
	if (p->width > 1)
		w = p->width - 1;
	if (!p->minus)
		p->count += ft_printf_pad(w, ' ');
	p->count += ft_printf_putchar_count('%');
	if (p->minus)
		p->count += ft_printf_pad(w, ' ');
}
*/
