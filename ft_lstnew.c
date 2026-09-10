#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

/*
#include <stdio.h>
int	main(void)
{
	char	*data = "Hello World!";
	t_list	*node;

	node = ft_lstnew(data);
	if (!node)
	{
		printf("Allocation failed.\n");
		return (1);
	}
	printf("Node content: %s\n", (char *)node->content);
	printf("Node next: %p\n", (void *)node->next);
	free(node);
	return (0);
}
*/
