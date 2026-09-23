/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elim-hon <elim-hon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 08:14:39 by elim-hon          #+#    #+#             */
/*   Updated: 2026/09/21 11:06:59 by elim-hon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

unsigned int	ft_lstsize(t_list *lst)
{
	unsigned int	count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

/*
#include <stdio.h>
int	main(void)
{
	t_list	*head;

	head = NULL;
	t_list	*node1 = ft_lstnew("Three");
	t_list	*node2 = ft_lstnew("Two");
	t_list	*node3 = ft_lstnew("One");
	ft_lstadd_front(&head, node1);
	ft_lstadd_front(&head, node2);
	ft_lstadd_front(&head, node3);
	printf("%d\n", ft_lstsize(head));
	return (0);
}
*/
