/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_engine2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:15:18 by lgosselk          #+#    #+#             */
/*   Updated: 2024/05/01 11:31:04 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	ft_generate_ray(t_base *base, double x, double y)
{
	t_ray		ray;
	t_vector3	offset;
	t_vector3	pixel_sample;

	offset = ft_vec3_new(0, 0, 0);
	pixel_sample = ft_vec3_add(base->camera->pixel00_loc, ft_vec3_add(
				ft_vec3_mult(base->camera->pixel_delta_u, x + offset.x),
				ft_vec3_mult(base->camera->pixel_delta_v, y + offset.y)));
	ray.origin = base->camera->lookfrom;
	ray.dir = ft_vec3_sub(pixel_sample, ray.origin);
	return (ray);
}

double	module_v(t_vector3	v)
{
	return (sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2)));
}

t_vector3   ft_vec3_scale(t_vector3 v, double num)
{
	return (ft_vec3_new((num * v.x), (num * v.y), (num * v.z)));
}

t_vector3   ft_ray_at2(const t_ray *ray, const double time)
{
	return (ft_vec3_add(ray->origin, ft_vec3_scale(ray->dir, time)));
}

t_color	_color_clap(t_color color)
{
	t_color	tmp;

	tmp = color;
	if (tmp.red > 255)
		tmp.red = 255;
	if (tmp.green > 255)
		tmp.green = 255;
	if (tmp.blue > 255)
		tmp.blue = 255;
	return (tmp);
}

t_vector3	get_normalized(t_vector3 v)
{
	double	length;

	length = ft_vec3_len(v);
	if (length == 0)
		return (v);
	return (ft_vec3_scale(v, 1 / length));
}

/* --------------------------------------------------------------------------------------------- */

/*void	ft_sphere_setup(t_hit *rec, const t_sphere *sphere,
	const t_ray *r)
{
	rec->point = ft_ray_at2(r, rec->t);
	rec->normal = ft_vec3_sub(rec->point, sphere->center);
	rec->color = sphere->color;
}

void	ft_plane_setup(t_hit *rec, const t_plane *plane,
	const t_ray *r)
{
	rec->point = ft_ray_at2(r, rec->t);
	rec->normal = plane->norm;
	rec->color = plane->color;
}

double	determinant(t_equation *eq)
{
	double	delta;

	delta = pow(eq->b, 2) - (4 * eq->a * eq->c);
	if (delta < 0)
		return (-1);
	return (delta);
}

double	solve(t_equation *eq)
{
	double	delta;

	if (eq->a == 0.0 && eq->b != 0.0)
	{
		eq->t1 = -eq->c / eq->b;
		return (0);
	}
	else
	{
		delta = determinant(eq);
		if (delta < 0)
			return (-1);
		eq->t1 = (-eq->b - sqrt(delta)) / (2 * eq->a);
		eq->t2 = (-eq->b + sqrt(delta)) / (2 * eq->a);
		return (delta);
	}
}

bool	ft_hit_sphere2(t_sphere *sp, const t_ray *ray, t_hit *inter)
{
	t_vector3		co;
	t_equation	equation;

	equation.t1 = -1.0f;
	co = ft_vec3_sub(ray->origin, sp->center);
	equation.a = ft_vec3_dot(ray->dir, ray->dir);
	equation.b = 2.0f * ft_vec3_dot(co, ray->dir);
	equation.c = ft_vec3_dot(co, co) - pow(sp->radius, 2);
	if (solve(&equation) > 0 && \
		(equation.t1 > EPSILON || equation.t2 > EPSILON))
	{
		if (equation.t1 > EPSILON)
			inter->t = equation.t1;
		else
			inter->t = equation.t2;
		inter->color = sp->color;
		return (true);
	}
	return (false);
}

bool	ft_hit_plane2(t_plane *plane, const t_ray *ray, t_hit *inter)
{
	t_vector3		co;
	t_equation	equation;

	if (ft_vec3_dot(ray->dir, plane->norm) != 0.0)
	{
		co = ft_vec3_sub(ray->origin, plane->coord);
		equation.a = 0;
		equation.b = ft_vec3_dot(ray->dir, plane->norm);
		equation.c = ft_vec3_dot(co, plane->norm);
		solve(&equation);
		if (equation.t1 > EPSILON)
		{
			inter->t = equation.t1;
			inter->color = plane->color;
			return (true);
		}
	}
	return (false);
}*/

