#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	size_t	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
		write(fd, &s[i++], 1);
	write(fd, "\n", 1);
}

/*
int	main(void)
{
	ft_putendl_fd("This is a string followed by a newline.", 1);
}
*/
