#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
		((unsigned char *)b)[i++] = (unsigned char)c;
	return (b);
}

/*
#include <stdio.h>
int	main(void)
{
	char	str[10] = "abcdefghi";
	int	i;

	i = 0;
	ft_memset(str, 'A', 5);
	while (i < 9)
		printf("%c\n", str[i++]);
	return (0);
}
*/
