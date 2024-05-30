/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_list_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 20:01:50 by scherty           #+#    #+#             */
/*   Updated: 2024/05/30 10:02:54 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_light	*ft_light_new(t_vector3 coord, t_color	color, double intensity)
{
	t_light	*new;

	new = (t_light *)malloc(sizeof(t_light));
	if (!new)
		return (NULL);
	new->coord = coord;
	new->color = color;
	new->ratio = intensity;
	new->next = NULL;
	return (new);
}

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

	if (!*light)
	{
		*light = new;
		return ;
	}
	last = ft_light_last(*light);
	last->next = new;
}
