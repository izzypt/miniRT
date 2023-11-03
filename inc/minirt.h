/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 20:54:28 by simao             #+#    #+#             */
/*   Updated: 2023/11/03 12:00:42 by simao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

/**********/
/* LIBS  */
/********/

# include "libs/get_next_line/get_next_line.h"
# include "libs/mlx_linux/mlx.h"
# include "libs/printf/ft_printf.h"
# include <stdio.h>
# include <math.h>
# include <limits.h>
# include <time.h>

/*************/
/* DEFINES  */
/***********/

# define TITLE "MiniRT"
# define PI 3.1415926
# define BLUE 0x0000FF
# define RED 0xFF0000
# define GREEN 0x00FF00
# define YELLOW 0xFFFF00 
# define BLACK 0x000000 
# define WHITE 0xFFFFFF
# define ARROW_LEFT 65361
# define ARROW_RIGHT 65363
# define ARROW_UP 65362
# define ARROW_DOWN 65364
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define MENU "../scenes/menu.xpm"
# define T_MIN 1
# define T_MAX 2147483646
# define CY 934
# define PL 933
# define SP 932

/**************/
/* STRUCTS   */
/************/

typedef struct mlx
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	void		*menu_img;
	int			bpp;
	int			line_len;
	int			endian;
}	t_mlx;

typedef struct vector
{
	float	x;
	float	y;
	float	z;
}	t_Vector;

typedef struct color
{
	float	r;
	float	g;
	float	b;
}	t_Color;

typedef struct rotation_matrix
{
	float	m[3][3];
}	t_RotMatrix;

typedef struct camera
{
	t_Vector	pos;
	t_Vector	dir;
	t_Vector	initial_dir;
	float		fov;
}	t_Camera;

typedef struct viewport
{
	float	width;
	float	height;
	float	dist;
	float	aspect_ratio;
}	t_Viewport;

typedef struct canvas
{
	int	width;
	int	height;
}	t_Canvas;

typedef struct point
{
	float	t1;
	float	t2;
}	t_Point;

typedef struct sphere
{
	float		radius;
	float		spec;
	t_Color		color;
	t_Vector	center;
}	t_Sphere;

typedef struct plane
{
	t_Vector	point;
	t_Vector	normal;
	t_Color		color;
	float		spec;
}	t_Plane;

typedef struct cylinder
{
	t_Vector	pos;
	t_Vector	normal;
	t_Color		color;
	float		radius;
	float		height;
	float		spec;
}	t_Cylinder;

typedef struct light
{
	char		type;
	float		intensity;
	t_Vector	position;
	t_Vector	direction;
}	t_Light;

typedef struct scene
{
	t_Sphere	*spheres;
	t_Light		*lights;
	t_Plane		*planes;
	t_Cylinder	*cylinders;
	int			spheres_count;
	int			plane_count;
	int			cyl_count;
	int			background;
	int			max_obj_count;
}	t_Scene;

typedef struct close_intersection
{
	t_Sphere	*clst_sp;
	t_Plane		*clst_pl;
	t_Cylinder	*clst_cy;
	float		clst_t;
	int			object;
	t_Point		sp;
	t_Point		cy;
	float		pl;
}	t_Intersection;

/**************/
/* OBJECTS   */
/************/

t_Scene			*scene(void);
t_Camera		*camera(void);
t_Viewport		*viewport(void);
t_Canvas		*canvas(void);
t_mlx			*mlibx(void);

/**************/
/* VECTORS   */
/************/

float			dot_product(t_Vector vector1, t_Vector vector2);
t_Vector		vector_normalize(t_Vector *vector1);
float			vector_magnitude(t_Vector vector1);
t_Vector		vector_sub(t_Vector vector1, t_Vector vector2);
t_Vector		vector_add(t_Vector vector1, t_Vector vector2);
t_Vector		vector_mult(t_Vector vector1, float num);
t_Vector		vector_div(t_Vector *vector1, float num);
t_Vector		cross_product(t_Vector A, t_Vector B);
t_Vector		mult_mtrx_vector(t_RotMatrix *matrix, t_Vector vector);
float			angle_btwn_vectors(t_Vector vector1, t_Vector vector2);

/***********/
/* COLORS */
/**********/

int				rgb_to_hex(t_Color color);
t_Color			hex_to_rgb(int hex_color);
t_Color			color_add(t_Color color1, t_Color color2);
t_Color			color_mult(t_Color color1, float num);
t_Color			color_sub(t_Color color1, t_Color color2);
t_Color			color_mult(t_Color color1, float num);
t_Color			night_sky(void);
t_Color			blue_sky(t_Vector ray);
t_Color			background_color(t_Vector ray);
t_Color			cyl_color(t_Intersection itsct, t_Vector ray, \
				t_Vector p, t_Vector dt);
t_Color			pln_color(t_Intersection itsct, \
				t_Vector ray, t_Vector p, t_Vector dt);
t_Color			sphr_color(t_Intersection itsct, t_Vector ray, \
				t_Vector p, t_Vector dt);

/************/
/* PARSER  */
/**********/

int				parse_file(char **argv);
void			parse_light(char **line);
void			parse_camera(char **line);
void			parse_ambient(char **line);
void			parse_sphere(char **line);
void			parse_plane(char **line);
void			parse_cylinder(char **line);

/***************/
/* VALIDATORS */
/*************/

void			validate_rgb_values(int r, int g, int b);
void			validate_normal_vector(int x, int y, int z);
float			validate_fov(float fov);

/*****************/
/* INITIALIZER  */
/***************/

void			set_viewport(void);
void			set_camera(t_Vector cam_pos, t_Vector cam_dir, float fov);
void			set_canvas(int width, int height);
void			set_ambient_light(float intensity);
void			set_point_light(float intensity, t_Vector position);
void			set_mlx(void);
void			set_sphere(float diameter, t_Vector center, t_Color color);
void			set_plane(t_Vector point, t_Vector normal, t_Color color);
void			set_cylinder(t_Cylinder cylinder);

/**************/
/* RENDERER  */
/************/

void			render(void);
t_Point			intrscts_sphr(t_Vector O, t_Vector D, t_Sphere sphere);
float			intrscts_pln(t_Vector O, t_Vector D, t_Plane pln);
t_Point			intrscts_cyl(t_Vector O, t_Vector D, t_Cylinder cylinder);
t_Intersection	clst_intsct(t_Vector O, t_Vector D, float t_min, float t_max);
t_Color			trace_ray(t_Vector pos, int t_min, int t_max);
float			calc_light(t_Vector P, t_Vector N, t_Vector V, float spec);
void			diff_reflection(t_Vector norm, t_Vector lvec, float *i, int j);
void			spec_reflection(t_Vector norm, t_Vector lvec, int spec, \
				float *i, int j, t_Vector V);

/******************/
/* KEYS MANAGER  */
/****************/

int				close_window(void);
int				key_press(int keycode);

/************/
/* UTILS   */
/**********/

t_Vector		canvas_to_viewport(int x, int y);
float			calculate_fov(void);
void			set_fov(float degrees);
void			put_pixel(int x, int y, t_Color color);
void			free_matrix(char **matrix);
void			end_program(void);
void			send_error(char *error);
int				ft_atoi(const char *str);
float			ft_atof(const char *str);
char			*ft_strdup(char *s1);
t_RotMatrix		create_rot_matrix(t_Vector axis, float angle);
t_RotMatrix		rotate_camera(void);


#endif