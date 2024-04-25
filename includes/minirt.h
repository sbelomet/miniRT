/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 10:07:34 by lgosselk          #+#    #+#             */
/*   Updated: 2024/04/25 12:39:16 by sbelomet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <math.h>
# include <limits.h>

/* Libraries External */
# include "../minilibx/mlx.h"
# include "../libft/includes/libft.h"

/* Defines */
# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
# define VIEWPORT_HEIGHT 2.0
# define VIEWPORT_WIDTH 3.555555555
# define SAMPLE_PPIXEL 40
# define PIX_SAMPLE_SCALE 0.025
# define MAX_DEPTH 10

# define TITLE "BetterBlender"
# define MALLOC_ERR "Malloc error"
# define EXT_ERR "Invalid extension file"
# define BAD_ARGS "Bad number of arguments"
# define MLX_ERR "MLX initialisation failure"
# define IMG_ERR "Image initialisation failure"
# define FILE_ERR "Cannot open file with path: "
# define WIN_ERR "Window initialisation failure"
# define ISS_ERR "whitespace that is not a space detected"
# define OBJNAME_ERR "Invalid object name while parsing file"
# define REGEX_ERR "File contains some not allowed characters"
# define RANGE_ERR "Some number while parsing file is out of range"
# define CREATE_ERR "An error occurred when trying to create an object"
# define TWICE_ERR "Twice single object detected, only one A, C, L object"

/* Enum */

enum e_types
{
	ALIGHT,
	CAMERA,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER,
};

enum e_materials
{
	LAMBERTIAN,
	METAL,
	DIELECTRIC,
};

/* Basic units structures */

typedef struct s_vector3
{
	double	x;
	double	y;
	double	z;
}			t_vector3;

typedef struct s_color
{
	double	alpha;
	double	red;
	double	green;
	double	blue;
}			t_color;

typedef struct s_ray
{
	t_vector3	origin;
	t_vector3	dir;
}				t_ray;

typedef struct s_inter
{
	double	min;
	double	max;
}			t_inter;

typedef struct s_hit_rec
{
	t_vector3			p;
	t_vector3			normal;
	struct s_material	*mat;
	double				t;
	int					front_face;
	struct s_base		*base;
}						t_hit_rec;

typedef struct s_material
{
	int		material;
	t_color	albedo;
	double	fuzz;
	double	ref_index;
	int		(*ft_scatter)(const t_ray, const t_hit_rec, t_color *, t_ray *);
}				t_material;

/* Objects structures */

typedef struct s_alight
{
	double	ratio;
	t_color	color;
}				t_alight;

typedef struct s_camera
{
	double		focal_length;
	double		viewport_width;
	double		viewport_height;
	t_vector3	lookfrom;
	t_vector3	lookat;
	t_vector3	vup;
	t_vector3	ori;
	double		vfov;
	t_vector3	pixel00_loc;
	t_vector3	pixel_delta_u;
	t_vector3	pixel_delta_v;
}				t_camera;

typedef struct s_light
{
	t_vector3	coord;
	double		ratio;
	t_color		color;
}				t_light;

typedef struct s_sphere
{
	t_vector3	center;
	double		diam;
	double		radius;
	t_color		color;
	t_material	*mat;
}				t_sphere;

typedef struct s_plane
{
	t_vector3	coord;
	t_vector3	norm;
	t_color		color;
}				t_plane;

typedef struct s_cylin
{
	t_vector3	coord;
	t_vector3	ori;
	double		diam;
	double		height;
	t_color		color;
}				t_cylin;

/* Other structures */

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
	struct s_objects	*next;
}					t_objects;

typedef struct s_uniques
{
	t_light		*light;
	t_camera	*camera;
	t_alight	*alight;
}				t_uniques;

typedef struct s_image
{
	int		endian;
	void	*img_ptr;
	char	*img_data;
	int		size_line;
	int		bitsperpix;
}				t_image;

/* Base */

typedef struct s_base
{
	t_image			image;
	t_alloc			*alloc;
	void			*mlx_ptr;
	void			*win_ptr;
	int				exit_code;
	t_camera		camera;
	unsigned long	seed;
	t_uniques		uniques;
	t_objects		*first_object;
	t_hittable		*first_hittable;
}					t_base;

/* FUNCTIONS */

/* Cleaning */
void		on_destroy(t_base *base);
int			close_window(t_base *base);

