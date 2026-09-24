/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elim-hon <elim-hon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/23 11:02:26 by elim-hon          #+#    #+#             */
/*   Updated: 2026/09/24 08:39:59 by elim-hon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_ft_printf
{
	const char	*format;
	va_list		ap;
	int			count;
	int			minus;
	int			zero;
	int			hash;
	int			space;
	int			plus;
	int			width;
	int			dot;
	int			precision;
	char		spec;
}	t_ft_printf;

int		ft_printf(const char *format, ...);
void	ft_printf_init_state(t_ft_printf *p);
void	ft_printf_arg(t_ft_printf *p);
void	ft_printf_parse(t_ft_printf *p);
void	ft_printf_parse_flags(t_ft_printf *p);
void	ft_printf_parse_width(t_ft_printf *p);
void	ft_printf_parse_precision(t_ft_printf *p);
void	ft_printf_parse_spec(t_ft_printf *p);
void	ft_printf_char(t_ft_printf *p);
void	ft_printf_string(t_ft_printf *p);
void	ft_printf_pointer(t_ft_printf *p);
void	ft_printf_percent(t_ft_printf *p);
void	ft_printf_int(t_ft_printf *p);
void	ft_printf_unsigned(t_ft_printf *p);
void	ft_printf_hex(t_ft_printf *p);
void	ft_printf_number(t_ft_printf *p, unsigned long n, int negative);
void	ft_printf_number_all(t_ft_printf *p, char *s, unsigned long n,
			int negative);
void	ft_printf_sign(t_ft_printf *p, int negative);
void	ft_printf_prefix(t_ft_printf *p, unsigned long n);
int		ft_printf_extra_len(t_ft_printf *p, unsigned long n, int negative);
int		ft_printf_putchar_count(char c);
int		ft_printf_putstr_count(const char *s);
int		ft_printf_pad(int width, char c);
int		ft_printf_numlen(unsigned long n, int base);
char	*ft_printf_uitoa_base(unsigned long n, int base, int uppercase);
int		ft_printf_get_base(t_ft_printf *p);
int		ft_printf_is_upper(t_ft_printf *p);

#endif