t_vector3	set_plane_normal(const t_ray *ray, const t_vector3 normal)
{
	int	face;

	face = ft_vec3_dot(ray->dir, normal) < 0;
	if (face)
		return (normal);
	else
		return (ft_vec3_mult(normal, -1));
}

t_qua_sol	calc_quadratic_sphere(const t_ray *ray, t_sphere *sphere)
{
	double		a;
	double		half_b;
	double		c;
	t_qua_sol	solution;

	a = ft_vec3_dot(ray->dir, ray->dir);
	half_b = ft_vec3_dot(ft_vec3_sub(ray->origin, sphere->center), ray->dir);
	c = ft_vec3_dot(ft_vec3_sub(ray->origin, sphere->center),
			ft_vec3_sub(ray->origin, sphere->center)) - sphere->radius
				* sphere->radius;
	solution.delta = pow(half_b, 2) - a * c;
	if (solution.delta < 0)
		return (solution);
	solution.t1 = (-half_b - sqrt(solution.delta)) / a;
	solution.t2 = (-half_b + sqrt(solution.delta)) / a;
	return (solution);
}

bool	ft_hit_sphere2(t_hit *rec, const t_ray *ray, t_sphere *sphere)
{
	t_qua_sol	solution;

	solution = calc_quadratic_sphere(ray, sphere);
	if (solution.delta < 0)
		return (false);
	if (solution.t1 < rec->t_min || rec->t < solution.t1)
		return (false);
	rec->t = solution.t1;
	rec->point = ft_ray_at2(ray, rec->t);
	rec->normal = get_normalized(ft_vec3_sub(rec->point, sphere->center));
	rec->normal = get_normalized(rec->normal);
	rec->color = sphere->color;
	return (true);
}

bool	ft_hit_plane2(const t_ray *ray, t_hit *rec, t_plane *plane, double max)
{
	double	temp;
	double	denom;

	plane->norm = get_normalized(plane->norm);
	denom = ft_vec3_dot(plane->norm, ray->dir);
	if (fabs(denom) < EPSILON || denom > 0)
		return (false);
	temp = ft_vec3_dot(ft_vec3_sub(plane->coord, ray->origin),
			plane->norm) / denom;
	if (temp < rec->t_min
		|| temp > max)
		return (false);
	rec->t = temp;
	rec->point = ft_ray_at2(ray, rec->t);
	//rec->normal = plane->norm;
	rec->normal = set_plane_normal(ray, plane->norm);
	rec->color = plane->color;
	return (true);
}

bool    intersects(t_objects *list, const t_ray *ray, t_hit *temp)
{
	if (list->type == SPHERE)
	{
		if (ft_hit_sphere2(temp, ray, (t_sphere *)list->object))
			return (true);
	}
	if (list->type == PLANE)
	{
		if (ft_hit_plane2(ray, temp, (t_plane *)list->object, temp->t))
			return (true);
	}
	return (false);
}

bool	ft_hit_anything2(t_objects *list, const t_ray *ray, t_hit *hit)
{
    t_hit	temp;
	bool	hit_bool;

	hit_bool = false;
	hit->t = INFINITY;
	temp.t_min = EPSILON;
	temp.t = INFINITY;
	while (list)
	{
		if (intersects(list, ray, &temp))
		{
			hit->id = list->id;
			*hit = temp;
			hit_bool = true;
		}
		list = list->next;
	}
	return (hit_bool);
}

/* --------------------------------------------------------------------------------------------- */

bool	sphere_shadow(const t_ray *ray, t_sphere *sphere)
{
	t_qua_sol	solution;

	solution = calc_quadratic_sphere(ray, sphere);
	if (solution.delta < 0)
		return (false);
	if (solution.t1 > EPSILON || solution.t2 > EPSILON)
		return (true);
	return (false);
}

