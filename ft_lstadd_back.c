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
*/

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

/*
#include <stdio.h>
int	main(void)
{
	t_list	*head;
	t_list	*curr;
	t_list	*temp;

	head = NULL;
	ft_lstadd_back(&head, ft_lstnew("First"));
	ft_lstadd_back(&head, ft_lstnew("Second"));
	ft_lstadd_back(&head, ft_lstnew("Third"));
	curr = head;
	while (curr)
	{
		printf("%s\n", (char *)curr->content);
		curr = curr->next;
	}
	while (head)
	{
		temp = head->next;
		free(head);
		head = temp;
	}
	return (0);
}
*/
