/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_funcs2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:32:06 by lgosselk          #+#    #+#             */
/*   Updated: 2024/05/30 11:35:29 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector3	reflect(t_vector3 in, t_vector3 normal)
{
    t_vector3   reflect;
    double      dot_prod;
    t_vector3   normal_dot;
    t_vector3   expression;

    dot_prod = ft_vec3_dot(in, normal);
    normal_dot = ft_vec3_mult(normal, dot_prod);
    expression = ft_vec3_mult(normal_dot, 2);
    
    reflect = ft_vec3_sub(in, expression);
	return (reflect);
}

t_color	ft_add_specular(t_light *light, t_hit_rec rec, t_exposure exp)
{
	t_color		specular;

	exp.reflectv = reflect(ft_vec3_negate(exp.lightv), rec.normal);
	exp.reflect_dot_eye = ft_vec3_dot(exp.reflectv, rec.eyev);
	if (exp.reflect_dot_eye <= 0)
		specular = ft_color_new(0, 0, 0, 0);
	else
	{
		exp.factor = pow(exp.reflect_dot_eye, rec.mat->shine);
		specular = ft_color_mult(light->intensity, rec.mat->spec * exp.factor);
	}
	return (specular);
}

bool	ft_dark_spec(t_exposure *exp, t_hit_rec rec, t_light *light)
{
	exp->lightv = ft_vec3_unit(ft_vec3_sub(light->coord,
		rec.p));
	exp->light_dot_normal = ft_vec3_dot(exp->lightv, rec.normal);
	if (exp->reflect_dot_eye < 0)
		return (true);
	return (false);
}