/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hittables_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 12:34:34 by sbelomet          #+#    #+#             */
/*   Updated: 2024/04/25 15:25:18 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hittable	*ft_hittable_new(void *object)
{
	t_hittable	*new;

	new = (t_hittable *)malloc(sizeof(t_hittable));
	if (!new)
		return (NULL);
	new->object = object;
	new->next = NULL;
	return (new);
}

t_hittable	*ft_hittable_last(t_hittable *hittable)
{
	t_hittable	*last;

	last = hittable;
	if (!last)
		return (NULL);
	while (last->next)
		last = last->next;
	return (last);
}

void	ft_hittable_add(t_hittable **hittable, t_hittable *new)
{
	t_hittable	*last;

	if (!*hittable)
	{
		*hittable = new;
		return ;
	}
	last = ft_hittable_last(*hittable);
	last->next = new;
}
