/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:46:51 by lgosselk          #+#    #+#             */
/*   Updated: 2024/06/10 11:25:59 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

/* Basic structures */

typedef struct s_vector3
{
	double	x;
	double	y;
	double	z;
}			t_vector3;

typedef struct s_vector4
{
	double	x;
	double	y;
	double	z;
	double	w;
}			t_vector4;

typedef struct s_matrix
{
	double	m[4][4];
}			t_matrix;

typedef struct s_gtform
{
	t_matrix	fwdtfm;
	t_matrix	bcktfm;
	t_matrix	scaling;
	t_matrix	rotation;
	t_matrix	transpose;
	t_matrix	translation;
}				t_gtform;

typedef struct s_color
{
	double	alpha;
	double	red;
	double	green;
	double	blue;
}			t_color;

typedef struct s_image
{
	int		endian;
	void	*img_ptr;
	char	*img_data;
	int		size_line;
	int		bitsperpix;
}				t_image;

typedef struct s_ray
{
	t_vector3	p1;
	t_vector3	p2;
	t_vector3	lab;
}				t_ray;

typedef struct s_inter
{
	double	min;
	double	max;
}			t_inter;

/* Objects structures */

typedef struct s_alight
{
	double	ratio;
	t_color	color;
	t_color	intensity;
}				t_alight;

typedef struct s_camera
{
	double		horz_size;
	double		aspect;
	double		length;
	t_vector3	lookfrom;
	t_vector3	lookat;
	t_vector3	vup;
	t_vector3	alignment;
	t_vector3	proj_screen_u;
	t_vector3	proj_screen_v;
	t_vector3	proj_screen_center;
}				t_camera;

typedef struct s_light
{
	int				id;
	t_vector3		coord;
	double			ratio;
	t_color			color;
	t_color			intensity;
	struct s_light	*next;
}					t_light;

typedef struct s_sphere
{
	t_vector3			center;
	double				diam;
	double				radius;
	t_color				color;
	struct s_material	*mat;
	t_gtform			tm;
}						t_sphere;

typedef struct s_plane
{
	t_vector3			coord;
	t_vector3			norm;
	t_color				color;
	struct s_material	*mat;
	t_gtform			tm;
}						t_plane;

typedef struct s_cylin
{
	t_vector3			coord;
	t_vector3			ori;
	double				diam;
	double				radius;
	double				height;
	t_color				color;
	struct s_material	*mat;
	t_gtform			tm;
}						t_cylin;

typedef struct s_cone
{
	t_vector3			coord;
	t_vector3			ori;
	double				diam;
	double				radius;
	double				height;
	t_color				color;
	struct s_material	*mat;
	t_gtform			tm;
}						t_cone;

/* Other structures */

typedef struct s_hit_rec
{
	struct s_objects	*object;
	t_vector3			p;
	t_vector3			normal;
	struct s_material	*mat;
	double				t;
	int					front_face;
	t_color				emmited;
	t_color				color;
	double				intensity;
	struct s_base		*base;
	t_vector3			eyev;
}						t_hit_rec;

typedef struct s_aabb
{
	t_inter	x;
	t_inter	y;
	t_inter	z;
}			t_aabb;

typedef struct s_hittable
{
	void				*object;
	struct s_hittable	*next;
}						t_hittable;

typedef struct s_objects
{
	int					id;
	int					type;
	void				*object;
	int					(*ft_hit)(const void *, const t_ray, t_hit_rec *);
	struct s_objects	*next;
}					t_objects;

typedef struct s_material
{
	double	reflect;
	double	shine;
	double	spec;
	void	(*ft_comp_color)(t_objects *, t_hit_rec *,
			t_light *, t_color *);
}			t_material;

typedef struct s_exposure
{
	t_vector3	lightv;
	t_vector3	reflectv;
	double		light_dot_normal;
	double		reflect_dot_eye;
	double		factor;
}	t_exposure;

typedef struct s_selected
{
	int		id;
	int		type;
	bool	modified;
	bool	in_translation;
	int		cylin_cone_modes;
}				t_selected;

typedef struct s_equation
{
	double		a;
	double		b;
	double		c;
	double		t;
	double		t1;
	double		t2;
	double		t3;
	double		t4;
	double		min_t;
	t_vector3	oc;
}				t_equation;

typedef struct s_poi
{
	t_vector3	poi[4];
	int			tv[4];
	int			index;
}				t_poi;

/* Base */

typedef struct s_base
{
	t_image			image;
	t_alloc			*alloc;
	void			*mlx_ptr;
	void			*win_ptr;
	t_camera		*camera;
	t_alight		*alight;
	int				exit_code;
	unsigned long	seed;
	t_selected		select;
	t_objects		*first_object;
	t_light			*first_light;
	int				num_of_lights;
}					t_base;

#endif