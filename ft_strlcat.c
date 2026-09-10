#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;
	size_t	dst_len;
	size_t	i;

	src_len = 0;
	dst_len = 0;
	i = 0;
	while (src[src_len])
		src_len++;
	while (dst[dst_len] && dst_len < dstsize)
		dst_len++;
	if (dstsize <= dst_len)
		return (dstsize + src_len);
	while (src[i] && dst_len + i < dstsize - 1)
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len); 
}

/*
#include <stdio.h>
int	main(void)
{
	char	src[] = "DEFGHI";
	char	dst[9] = "ABC";
	size_t	len;

	len = ft_strlcat(dst, src, 2);
	printf("%zu\n", len);
	printf("%s\n", dst);
}
*/
