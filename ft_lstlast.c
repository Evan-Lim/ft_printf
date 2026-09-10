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

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}
*/

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

/*
#include <stdio.h>
int	main(void)
{
	t_list	*head;
	t_list	*last;

	head = NULL;
	t_list	*node1 = ft_lstnew("Three");
	t_list	*node2 = ft_lstnew("Two");
	t_list	*node3 = ft_lstnew("One");
	ft_lstadd_front(&head, node1);
	ft_lstadd_front(&head, node2);
	ft_lstadd_front(&head, node3);
	last = ft_lstlast(head);
	printf("%s\n", (char *)last->content);
	free(node1);
	free(node2);
	free(node3);
	return (0);
}
*/
