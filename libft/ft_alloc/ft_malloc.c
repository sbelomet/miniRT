/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 09:25:24 by lgosselk          #+#    #+#             */
/*   Updated: 2024/03/14 13:47:29 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_malloc_clear(t_alloc **lst)
{
	t_alloc	*temp;
	t_alloc	*to_del;

	if (*lst)
	{
		to_del = *lst;
		while (to_del != NULL)
		{
			if (to_del->ptr)
				free(to_del->ptr);
			temp = to_del->next;
			free(to_del);
			to_del = temp;
		}
	}
}

static t_alloc	*get_last(t_alloc *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_alloc	*malloc_new(void *content)
{
	t_alloc	*node;

	node = (t_alloc *) malloc(sizeof(t_alloc));
	if (!node)
		return (NULL);
	node->next = NULL;
	node->ptr = content;
	return (node);
}

int	malloc_add(t_alloc **lst, t_alloc *new_node)
{
	t_alloc	*last;

	if (new_node == NULL || lst == NULL)
		return (0);
	if (*lst == NULL)
	{
		*lst = new_node;
		return (1);
	}
	else
	{
		last = get_last(*lst);
		last->next = new_node;
		return (1);
	}
	return (0);
}

void	*ft_malloc(int size, t_alloc **lst)
{
	void	*alloc;

	alloc = malloc(size);
	if (!alloc)
		return (NULL);
	if (!malloc_add(lst, malloc_new(alloc)))
		return (NULL);
	return (alloc);
}