bool	intersect_shadow(const t_ray *ray, t_objects *obj)
{
	if (obj->type == SPHERE)
		return (sphere_shadow(ray, (t_sphere *)obj->object));
	// cylinder
	return (false);
}

int	in_shadow(t_base *base, t_hit *hit, t_light *light)
{
	t_ray		shadow;
	t_objects	*list;
	t_vector3	light_direc;

	list = base->first_object;
	light_direc = ft_vec3_sub(light->coord, hit->point);
	shadow = (t_ray){hit->point, light_direc};
	while (list)
	{
		if (hit->id == list->id)
		{
			list = list->next;
			continue;
		}
		if (intersect_shadow(&shadow, list))
			return (true);
		list = list->next;
	}
	return (false);
}

double	vec3_cossine(t_vector3 v1, t_vector3 v2)
{
	double	dot;
	double	lengths;

	dot = ft_vec3_dot(v1, v2);
	lengths = ft_vec3_len(v1) * ft_vec3_len(v2);
	return (dot / lengths);
}

double	ft_min(double a, double b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

t_color ft_diffuse(t_hit *hit, t_light *light)
{
	t_vector3	light_dir;
	t_color	diff_color;
	double	cos_angle;
	double	diffuse_ratio;
	double	attenuation;

	light_dir = ft_vec3_sub(light->coord, hit->point);
	attenuation = ft_min(1.0, 90.0 / ft_vec3_len(light_dir));
	cos_angle = vec3_cossine(hit->normal, light_dir);
	diffuse_ratio = light->ratio * cos_angle * attenuation;
	diff_color = ft_color_mult(hit->color, diffuse_ratio);
	return (_color_clap(diff_color));
}

t_color	calculate_color(t_base *base, t_hit *hit)
{
	t_color		ret;
	ret = ft_color_mult(hit->color, base->alight->ratio);
	if (base->light && !in_shadow(base, hit, base->light))
		ret = ft_color_add(ret, ft_diffuse(hit, base->light));
	return (ret);
}

t_color	find_color(t_base *base, const t_ray *ray)
{
	t_hit		hit;
	t_color		color;

	color = ft_color_new(0, 0, 0, 0);
	if (ft_hit_anything2(base->first_object, ray, &hit))
	{
		color = calculate_color(base, &hit);
		return (color);
	}
	return (color);
}

void	ft_render2(t_base *base)
{
	int		x;
	int		y;
	t_ray	ray;
	t_color	color;

	y = 0;
    while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			ray = ft_generate_ray(base, x, y);
			color = find_color(base, &ray);
			ft_pixel_put(base, x, y, ft_get_color_int(color));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(base->mlx_ptr, base->win_ptr,
			base->image.img_ptr, 0, 0);
}

/*-----------------------------------------------------------*/

void	ft_setup_selected(t_base *base, t_objects *obj)
{
	if (obj->type == SPHERE)
		printf("Sphere selected\n");
	if (obj->type == PLANE)
		printf("Plane selected\n");
	if (obj->type == CYLINDER)
	{
		printf("Cylinder selected, mode Height selected by default\n");
		base->select.type_add = HEIGHT;
	}	
}

bool	ft_hit_select(t_base *base, t_objects *list, const t_ray *ray)
{
    double	t;
	t_hit	temp;
	bool	hit_bool;

	hit_bool = false;
	temp.t = INFINITY;
	t = INFINITY;
	while (list)
	{
		if (intersects(list, ray, &temp) && (temp.t < t))
		{
			t = temp.t;
			base->select.id = list->id;
			base->select.type = list->type;
			ft_setup_selected(base, list);
			hit_bool = true;
		}
		list = list->next;
	}
	return (hit_bool);
}

bool select_object(t_base *base, int x, int y)
{
	t_ray	ray;

	ray = ft_generate_ray(base, x, y);
	if (ft_hit_select(base, base->first_object, &ray))
		return (true);
	return (false);
}