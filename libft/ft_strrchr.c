/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elim-hon <elim-hon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 08:17:22 by elim-hon          #+#    #+#             */
/*   Updated: 2026/09/21 08:17:23 by elim-hon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	if (s[i] == (char)c)
		return ((char *)&s[i]);
	while (i > 0)
	{
		i--;
		if (s[i] == (char)c)
			return ((char *)&s[i]);
	}
	return (NULL);
}

/*
#include <stdio.h>
int	main(void)
{
	char	str[] = "42 Penang Piscine";
	char	*rchr_res = ft_strrchr(str, 'P');

	if (rchr_res)
		printf("%s\n", rchr_res);
	return (0);
}
*/
