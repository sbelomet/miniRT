/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_list_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 20:01:50 by scherty           #+#    #+#             */
/*   Updated: 2024/06/14 10:56:50 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_light	*ft_light_last(t_light *light)
{
	t_light	*last;

	last = light;
	if (!last)
		return (NULL);
	while (last->next)
		last = last->next;
	return (last);
}

void	ft_light_add(t_light **light, t_light *new)
{
	t_light	*last;

	new->id = -1;
	if (!*light)
	{
		new->id = 1;
		*light = new;
		return ;
	}
	last = ft_light_last(*light);
	new->id = last->id + 1;
	last->next = new;
}
