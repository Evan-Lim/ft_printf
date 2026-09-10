#include "libft.h"

/*
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
*/

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (!dstsize)
		return (ft_strlen(src));
	while (src[i] && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

/*
#include <stdio.h>
int	main(void)
{
	char	src[] = "Hello World!";
	char	dst[13];
	size_t	i;

	i = ft_strlcpy(dst, src, 6);
	printf("%zu\n", i);
	printf("%s\n", dst);
}
*/
