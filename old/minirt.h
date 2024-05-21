/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelomet <sbelomet@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 10:07:34 by lgosselk          #+#    #+#             */
/*   Updated: 2024/05/21 15:29:49 by sbelomet         ###   ########.fr       */
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

/* Utils macros */
# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
# define SAMPLE_PPIXEL 40
# define EPSILON 1e-6
# define PIX_SAMPLE_SCALE 0.025
# define MAX_DEPTH 10

/* Key mapping macros */
# define TAB_KEY 48
# define ESC_KEY 53
# define PLUS_KEY 69
# define MINUS_KEY 78
# define RENDER_KEY 76
# define DE_SELECT_KEY 36

/* Messages macros */
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
# define ARGS_ERR "Bad number of arguments while parsing an object"
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

enum e_type_add
{
	HEIGHT,
	WIDTH,
};

enum e_materials
{
	LAMBERTIAN,
	METAL,
	DIELECTRIC,
	EMMISSIVE,
};

/* Basic units structures */

typedef struct s_vector3
{
	double	x;
	double	y;
	double	z;
	double	w;
}			t_vector3;

typedef struct s_vector4
{
	double	x;
	double	y;
	double	z;
	double	w;
}			t_vector4;

typedef struct s_color
{
	double	alpha;
	double	red;
	double	green;
	double	blue;
}			t_color;

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
}						t_hit_rec;

typedef struct s_material
{
	int		material;
	t_color	albedo;
	double	fuzz;
	double	ref_index;
	int		(*ft_scatter)(const t_ray, const t_hit_rec, t_color *, t_ray *);
}				t_material;

typedef struct s_aabb
{
	t_inter	x;
	t_inter	y;
	t_inter	z;
}			t_aabb;

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
	t_vector3		coord;
	double			ratio;
	t_color			color;
	struct s_light	*next;
}					t_light;

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
	t_material	*mat;
}				t_plane;

typedef struct s_cylin
{
	t_vector3	coord;
	t_vector3	ori;
	double		diam;
	double		radius;
	double		height;
	t_vector3	min;
	t_vector3	max;
	t_color		color;
	t_material	*mat;
}				t_cylin;

/* Other structures */

typedef	struct s_selected
{
	int		id;
	int		type;
	int		type_add; // HEIGHT OR WIDTH, ONLY FOR CYLINDER
	bool	modified;
	bool    translation;
}				t_selected;

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
	int					(*ft_hit)(const void *, const t_ray,
			const t_inter, t_hit_rec *);
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
	t_camera		*camera;
	t_alight		*alight;
	t_light			*light;
	unsigned long	seed;
	t_objects		*first_object;
	t_hittable		*first_hittable;
	t_selected		select;
}					t_base;

/* Alternative structures --------------- */

typedef struct s_hit
{
	double				t;
	int                 id;
	double				t_min;
	t_vector3			point;
	t_color             color;
	t_vector3			normal;
}						t_hit;

typedef struct s_qua_sol
{
	double		t1;
	double		t2;
	double		delta;
}				t_qua_sol;

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

typedef struct s_matrix
{
	double	m[4][4];
}			t_matrix;

typedef struct s_gtform
{
	t_matrix	fwdtfm;
	t_matrix	bcktfm;
}				t_gtform;

void    ft_render2(t_base *base);

/* ------------------------------------- */

/* FUNCTIONS */

/***   UTILS   ***/

/* Parsing utils */
t_color		parse_color(char *arg);
t_vector3	parse_vector(char *arg);
bool		out_range_color(t_color color);
bool		out_range_norm(t_vector3 vector);
bool		out_range(double min, double max, double value);

/* Parsing utils 2 */
bool		line_regex(char *line);
int			extract_type(char *arg);
bool		only_numbers(char *arg);
bool		right_args(char **args, int type);
t_objects	*get_last_object(t_objects *list);

/* Cleaning */
void		on_destroy(t_base *base);
int			close_window(t_base *base);

/* Hittable utils */
t_hittable	*ft_hittable_new(void *object);
t_hittable	*ft_hittable_last(t_hittable *hittable);
void		ft_hittable_add(t_hittable **hittable, t_hittable *new);

/* ---------------- */

/* Init */
void		set_base(t_base *base);
int			ft_base_init(t_base *base);
void		ft_camera_init(t_base *base);

/* Errors */
void		*print_error_null(char *error, char *var);
int			print_error(char *error, char *var, int return_val);
int			set_exit_code(t_base *base, int exit_code, int return_val);

/***   PARSING  ***/

/* Parsing file */
int			file_parse(t_base *base, char *filepath);

/* Creating objects */
t_plane		*create_plane(char **args);
t_sphere	*create_sphere(char **args);
t_cylin		*create_cylinder(char **args);

/* Creating uniques */
t_light		*create_light(char **args);
t_camera	*create_camera(char **args);
t_alight	*create_amblight(char **args);

