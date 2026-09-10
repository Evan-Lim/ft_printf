#include "libft.h"

/*
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
*/

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}

/*
#include <stdio.h>
int	main(void)
{
	t_list	*head;
	t_list	*current;

	head = NULL;
	t_list	*node1 = ft_lstnew("World!");
	t_list	*node2 = ft_lstnew("Hello ");
	ft_lstadd_front(&head, node1);
	ft_lstadd_front(&head, node2);
	current = head;
	while (current)
	{
		printf("%s", (char *)current->content);
		current = current->next;
	}
	printf("\n");
	free(node1);
	free(node2);
	return (0);
}
*/
