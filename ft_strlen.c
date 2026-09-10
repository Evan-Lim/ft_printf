#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

/*
#include <stdio.h>
int	main(void)
{
	char	*str = "Hello World!";
	printf("%zu\n", ft_strlen(str));
	return (0);
}
*/
