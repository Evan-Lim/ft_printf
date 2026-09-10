#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	i = 0;
	if (!dst && !src)
		return (NULL);
	if (dst > src)
	{
		while (i < len)
			i++;
		while (i > 0)
		{
			i--;
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		}
	}
	else
	{
		while (i < len)
		{
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
			i++;
		}	
	}
	return (dst);
}

/*
#include <stdio.h>
int	main(void)
{
	char	str[] = "123456789";
	int	i;

	ft_memmove(str + 2, str, 5);
	i = 0;
	while (i < 9)
		printf("%c\n", str[i++]);
	return (0);
}
*/
