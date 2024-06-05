/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:24:54 by sbelomet          #+#    #+#             */
/*   Updated: 2024/06/04 10:12:34 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_object_add(t_objects **hittable, t_objects *new)
{
	t_objects	*last;

	new->id = -1;
	if (!*hittable)
	{
		new->id = 1;
		*hittable = new;
		return ;
	}
	last = get_last_object(*hittable);
	new->id = last->id + 1;
	last->next = new;
}
