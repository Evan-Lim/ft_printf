/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elim-hon <elim-hon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 08:07:38 by elim-hon          #+#    #+#             */
/*   Updated: 2026/09/24 09:02:01 by elim-hon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printf_parse_flags(t_ft_printf *p)
{
	while (*p->format == '-' || *p->format == '0' || *p->format == '#'
		|| *p->format == ' ' || *p->format == '+')
	{
		if (*p->format == '-')
			p->minus = 1;
		else if (*p->format == '0')
			p->zero = 1;
		else if (*p->format == '#')
			p->hash = 1;
		else if (*p->format == ' ')
			p->space = 1;
		else if (*p->format == '+')
			p->plus = 1;
		p->format++;
	}
}

void	ft_printf_parse_width(t_ft_printf *p)
{
	if (*p->format == '*')
	{
		p->width = va_arg(p->ap, int);
		if (p->width < 0)
		{
			p->minus = 1;
			p->width = -p->width;
		}
		p->format++;
	}
	else
	{
		while (*p->format >= '0' && *p->format <= '9')
		{
			p->width = p->width * 10 + (*p->format - '0');
			p->format++;
		}
	}
}

void	ft_printf_parse_precision(t_ft_printf *p)
{
	if (*p->format != '.')
		return ;
	p->dot = 1;
	p->format++;
	if (*p->format == '*')
	{
		p->precision = va_arg(p->ap, int);
		p->format++;
	}
	else
	{
		while (*p->format >= '0' && *p->format <= '9')
		{
			p->precision = p->precision * 10 + (*p->format - '0');
			p->format++;
		}
	}
}

void	ft_printf_parse_spec(t_ft_printf *p)
{
	p->spec = *p->format;
	if (p->spec)
		p->format++;
}

void	ft_printf_parse(t_ft_printf *p)
{
	ft_printf_parse_flags(p);
	ft_printf_parse_width(p);
	ft_printf_parse_precision(p);
	ft_printf_parse_spec(p);
}
