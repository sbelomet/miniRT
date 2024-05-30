/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:24:54 by sbelomet          #+#    #+#             */
/*   Updated: 2024/05/30 09:57:44 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_object_add(t_objects **hittable, t_objects *new)
{
	t_objects	*last;

	if (!*hittable)
	{
		*hittable = new;
		return ;
	}
	last = get_last_object(*hittable);
	new->id = last->id;
	last->next = new;
}
