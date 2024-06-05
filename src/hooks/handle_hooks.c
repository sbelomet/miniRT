/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 12:50:48 by lgosselk          #+#    #+#             */
/*   Updated: 2024/06/04 14:00:52 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	add_to_sphere(t_sphere *sphere, int type)
{
	printf("Modifying diameter of sphere\n");
	if (type == PLUS_KEY)
		sphere->diam = sphere->diam + 0.5;
	else
		sphere->diam = sphere->diam - 0.5;
	sphere->radius = sphere->diam / 2;
	printf("new diameter of sphere: %lf\n", sphere->diam);
	return (true);
}

bool	add_to_cylinder(t_cylin *cylinder, int type, int mode)
{
	printf("Modifying attributes of cylinder\n");
	if (type == PLUS_KEY)
	{
		if (mode == HEIGHT)
			cylinder->height = cylinder->height + 0.5;
		else if (mode == WIDTH)
		{
			cylinder->diam = cylinder->diam + 0.5;
			cylinder->radius = cylinder->diam / 2;
		}
	}
	else
	{
		if (mode == HEIGHT)
			cylinder->height = cylinder->height - 0.5;
		else if (mode == WIDTH)
		{
			cylinder->diam = cylinder->diam - 0.5;
			cylinder->radius = cylinder->diam / 2;
		}
	}
	return (true);
}

bool	modify_value(t_base *base, int type)
{
	t_objects	*objs;
	bool		modified;

	if (base->select.id == -1)
		return false;
	modified = false;
	objs = base->first_object;
	while (objs)
	{
		if (objs->id == base->select.id)
		{
			if (objs->type == SPHERE)
				modified = add_to_sphere((t_sphere *)objs->object, type);
			if (objs->type == CYLINDER)
				modified = add_to_cylinder((t_cylin *)objs->object, type,
					base->select.cylin_cone_modes);
			if (modified)
			{
				base->select.modified = true;
				return (true);
			}
		}
		objs = objs->next;
	}
	return (false);
}

void	switching_cylin_mode(t_base *base)
{
	if (base->select.type == CYLINDER)
	{
		if (base->select.cylin_cone_modes == HEIGHT)
		{
			base->select.cylin_cone_modes = WIDTH;
			printf("cylinder mode modification switched to width\n");
		}
		else
		{
			base->select.cylin_cone_modes = HEIGHT;
			printf("cylinder mode modification switched to height\n");
		}
	}
	printf("This type of object cannot change their mode\n");
}

void	reset_select(t_base *base)
{
	base->select.id = -1;
	base->select.type = -1;
	base->select.modified = false;
	base->select.cylin_cone_modes = -1;
	base->select.in_translation = false;
}

/*t_matrix	ft_create_matrix(void)
{
	int			i;
	int			j;
	t_matrix	matrix;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			matrix.m[i][j] = 0;
			if (i == j)
				matrix.m[i][j] = 1;
		}
	}
	return (matrix);
}

t_matrix	ft_mult_matrix(t_matrix a, t_matrix b)
{
	int			i;
	int			j;
	int			k;
	t_matrix	matrix;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			matrix.m[i][j] = 0;
			k = -1;
			while (++k < 4)
				matrix.m[i][j] += a.m[i][k] * b.m[k][j];
		}
	}
	return (matrix);
}

t_matrix	ft_reverse_x(double angle)
{
	t_matrix	matrix;

	matrix = ft_create_matrix();
	matrix.m[1][1] = cos(angle);
	matrix.m[1][2] = sin(angle);
	matrix.m[2][1] = -sin(angle);
	matrix.m[2][2] = cos(angle);
	return (matrix);
}

t_matrix	ft_reverse_y(double angle)
{
	t_matrix	matrix;

	matrix = ft_create_matrix();
	matrix.m[0][0] = cos(angle);
	matrix.m[0][2] = -sin(angle);
	matrix.m[2][0] = sin(angle);
	matrix.m[2][2] = cos(angle);
	return (matrix);
}

t_matrix	ft_reverse_z(double angle)
{
	t_matrix	matrix;

	matrix = ft_create_matrix();
	matrix.m[0][0] = cos(angle);
	matrix.m[0][1] = sin(angle);
	matrix.m[1][0] = -sin(angle);
	matrix.m[1][1] = cos(angle);
	return (matrix);
}

t_matrix	ft_rotate_x(double angle)
{
	t_matrix	matrix;

	matrix = ft_create_matrix();
	matrix.m[1][1] = cos(angle);
	matrix.m[1][2] = -sin(angle);
	matrix.m[2][1] = sin(angle);
	matrix.m[2][2] = cos(angle);
	return (matrix);
}

t_matrix	ft_rotate_y(double angle)
{
	t_matrix	matrix;

	matrix = ft_create_matrix();
	matrix.m[0][0] = cos(angle);
	matrix.m[0][2] = sin(angle);
	matrix.m[2][0] = -sin(angle);
	matrix.m[2][2] = cos(angle);
	return (matrix);
}

t_matrix	ft_rotate_z(double angle)
{
	t_matrix	matrix;

	matrix = ft_create_matrix();
	matrix.m[0][0] = cos(angle);
	matrix.m[0][1] = -sin(angle);
	matrix.m[1][0] = sin(angle);
	matrix.m[1][1] = cos(angle);
	return (matrix);
}

t_matrix	ft_matrix_rotate(t_vector3 normal)
{
	t_matrix	matrix;

	matrix = ft_create_matrix();
	matrix = ft_mult_matrix(ft_rotate_x(normal.x), matrix);
	matrix = ft_mult_matrix(ft_rotate_y(normal.y), matrix);
	matrix = ft_mult_matrix(ft_rotate_z(normal.z), matrix);
	return (matrix);
}

t_matrix	ft_matrix_rotate_x(int keycode)
{
	t_matrix	matrix;
	(void)keycode;
	matrix = ft_create_matrix();
	matrix = ft_mult_matrix(ft_rotate_x(0.5), matrix);
	return (matrix);
}

t_matrix	ft_matrix_rotate_y(int keycode)
{
	t_matrix	matrix;

	matrix = ft_create_matrix();
    if (keycode == 13)
		matrix = ft_mult_matrix(ft_rotate_y(0.5), matrix);
	else
		matrix = ft_mult_matrix(ft_reverse_y(0.5), matrix);
	return (matrix);
}

t_vector3	ft_matrix_to_vector3(t_matrix m, t_vector3 v)
{
	t_vector3	vec;

	vec.x = m.m[0][0] * v.x + m.m[1][0] * v.y + m.m[2][0] * v.z + m.m[3][0];
	vec.y = m.m[0][1] * v.x + m.m[1][1] * v.y + m.m[2][1] * v.z + m.m[3][1];
	vec.z = m.m[0][2] * v.x + m.m[1][2] * v.y + m.m[2][2] * v.z + m.m[3][2];
	//vec.w = m.m[0][3] * v.x + m.m[1][3] * v.y + m.m[2][3] * v.z + m.m[3][3];
	return (vec);
}

bool	ft_rotation_plane(t_plane *plane, int keycode)
{		
	t_matrix	res_matrix;

	if (keycode == 0 || keycode == 2 || keycode == 1 || keycode == 13)
	{
		if (keycode == 0 || keycode == 2)
			res_matrix = ft_matrix_rotate_x(keycode);
		if (keycode == 1 || keycode == 13)
			res_matrix = ft_matrix_rotate_y(keycode);
		plane->norm = ft_matrix_to_vector3(res_matrix, plane->norm);
		return (true);
	}
	return (false);
}

void	ft_rotate(t_base *base, int keycode)
{
	t_objects	*objs;

	objs = base->first_object;
	while (objs)
	{
		if (objs->id == base->select.id && objs->type == PLANE)
		{
			if (ft_rotation_plane((t_plane *)objs->object, keycode))
				base->select.modified = true;
		}
		//if (objs->id == base->select.id && objs->type == CYLINDER)
		//{
		//	if (ft_rotation_cylinder((t_cylin *)objs->object, keycode))
		//		base->select.modified = true;
		//}
		objs = objs->next;
	}
}

t_matrix	ft_translate(double x, double y)
{
	t_matrix	matrix;

	matrix = ft_create_matrix();
	matrix.m[3][0] = x;
	matrix.m[3][1] = y;
	//matrix.m[3][3] = 0; w at 0 for translation?
	return (matrix);
}

double	calc_delta(double a, double b)
{
	printf("a: %lf and b: %lf\n", a , b);
	printf("a - b: %lf and b - a: %lf\n", (a-b) , (b - a));
	if (a > b)
		return (a - b);
	else
		return (b - a);
}

bool	ft_plane_translation(t_plane *plane, int x, int y)
{
	t_matrix	res_matrix;

	res_matrix = ft_translate(calc_delta(plane->coord.x, (double)x),
		calc_delta(plane->coord.y, (double)y));
	plane->coord = ft_matrix_to_vector3(res_matrix, plane->coord);
	return (true);
}

bool	ft_sphere_translation(t_sphere *sphere, int x, int y)
{
	t_matrix	res_matrix;
	
	res_matrix = ft_translate(calc_delta(sphere->center.x, (double)x),
		calc_delta(sphere->center.y, (double)y));
	sphere->center = ft_matrix_to_vector3(res_matrix, sphere->center);
	printf("sphere center: x-> %lf, y-> %lf, z-> %lf\n", sphere->center.x, sphere->center.y, sphere->center.z);
	return (true);
}

bool	ft_cylin_translation(t_cylin *cylinder, int x, int y)
{
	t_matrix	res_matrix;

	res_matrix = ft_translate(calc_delta(cylinder->coord.x, (double)x),
		calc_delta(cylinder->coord.y, (double)y));
	cylinder->coord = ft_matrix_to_vector3(res_matrix, cylinder->coord);
	return (true);
}

void	ft_translation(t_base *base, int x, int y)
{
	t_objects	*objs;

	objs = base->first_object;
	while (objs)
	{
		if (objs->id == base->select.id)
		{
			if (objs->type == PLANE &&
				ft_plane_translation((t_plane *)objs->object, x, y))
				base->select.modified = true;
			if (objs->type == SPHERE &&
				ft_sphere_translation((t_sphere *)objs->object, x, y))
				base->select.modified = true;
			if (objs->type == CYLINDER &&
				ft_cylin_translation((t_cylin *)objs->object, x, y))
				base->select.modified = true;
		}
		objs = objs->next;
	}
}*/

