/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elim-hon <elim-hon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 08:17:17 by elim-hon          #+#    #+#             */
/*   Updated: 2026/09/21 13:01:50 by elim-hon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!needle[0])
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		j = 0;
		while ((i + j) < len && haystack[i + j] && needle[j] && haystack[i
				+ j] == needle[j])
			j++;
		if (!needle[j])
			return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}

/*
#include <stdio.h>

int	main(void)
{
	char	*haystack;

	haystack = "Foo Bar 42";
	printf("%s\n", ft_strnstr(haystack, "Bar", 8));
	printf("%p\n", ft_strnstr(haystack, "Bar", 5));
	return (0);
}
*/
