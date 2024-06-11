/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 15:15:10 by sbelomet          #+#    #+#             */
/*   Updated: 2024/06/10 10:57:27 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_compute_shadow(t_objects *list, t_objects *current,
	t_ray light_ray, double light_dist)
{
	t_objects	*tmp_obj;
	int			shadow_good;
	double		dist;
	t_hit_rec	light_rec;

	tmp_obj = list;
	shadow_good = false;
	while (tmp_obj)
	{
		if (tmp_obj != current)
		{
			if (tmp_obj->ft_hit(tmp_obj->object, light_ray, &light_rec))
			{
				dist = ft_vec3_len_squared(
						ft_vec3_sub(light_rec.p, light_ray.p1));
				if (dist <= light_dist)
				{
					shadow_good = true;
					break ;
				}
			}
		}
		tmp_obj = tmp_obj->next;
	}
	return (shadow_good);
}

static int	ft_return_dark(t_hit_rec *rec, t_light *l)
{
	rec->emmited = l->color;
	rec->intensity = 0.0;
	return (false);
}

int	ft_compute_light(t_objects *list, t_hit_rec *rec, t_light *l)
{
	t_vector3	light_dir;
	t_vector3	start_point;
	double		angle;
	t_ray		light_ray;
	double		light_dist;

	light_dist = ft_vec3_len_squared(ft_vec3_sub(l->coord, rec->p));
	light_dir = ft_vec3_unit(ft_vec3_sub(l->coord, rec->p));
	start_point = rec->p;
	light_ray = ft_ray_new(start_point, ft_vec3_add(start_point, light_dir));
	if (!ft_compute_shadow(list, rec->object, light_ray, light_dist))
	{
		angle = acos(ft_vec3_dot(rec->normal, light_dir));
		if (angle > 1.5708)
			return (ft_return_dark(rec, l));
		else
		{
			rec->emmited = l->color;
			rec->intensity = l->ratio * (1.0 - (angle / 1.5708))
				/ light_dist * 90;
			return (true);
		}
	}
	return (ft_return_dark(rec, l));
}

int	ft_calc_lights(t_objects *list, t_hit_rec *rec, t_light *lights)
{
	t_exposure	exp;
	t_hit_rec	tmp_rec;
	int			light_good;

	light_good = false;
	rec->emmited = ft_color_new(0, 0, 0, 0);
	tmp_rec = *rec;
	while (lights)
	{
		if (ft_compute_light(list, &tmp_rec, lights))
		{
			light_good = true;
			rec->emmited = ft_color_add(rec->emmited,
					ft_color_mult(tmp_rec.emmited, tmp_rec.intensity));
			if (ft_dark_spec(&exp, tmp_rec, lights))
				ft_return_dark(&tmp_rec, lights);
			else
				rec->emmited = ft_color_add(rec->emmited,
						ft_add_specular(lights, tmp_rec, exp));
			rec->intensity = tmp_rec.intensity;
		}
		lights = lights->next;
	}
	return (light_good);
}
