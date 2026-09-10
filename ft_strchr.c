#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)&s[i]);
	return (NULL);
}

/*
#include <stdio.h>
int	main(void)
{
	char	str[] = "42 Penang Piscine";
	char	*chr_res = ft_strchr(str, 'P');

	if (chr_res)
		printf("%s\n", chr_res);
	return (0);
}
*/