/* Defaults */
bool		default_uniques(t_base *base);

/* ---------------- */

/***   HOOKS  ***/
void		ft_hooks(t_base *base);
bool		select_object(t_base *base, int x, int y);

/* ---------------- */

/* Color */
t_color		ft_color_new(const double a, const double r,
				const double g, const double b);
int			ft_get_color_int(t_color color);
t_color		ft_color_byte_to_per(const t_color color);
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
void		ft_swap(double *a, double *b);

/* Hittable Utils */
void		ft_set_hit_func(t_objects *new_object, int type);
int			ft_hit_anything(t_objects *list, const t_ray r,
				const t_inter ray_t, t_hit_rec *rec);
int			ft_hit_sphere(const void *sphere_obj, const t_ray r,
				const t_inter ray_t, t_hit_rec *rec);
int			ft_hit_plane(const void *plane_obj, const t_ray r,
				const t_inter ray_t, t_hit_rec *rec);
int			ft_hit_cylinder(const void *cylinder_obj, const t_ray r,
				const t_inter ray_t, t_hit_rec *rec);

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
int			ft_vec3_grtr(const t_vector3 v1, const t_vector3 v2);
int			ft_vec3_lssr(const t_vector3 v1, const t_vector3 v2);

/* Vector4 Utils */
t_vector4	ft_vec4_new(const double x, const double y, const double z,
			const double w);
void		ft_vec4_print(const t_vector4 v, const char *name);
t_vector4	ft_vec4_mult_mtrx(const t_vector4 v, const t_matrix m);

/* Matrix Utils */
t_matrix	ft_mtrx_new(void);
t_matrix	ft_mtrx_new2(const t_vector4 x, const t_vector4 y,
			const t_vector4 z, const t_vector4 w);
void		ft_mtrx_print(const t_matrix m, const char *name);
t_matrix	ft_mtrx_mult_mtrx(const t_matrix m1, const t_matrix m2);
double		ft_mtrx_det(t_matrix *m, int size);
t_matrix	ft_mtrx_inverse(const t_matrix m);

/* Geometric Transforms Utils */
t_gtform	ft_gtf_new(void);
t_gtform	ft_gtf_new2(const t_matrix fwd, const t_matrix bck);
t_gtform	ft_gtf_mult(const t_gtform g1, const t_gtform g2);
void		ft_gtf_set_transform(t_gtform *gt, const t_vector3 trans,
			const t_vector3 rot, const t_vector3 scale);
t_ray		ft_gtf_apply_ray(const t_gtform gt, const t_ray r, const int dir_flag);
t_vector3	ft_gtf_apply_vec3(const t_gtform gt, const t_vector3 v,
			const int dir_flag);

/* Ray Utils */
t_ray		ft_ray_new(const t_vector3 origin, const t_vector3 dir);
t_vector3	ft_ray_at(const t_ray ray, const double t);
t_ray		ft_ray_calculate(t_base *base, int i, int j);
t_color		ft_ray_color(t_base *base, t_ray r, int depth, t_objects *world);

/* Intervals Utils */
t_inter		ft_inter_new(const double min, const double max);
t_inter		ft_inter_new2(const t_inter a, const t_inter b);
int			ft_inter_contains(const t_inter inter, const double x);
int			ft_inter_surrounds(const t_inter inter, const double x);
double		ft_inter_clamp(const t_inter inter, const double x);
t_inter		ft_inter_expand(const t_inter inter, const double delta);

/* Material Utils */
t_material	*ft_mat_new(int type, t_color albedo, int (*ft_scatter)
				(const t_ray, const t_hit_rec, t_color *, t_ray *));
t_vector3	ft_reflect(const t_vector3 v, const t_vector3 n);
t_vector3	ft_refract(const t_vector3 uv,
				const t_vector3 n, double etai_over_etat);
t_color		ft_emmited(double u, double v, const t_vector3 p);

/* Scatter Functions */
int			ft_lamb_scatter(const t_ray r_in, const t_hit_rec rec,
				t_color *attenuation, t_ray *scattered);
int			ft_metal_scatter(const t_ray r_in, const t_hit_rec rec,
				t_color *attenuation, t_ray *scattered);
int			ft_dielectric_scatter(const t_ray r_in, const t_hit_rec rec,
				t_color *attenuation, t_ray *scattered);
int			ft_false_scatter(const t_ray r_in, const t_hit_rec rec,
				t_color *attenuation, t_ray *scattered);

/* Axis-Aligned Bounding Boxes Utils */
t_aabb		ft_aabb_new(const t_inter x, const t_inter y, const t_inter z);
t_aabb		ft_aabb_new2(const t_vector3 a, const t_vector3 b);
t_aabb		ft_aabb_new3(const t_aabb box0, const t_aabb box1);
int			ft_aabb_hit(const t_aabb aabb, const t_ray r, t_inter ray_t);

#endif