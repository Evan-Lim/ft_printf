#include "libft.h"

void	ft_printf_init_flags(struct s_ft_printf_flags *flags)
{
	flags->alternate_form = 0;
	flags->left_justify = 0;
	flags->zero_padding = 0;
	flags->space = 0;
	flags->plus_sign = 0;
	flags->width = 0;
	flags->is_precision = 0;
	flags->precision = 0;
	flags->specifier = 0;
}

int	ft_printf_parse_flags(const char *format, int i, struct s_ft_printf_flags *flags)
{
	while (format[i] == '#' || format[i] == '-' || format[i] == '0' || format[i] == ' ' || format[i] == '+')
	{
		if (format[i] == '#')
			flags->alternate_form = 1;
		else if (format[i] == '-')
			flags->left_justify = 1;
		else if (format[i] == '0')
			flags->zero_padding = 1;
		else if (format[i] == ' ')
			flags->space = 1;
		else if (format[i] == '+')
			flags->plus_sign = 1;
		i++;
	}
	return (i);
}

int	ft_printf_parse_width(const char *format, int i, struct s_ft_printf_flags *flags)
{
	while (format[i] >= '0' && format[i] <= '9')
	{
		flags->width = (flags->width * 10) + (format[i] - '0');
		i++;
	}
	return (i);
}

int	ft_printf_parse_precision(const char *format, int i, struct s_ft_printf_flags *flags)
{
	if (format[i] == '.')
	{
		flags->is_precision = 1;
		i++;
		while (format[i] >= '0' && format[i] <= '9')
		{
			flags->precision = (flags->precision * 10) + (format[i] - '0');
			i++;
		}
	}
	return (i);
}

int	ft_printf_parse_conversion_specifier(const char *format, int i, struct s_ft_printf_flags *flags)
{
	if (format[i] == 'c' || format[i] == 's' || format[i] == 'p' || format[i] == 'd' || format[i] == 'i' || format[i] == 'u' || format[i] == 'x' || format[i] == 'X' || format[i] == '%')
	{
		flags->specifier = format[i];
		i++;
	}
	return (i);
}
