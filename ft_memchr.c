#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s)[i] == (unsigned char)c)
			return ((void *)&((unsigned char *)s)[i]);
		i++;
	}
	return (NULL);
}

/*
#include <stdio.h>
int	main(void)
{
	char	str[] = "Hello World!";
	char	*res;

	res = ft_memchr(str, 'W', 12);
	if (res)
		printf("%s\n", res);
	else
		printf("NULL\n");
	return (0);
}
*/