/* Init */
void		set_base(t_base *base);
int			ft_base_init(t_base *base);
t_camera	ft_camera_init(double vfov);

/* Errors */
void		*print_error_null(char *error, char *var);
int			print_error(char *error, char *var, int return_val);
int			set_exit_code(t_base *base, int exit_code, int return_val);

/* Parsing */
int			file_parse(t_base *base, char *filepath);

/* Color */
t_color		ft_color_new(const double a, const double r,
				const double g, const double b);
int			ft_get_color_int(t_color color);
t_color		ft_color_add(t_color c1, const t_color c2);
t_color		ft_color_sub(t_color c1, const t_color c2);
t_color		ft_color_mult(t_color c, const double value);
t_color		ft_color_div(t_color c, const double value);
t_color		ft_color_mult_color(t_color c1, const t_color c2);

/* Draw */
void		ft_render(t_base *base);
void		ft_pixel_put(t_base *base, int x, int y, int color);

/* Math Utils */
double		ft_rand_double_range(t_base *base, double min, double max);
double		ft_rand_double(t_base *base);
double		ft_deg_to_rad(double deg);
double		ft_rad_to_deg(double rad);

/* Hittable Utils */
int			ft_hit_anything(t_hittable *list, const t_ray r,
				const t_inter ray_t, t_hit_rec *rec);

/* Linked List Utils */
t_hittable	*ft_hittable_new(void *object);
t_hittable	*ft_hittable_last(t_hittable *hittable);
void		ft_hittable_add(t_hittable **hittable, t_hittable *new);

/* Vector3 Utils */
t_vector3	ft_vec3_new(const double x, const double y, const double z);
void		ft_vec3_print(const t_vector3 v, const char *name);
t_vector3	ft_set_face_normal(const t_ray r, const t_vector3 outward_normal,
				t_hit_rec *rec);
int			ft_vec3_near_zero(const t_vector3 v);
t_vector3	ft_vec3_add(t_vector3 v1, const t_vector3 v2);
t_vector3	ft_vec3_sub(t_vector3 v1, const t_vector3 v2);
t_vector3	ft_vec3_mult(t_vector3 v, const float value);
t_vector3	ft_vec3_div(t_vector3 v, const float value);
t_vector3	ft_vec3_mult_vec3(t_vector3 v1, const t_vector3 v2);
double		ft_vec3_dot(const t_vector3 v1, const t_vector3 v2);
t_vector3	ft_vec3_cross(const t_vector3 v1, const t_vector3 v2);
double		ft_vec3_len(const t_vector3 v);
double		ft_vec3_len_squared(const t_vector3 v);
t_vector3	ft_vec3_unit(t_vector3 v);
t_vector3	ft_vec3_rand(t_base *base);
t_vector3	ft_vec3_rand_range(t_base *base, const double min,
				const double max);
t_vector3	ft_vec3_rand_unit_sphere(t_base *base);
t_vector3	ft_vec3_rand_unit(t_base *base);
t_vector3	ft_vec3_rand_hemis(t_base *base, const t_vector3 normal);

/* Ray Utils */
t_ray		ft_ray_new(const t_vector3 origin, const t_vector3 dir);
t_vector3	ft_ray_at(const t_ray ray, const double t);
t_ray		ft_ray_calculate(t_base *base, int i, int j);
t_color		ft_ray_color(t_base *base, t_ray r, int depth, t_hittable *world);

/* Intervals Utils */
t_inter		ft_inter_new(const double min, const double max);
int			ft_inter_contains(const t_inter inter, const double x);
int			ft_inter_surrounds(const t_inter inter, const double x);
double		ft_inter_clamp(const t_inter inter, const double x);

/* Material Utils */
t_material	*ft_mat_new(int type, t_color albedo, int (*ft_scatter)
				(const t_ray, const t_hit_rec, t_color *, t_ray *));

/* Scatter Functions */
int			ft_lamb_scatter(const t_ray r_in, const t_hit_rec rec,
				t_color *attenuation, t_ray *scattered);
int			ft_metal_scatter(const t_ray r_in, const t_hit_rec rec,
				t_color *attenuation, t_ray *scattered);
int	ft_dielectric_scatter(const t_ray r_in, const t_hit_rec rec,
				t_color *attenuation, t_ray *scattered);

#endif