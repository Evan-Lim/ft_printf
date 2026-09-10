#include "libft.h"

int	ft_atoi(const char *str)
{
	size_t	i;
	int	sign;
	int	num;

	i = 0;
	sign = 1;
	num = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = (10 * num) + (str[i] - '0');
		i++;
	}
	return (sign * num);
}

/*
#include <stdio.h>
int	main(int argc, char **argv)
{
	printf("ft_atoi: %d | atoi: %d\n", ft_atoi(argv[1]), atoi(argv[1]));
	(void)argc;
	return (0);
}
*/