int	key_hook(int keycode, t_base *base)
{
	if (keycode == ESC_KEY)
		close_window(base);
	if (keycode == DESELECT_KEY)
	{
		reset_select(base);
		printf("Deselected object, camera or light\n");
	}
	if (keycode == PLUS_KEY && base->select.id != -1)
		{}//modify_value(base, PLUS_KEY);
	if (keycode == MINUS_KEY && base->select.id != -1)
		{}//modify_value(base, MINUS_KEY);
	if (keycode == A_KEY || keycode == D_KEY
		|| keycode == S_KEY || keycode == W_KEY)
		{}//ft_rotate(base, keycode);
	if (keycode == TAB_KEY && base->select.id != -1)
		{}//switching_cylin_cone_mode(base);
	if (keycode == CONTROL_LEFT || keycode == CONTROL_RIGHT)
	{
		if (base->select.id == -1)
			printf("Before, you must select an object\n");
		else
		{
			if (base->select.in_translation)
				printf("Translation mode disable\n");
			else
				printf("Translation mode enable\n");
			base->select.in_translation = !base->select.in_translation;
		}
	}
	if (keycode == CAMERA_SELECT)
	{
		if (base->select.type == CAMERA)
			printf("Camera is already selected\n");
		else
		{
			reset_select(base);
			printf("Camera selected\n");
			base->select.type = CAMERA;
			base->select.id = -2;
		}
	}
	if (keycode == LIGHT_SELECT)
	{
		if (base->select.type == LIGHT)
		{
			if (base->select.id < base->num_of_lights
				&& base->num_of_lights > 1)
			{
				base->select.id = base->select.id + 1;
				printf("light with id: %d selected\n", base->select.id);
			}
			else if (base->select.id == base->num_of_lights
				&& base->num_of_lights > 1)
			{
				printf("light with id: 1 selected\n");
				base->select.id = 1;
			}
			else
				printf("Only one light available\n");
		}
		else if (base->num_of_lights != 0)
		{
			reset_select(base);
			printf("light with id: 1 selected\n");
			base->select.id = 1;
			base->select.type = LIGHT;
		}
		else
			printf("No lights in this scene\n");
	}
	if ((keycode == RENDER_KEY && base->select.modified))
	{
		printf("Rendering new scene\n");
		//ft_render(base);
		base->select.modified = false;
	}
	printf("keycode: %d\n", keycode);
	return (1);
}

