/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elim-hon <elim-hon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/23 11:00:44 by elim-hon          #+#    #+#             */
/*   Updated: 2026/09/24 09:38:12 by elim-hon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printf_init_state(t_ft_printf *p)
{
	p->minus = 0;
	p->zero = 0;
	p->hash = 0;
	p->space = 0;
	p->plus = 0;
	p->width = 0;
	p->dot = 0;
	p->precision = 0;
	p->spec = 0;
}

void	ft_printf_arg(t_ft_printf *p)
{
	if (p->spec == 'c')
		ft_printf_char(p);
	else if (p->spec == 's')
		ft_printf_string(p);
	else if (p->spec == 'p')
		ft_printf_pointer(p);
	else if (p->spec == 'd' || p->spec == 'i')
		ft_printf_int(p);
	else if (p->spec == 'u')
		ft_printf_unsigned(p);
	else if (p->spec == 'x' || p->spec == 'X')
		ft_printf_hex(p);
	else if (p->spec == '%')
		ft_printf_percent(p);
}

int	ft_printf(const char *format, ...)
{
	t_ft_printf	p;

	if (format == NULL)
		return (-1);
	p.format = format;
	p.count = 0;
	va_start(p.ap, format);
	while (*p.format)
	{
		if (*p.format == '%')
		{
			p.format++;
			ft_printf_init_state(&p);
			ft_printf_parse(&p);
			ft_printf_arg(&p);
		}
		else
			p.count += ft_printf_putchar_count(*p.format++);
	}
	va_end(p.ap);
	return (p.count);
}

/*
#include "ft_printf.h"
#include <limits.h>
#include <stdio.h>

int	main(void)
{
	int	x;

	printf("=== %%c ===\n");
	printf("printf:    [%c]\n", 'A');
	ft_printf("ft_printf: [%c]\n", 'A');
	printf("printf:    [%5c]\n", 'A');
	ft_printf("ft_printf: [%5c]\n", 'A');
	printf("printf:    [%-5c]\n", 'A');
	ft_printf("ft_printf: [%-5c]\n", 'A');
	printf("printf:    [%05c]\n", 'A');
	ft_printf("ft_printf: [%05c]\n", 'A');
	printf("printf:    [%c]\n", 0);
	ft_printf("ft_printf: [%c]\n", 0);
	printf("=== %%s ===\n");
	printf("printf:    [%s]\n", "hello");
	ft_printf("ft_printf: [%s]\n", "hello");
	printf("printf:    [%10s]\n", "hello");
	ft_printf("ft_printf: [%10s]\n", "hello");
	printf("printf:    [%-10s]\n", "hello");
	ft_printf("ft_printf: [%-10s]\n", "hello");
	printf("printf:    [%.3s]\n", "hello");
	ft_printf("ft_printf: [%.3s]\n", "hello");
	printf("printf:    [%10.3s]\n", "hello");
	ft_printf("ft_printf: [%10.3s]\n", "hello");
	printf("printf:    [%-10.3s]\n", "hello");
	ft_printf("ft_printf: [%-10.3s]\n", "hello");
	printf("printf:    [%s]\n", (char *)NULL);
	ft_printf("ft_printf: [%s]\n", (char *)NULL);
	printf("printf:    [%10s]\n", "");
	ft_printf("ft_printf: [%10s]\n", "");
	printf("printf:    [%.0s]\n", "hello");
	ft_printf("ft_printf: [%.0s]\n", "hello");
	printf("=== %%p ===\n");
	x = 42;
	printf("printf:    [%p]\n", (void *)&x);
	ft_printf("ft_printf: [%p]\n", (void *)&x);
	printf("printf:    [%20p]\n", (void *)&x);
	ft_printf("ft_printf: [%20p]\n", (void *)&x);
	printf("printf:    [%-20p]\n", (void *)&x);
	ft_printf("ft_printf: [%-20p]\n", (void *)&x);
	printf("printf:    [%p]\n", (void *)NULL);
	ft_printf("ft_printf: [%p]\n", (void *)NULL);
	printf("printf:    [%20p]\n", (void *)NULL);
	ft_printf("ft_printf: [%20p]\n", (void *)NULL);
	printf("=== %%d and %%i ===\n");
	printf("printf:    [%d]\n", 0);
	ft_printf("ft_printf: [%d]\n", 0);
	printf("printf:    [%d]\n", 42);
	ft_printf("ft_printf: [%d]\n", 42);
	printf("printf:    [%d]\n", -42);
	ft_printf("ft_printf: [%d]\n", -42);
	printf("printf:    [%i]\n", 42);
	ft_printf("ft_printf: [%i]\n", 42);
	printf("printf:    [%i]\n", -42);
	ft_printf("ft_printf: [%i]\n", -42);
	printf("printf:    [%d]\n", INT_MAX);
	ft_printf("ft_printf: [%d]\n", INT_MAX);
	printf("printf:    [%d]\n", INT_MIN);
	ft_printf("ft_printf: [%d]\n", INT_MIN);
	printf("printf:    [%+d]\n", 42);
	ft_printf("ft_printf: [%+d]\n", 42);
	printf("printf:    [%+d]\n", -42);
	ft_printf("ft_printf: [%+d]\n", -42);
	printf("printf:    [% d]\n", 42);
	ft_printf("ft_printf: [% d]\n", 42);
	printf("printf:    [% d]\n", -42);
	ft_printf("ft_printf: [% d]\n", -42);
	printf("printf:    [%10d]\n", 42);
	ft_printf("ft_printf: [%10d]\n", 42);
	printf("printf:    [%-10d]\n", 42);
	ft_printf("ft_printf: [%-10d]\n", 42);
	printf("printf:    [%010d]\n", 42);
	ft_printf("ft_printf: [%010d]\n", 42);
	printf("printf:    [%010d]\n", -42);
	ft_printf("ft_printf: [%010d]\n", -42);
	printf("printf:    [%+010d]\n", 42);
	ft_printf("ft_printf: [%+010d]\n", 42);
	printf("printf:    [%.5d]\n", 42);
	ft_printf("ft_printf: [%.5d]\n", 42);
	printf("printf:    [%.5d]\n", -42);
	ft_printf("ft_printf: [%.5d]\n", -42);
	printf("printf:    [%.0d]\n", 0);
	ft_printf("ft_printf: [%.0d]\n", 0);
	printf("printf:    [%10.5d]\n", 42);
	ft_printf("ft_printf: [%10.5d]\n", 42);
	printf("printf:    [%-10.5d]\n", 42);
	ft_printf("ft_printf: [%-10.5d]\n", 42);
	printf("printf:    [%+10.5d]\n", 42);
	ft_printf("ft_printf: [%+10.5d]\n", 42);
	printf("printf:    [% 10.5d]\n", 42);
	ft_printf("ft_printf: [% 10.5d]\n", 42);
	printf("printf:    [%010.5d]\n", 42);
	ft_printf("ft_printf: [%010.5d]\n", 42);
	printf("=== %%u ===\n");
	printf("printf:    [%u]\n", 0);
	ft_printf("ft_printf: [%u]\n", 0);
	printf("printf:    [%u]\n", 42);
	ft_printf("ft_printf: [%u]\n", 42);
	printf("printf:    [%u]\n", UINT_MAX);
	ft_printf("ft_printf: [%u]\n", UINT_MAX);
	printf("printf:    [%10u]\n", 42);
	ft_printf("ft_printf: [%10u]\n", 42);
	printf("printf:    [%-10u]\n", 42);
	ft_printf("ft_printf: [%-10u]\n", 42);
	printf("printf:    [%010u]\n", 42);
	ft_printf("ft_printf: [%010u]\n", 42);
	printf("printf:    [%.5u]\n", 42);
	ft_printf("ft_printf: [%.5u]\n", 42);
	printf("printf:    [%.0u]\n", 0);
	ft_printf("ft_printf: [%.0u]\n", 0);
	printf("printf:    [%10.5u]\n", 42);
	ft_printf("ft_printf: [%10.5u]\n", 42);
	printf("printf:    [%-10.5u]\n", 42);
	ft_printf("ft_printf: [%-10.5u]\n", 42);
	printf("=== %%x ===\n");
	printf("printf:    [%x]\n", 0);
	ft_printf("ft_printf: [%x]\n", 0);
	printf("printf:    [%x]\n", 42);
	ft_printf("ft_printf: [%x]\n", 42);
	printf("printf:    [%x]\n", 255);
	ft_printf("ft_printf: [%x]\n", 255);
	printf("printf:    [%x]\n", UINT_MAX);
	ft_printf("ft_printf: [%x]\n", UINT_MAX);
	printf("printf:    [%#x]\n", 0);
	ft_printf("ft_printf: [%#x]\n", 0);
	printf("printf:    [%#x]\n", 42);
	ft_printf("ft_printf: [%#x]\n", 42);
	printf("printf:    [%#x]\n", 255);
	ft_printf("ft_printf: [%#x]\n", 255);
	printf("printf:    [%10x]\n", 42);
	ft_printf("ft_printf: [%10x]\n", 42);
	printf("printf:    [%-10x]\n", 42);
	ft_printf("ft_printf: [%-10x]\n", 42);
	printf("printf:    [%010x]\n", 42);
	ft_printf("ft_printf: [%010x]\n", 42);
	printf("printf:    [%#010x]\n", 42);
	ft_printf("ft_printf: [%#010x]\n", 42);
	printf("printf:    [%.5x]\n", 42);
	ft_printf("ft_printf: [%.5x]\n", 42);
	printf("printf:    [%.0x]\n", 0);
	ft_printf("ft_printf: [%.0x]\n", 0);
	printf("printf:    [%10.5x]\n", 42);
	ft_printf("ft_printf: [%10.5x]\n", 42);
	printf("printf:    [%-10.5x]\n", 42);
	ft_printf("ft_printf: [%-10.5x]\n", 42);
	printf("printf:    [%#10.5x]\n", 42);
	ft_printf("ft_printf: [%#10.5x]\n", 42);
	printf("=== %%X ===\n");
	printf("printf:    [%X]\n", 0);
	ft_printf("ft_printf: [%X]\n", 0);
	printf("printf:    [%X]\n", 42);
	ft_printf("ft_printf: [%X]\n", 42);
	printf("printf:    [%X]\n", 255);
	ft_printf("ft_printf: [%X]\n", 255);
	printf("printf:    [%X]\n", UINT_MAX);
	ft_printf("ft_printf: [%X]\n", UINT_MAX);
	printf("printf:    [%#X]\n", 0);
	ft_printf("ft_printf: [%#X]\n", 0);
	printf("printf:    [%#X]\n", 42);
	ft_printf("ft_printf: [%#X]\n", 42);
	printf("printf:    [%#X]\n", 255);
	ft_printf("ft_printf: [%#X]\n", 255);
	printf("printf:    [%10X]\n", 42);
	ft_printf("ft_printf: [%10X]\n", 42);
	printf("printf:    [%-10X]\n", 42);
	ft_printf("ft_printf: [%-10X]\n", 42);
	printf("printf:    [%010X]\n", 42);
	ft_printf("ft_printf: [%010X]\n", 42);
	printf("printf:    [%#010X]\n", 42);
	ft_printf("ft_printf: [%#010X]\n", 42);
	printf("printf:    [%.5X]\n", 42);
	ft_printf("ft_printf: [%.5X]\n", 42);
	printf("printf:    [%.0X]\n", 0);
	ft_printf("ft_printf: [%.0X]\n", 0);
	printf("printf:    [%10.5X]\n", 42);
	ft_printf("ft_printf: [%10.5X]\n", 42);
	printf("printf:    [%-10.5X]\n", 42);
	ft_printf("ft_printf: [%-10.5X]\n", 42);
	printf("printf:    [%#10.5X]\n", 42);
	ft_printf("ft_printf: [%#10.5X]\n", 42);
	printf("=== %%%% ===\n");
	printf("printf:    [%%]\n");
	ft_printf("ft_printf: [%%]\n");
	printf("printf:    [%5%]\n");
	ft_printf("ft_printf: [%5%]\n");
	printf("printf:    [%-5%]\n");
	ft_printf("ft_printf: [%-5%]\n");
	printf("printf:    [%05%]\n");
	ft_printf("ft_printf: [%05%]\n");
	printf("=== mixed ===\n");
	printf("printf:    [%d %s %x]\n", 42, "hi", 255);
	ft_printf("ft_printf: [%d %s %x]\n", 42, "hi", 255);
	printf("printf:    [%+d %-10s %#X]\n", -42, "hello", 255);
	ft_printf("ft_printf: [%+d %-10s %#X]\n", -42, "hello", 255);
	printf("printf:    [%5.3d %10.5s %08x]\n", 42, "hello", 255);
	ft_printf("ft_printf: [%5.3d %10.5s %08x]\n", 42, "hello", 255);
	printf("printf:    [%*d]\n", 10, 42);
	ft_printf("ft_printf: [%*d]\n", 10, 42);
	printf("printf:    [%-*d]\n", 10, 42);
	ft_printf("ft_printf: [%-*d]\n", 10, 42);
	printf("printf:    [%*d]\n", -10, 42);
	ft_printf("ft_printf: [%*d]\n", -10, 42);
	printf("printf:    [%.*d]\n", 5, 42);
	ft_printf("ft_printf: [%.*d]\n", 5, 42);
	printf("printf:    [%*.*d]\n", 10, 5, 42);
	ft_printf("ft_printf: [%*.*d]\n", 10, 5, 42);
	printf("printf:    [%-*.*d]\n", 10, 5, 42);
	ft_printf("ft_printf: [%-*.*d]\n", 10, 5, 42);
	printf("printf:    [%*.*s]\n", 10, 3, "hello");
	ft_printf("ft_printf: [%*.*s]\n", 10, 3, "hello");
	return (0);
}
*/
