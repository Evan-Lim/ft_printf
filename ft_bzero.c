#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		((unsigned char *)s)[i++] = '\0';
}

/*
#include <stdio.h>
int	main(void)
{
	int	i;
	int	arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	i = 0;
	ft_bzero(arr, 5 * sizeof(int));
	while (i < 10)
		printf("%d\n", arr[i++]);
	return (0);
}
*/