void	ft_setup_selected(t_base *base)
{
	if (base->select.type == SPHERE)
		printf("Sphere selected\n");
	if (base->select.type == PLANE)
		printf("Plane selected\n");
	if (base->select.type == CYLINDER || base->select.type == CONE)
	{
		if (base->select.type == CYLINDER)
			printf("Cylinder selected, mode Height selected by default\n");
		else
			printf("Cone selected, mode Height selected by default\n");
		base->select.cylin_cone_modes = HEIGHT;
	}
}

bool select_object(t_base *base, int x, int y)
{
	t_ray		ray;
	t_hit_rec	rec;

	ft_generate_ray(*base->camera, x, y, &ray);
	if (!ft_anything_hit(base->first_object, ray, &rec))
		return (false);
	base->select.id = rec.object->id;
	base->select.type = rec.object->type;
	ft_setup_selected(base);
	return (true);
}

int	button_hook(int buttoncode, int x, int y, t_base *base)
{
	printf("buttoncode: %d\n", buttoncode);
	printf("pos: x:%d and y:%d\n", x, y);
	if (!base->select.in_translation && buttoncode == 1
	&& (x >= 0 && x <= WIN_WIDTH) && (y >= 0 && y <= WIN_HEIGHT))
	{
		if (select_object(base, x, y))
			printf("Object finded with id-> %d\n", base->select.id);
		else
			reset_select(base);
	}
	else if (base->select.in_translation && (x >= 0 && x <= WIN_WIDTH)
		&& (y >= 0 && y <= WIN_HEIGHT))
	{
		if (buttoncode == 1) // click left
		{
			printf("In translation\n");
			//ft_translation(base, x, y);
		}
		if (buttoncode == 4) // roll up
		{
			
		}
		if (buttoncode == 5) // roll down
		{
			
		}
	}
	if (base->select.modified && base->select.in_translation && buttoncode == 1)
	{
		printf("Rendering new scene\n");
		//ft_render(base);
		base->select.modified = false;
	}
	return (1);
}

void	ft_hooks(t_base *base)
{
	mlx_hook(base->win_ptr, 2, (1L << 0), key_hook, base);
	mlx_hook(base->win_ptr, 4, (1L << 2), button_hook, base);
	mlx_hook(base->win_ptr, 17, (1L << 17), close_window, base);
	mlx_loop(base->mlx_ptr);
}