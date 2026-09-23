/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elim-hon <elim-hon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/23 11:02:26 by elim-hon          #+#    #+#             */
/*   Updated: 2026/09/23 11:29:51 by elim-hon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>

typedef struct s_ft_printf_flags
{
    int minus;
    int zero;
    int dot;
    int precision;
    int width;
    int hash;
    int space;
    int plus;
} t_ft_printf_flags;