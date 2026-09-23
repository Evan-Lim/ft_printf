/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elim-hon <elim-hon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 08:15:00 by elim-hon          #+#    #+#             */
/*   Updated: 2026/09/21 08:15:02 by elim-hon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dst && !src)
		return (NULL);
	while (i < n)
	{
		((unsigned char *)dst)[i] = ((const unsigned char *)src)[i];
		i++;
	}
	return (dst);
}

/*
#include <stdio.h>
int	main(void)
{
	char	src[6] = "abcde";
	char	dst[6] = "12345";
	int	i;

	i = 0;
	ft_memcpy(dst, src, 3);
	while (i < 5)
		printf("%c\n", dst[i++]);
	return (0);
}
*/
