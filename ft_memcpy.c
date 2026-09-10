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
