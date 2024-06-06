/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 12:50:48 by lgosselk          #+#    #+#             */
/*   Updated: 2024/06/05 15:49:34 by lgosselk         ###   ########.fr       */
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

/*bool	ft_rotable_normal(t_vector3 normal)
{
	if (normal.x == 0 && normal.y == 0 && (normal.z == 1 || normal.z == -1))
	{
		printf("No rotation\n");
		return (false);
	}
	return (true);
}*/

t_matrix	mtrx_rotation_x(double rad)
{
	t_matrix	table;

	table = ft_mtrx_new();
	table.m[1][1] = cos(rad);
	table.m[1][2] = -sin(rad);
	table.m[2][1] = sin(rad);
	table.m[2][2] = cos(rad);
	return (table);
}

t_matrix	mtrx_rotation_y(double rad)
{
	t_matrix	table;

	table = ft_mtrx_new();
	table.m[0][0] = cos(rad);
	table.m[0][2] = sin(rad);
	table.m[2][0] = -sin(rad);
	table.m[2][2] = cos(rad);
	return (table);
}

t_matrix	mtrx_rotation_z(double rad)
{
	t_matrix	table;

	table = ft_mtrx_new();
	table.m[0][0] = cos(rad);
	table.m[0][1] = -sin(rad);
	table.m[1][0] = sin(rad);
	table.m[1][1] = cos(rad);
	return (table);
}

t_matrix	mtrx_translate(t_vector3 coord)
{
	t_matrix	table;

	table = ft_mtrx_new();
	table.m[0][3] = coord.x;
	table.m[1][3] = coord.y;
	table.m[2][3] = coord.z;
	return (table);
}

t_matrix	mtrx_scaling(t_vector3 scale)
{
	t_matrix	table;

	table = ft_mtrx_new();
	table.m[0][0] = scale.x;
	table.m[1][1] = scale.y;
	table.m[2][2] = scale.z;
	return (table);
}

bool	ft_rotable_keys(int	keycode)
{
	if (keycode == A_KEY || keycode == D_KEY || keycode == S_KEY
		|| keycode == W_KEY || keycode == Z_KEY || keycode == X_KEY)
		return (true);
	return (false);
}

bool	ft_rotation_plane(t_plane *plane, int keycode)
{
	t_matrix	matrix;

	if (ft_rotable_keys(keycode))
	{
		if (keycode == Z_KEY || keycode == X_KEY)
			matrix = rotation_z(ft_deg_to_rad(5));
		else if (keycode == S_KEY || keycode == W_KEY)
			matrix = rotation_z(ft_deg_to_rad(5));
		else if (keycode == A_KEY || keycode == D_KEY)
			matrix = rotation_z(ft_deg_to_rad(5));
		else
			return (false);
		matrix = ft_mtrx_mult_mtrx(plane->tm.fwdtfm, matrix);
		plane->tm.fwdtfm = matrix;
		plane->tm.bcktfm = ft_mtrx_inverse(plane->tm.fwdtfm);
		return (true);
	}
	return (false);
}

bool	ft_rotation_cylinder(t_cylin *cylinder, int keycode)
{
	double		angle;
	t_matrix	new_rotation;

	angle = ft_deg_to_rad(10);
	if (ft_rotable_keys(keycode))
	{
		if (keycode == Z_KEY || keycode == X_KEY)
			new_rotation = rotation_y(angle);
		else if (keycode == S_KEY || keycode == W_KEY)
			new_rotation = rotation_z(angle);
		else if (keycode == A_KEY || keycode == D_KEY)
			new_rotation = rotation_x(angle);
		else
			return (false);
		cylinder->tm.rotation = ft_mtrx_mult_mtrx(cylinder->tm.rotation,
			new_rotation);
		ft_gtf_set_transform(&cylinder->tm, cylinder->tm.translation,
			cylinder->tm.rotation, cylinder->tm.scaling);
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
			printf("PLANE\n");
			if (ft_rotation_plane((t_plane *)objs->object, keycode))
			{
				printf("MODIFIED\n");
				base->select.modified = true;
			}	
		}
		if (objs->id == base->select.id && objs->type == CYLINDER)
		{
			printf("CYLINDER\n");
			if (ft_rotation_cylinder((t_cylin *)objs->object, keycode))
			{
				printf("MODIFIED\n");
				base->select.modified = true;
			}	
		}
		/*if (objs->id == base->select.id && objs->type == CONE)
		{
			//if (ft_rotation_cylinder((t_cylin *)objs->object, keycode))
			//	base->select.modified = true;
		}
		if (base->select.id == -2 && objs->type == CAMERA)
		{
			//if (ft_rotation_cylinder((t_cylin *)objs->object, keycode))
			//	base->select.modified = true;
		}*/
		objs = objs->next;
	}
}

void	switching_cylin_cone_mode(t_base *base)
{
	if (base->select.type == CYLINDER || base->select.type == CONE)
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
	if (ft_rotable_keys(keycode) && base->select.id != -1)
		ft_rotate(base, keycode);
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
		ft_render(base);
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
	if (base->select.id == rec.object->id)
	{
		printf("Already selected\n");
		return (true);
	}
	base->select.id = rec.object->id;
	base->select.type = rec.object->type;
	ft_setup_selected(base);
	return (true);
}

int	button_hook(int buttoncode, int x, int y, t_base *base)
{
	//printf("buttoncode: %d\n", buttoncode);
	//printf("pos: x:%d and y:%d\n", x, y);
	if (!base->select.in_translation && buttoncode == 1
	&& (x >= 0 && x <= WIN_WIDTH) && (y >= 0 && y <= WIN_HEIGHT))
	{
		if (select_object(base, x, y))
			printf("Object finded with id-> %d\n", base->select.id);
		else
		{
			printf("Reseting object selection\n");
			reset_select(base);
		}	
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