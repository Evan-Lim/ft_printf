#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s1)[i] != ((unsigned char *)s2)[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}

/*
#include <stdio.h>
int	main(void)
{
	char	s1[] = "Hello World";
	char	s2[] = "Hello world";

	printf("%d\n", ft_memcmp(s1, s2, 11));
	return (0);
}
*/
