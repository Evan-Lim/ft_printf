#include "libft.h"

/*
void	map_func(unsigned int i, char *c)
{
	if (i % 2 == 0 && *c >= 'a' && *c <= 'z')
		*c = *c - 32;
}
*/

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;
	
	if (!s || !f)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}

/*
#include <stdio.h>
int	main(void)
{
	char	str[] = "hello world";

	ft_striteri(str, map_func);
	printf("%s\n", str);
	return (0);
}
*/
