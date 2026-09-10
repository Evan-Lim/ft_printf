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

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		last = ft_lstlast(*lst);
		last->next = new;
	}
}

#include <stdio.h>
void	print_content(void *content)
{
	printf("%s\n", (char *)content);
}
*/

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}

/*
int	main(void)
{
	t_list	*head;
	t_list	*tmp;

	head = NULL;
	ft_lstadd_back(&head, ft_lstnew("Node 1"));
	ft_lstadd_back(&head, ft_lstnew("Node 2"));
	ft_lstadd_back(&head, ft_lstnew("Node 3"));
	printf("Iterating through list:\n");
	ft_lstiter(head, print_content);
	while (head)
	{
		tmp = head->next;
		free(head);
		head = tmp;
	}
	return (0);
}
*/
