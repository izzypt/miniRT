/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 20:54:28 by simao             #+#    #+#             */
/*   Updated: 2023/10/02 13:05:58 by simao            ###   ########.fr       */
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

/*************/
/* DEFINES  */
/***********/

# define PI 3.1415926
# define BLUE 0x0000FF
# define GREEN 0x00FF00
# define RED 0xFF0000
# define WHITE 0xFFFFFF 
# define YELLOW 0xFFFF00 

/**************/
/* STRUCTS   */
/************/

typedef struct mlx
{
	void		*mlx;
	void		*win;
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

typedef struct camera
{
	float	x;
	float	y;
	float	z;
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
}	t_Scene;

typedef struct close_intersection
{
	t_Sphere	*closest_sphere;
	float		closest_t;
}	t_Intersection;

/**************/
/* OBJECTS   */
/************/

t_Scene			*scene(void);
t_Vector		*camera(void);
t_Viewport		*viewport(void);
t_Canvas		*canvas(void);
t_mlx			*mlibx(void);

/**************/
/* VECTORS   */
/************/

float			dot_product(t_Vector vector1, t_Vector vector2);
t_Vector		vector_normalize(t_Vector *vector1);
float			vector_magnitude(t_Vector vector1);
t_Vector		vector_sub(t_Vector *vector1, t_Vector *vector2);
t_Vector		vector_add(t_Vector *vector1, t_Vector *vector2);
t_Vector		vector_mult(t_Vector *vector1, float num);
t_Vector		vector_div(t_Vector *vector1, float num);

/************/
/* PARSER  */
/**********/
int				parse_file(char **argv);
void			parse_light(char **line);
void			parse_camera(char **line);
void			parse_ambient(char **line);

/*******************/
/* INTERSECTIONS  */
/*****************/

t_Point			intersects_sphere(t_Vector O, t_Vector D, t_Sphere sphere);
t_Color			trace_ray(t_Vector pos, int t_min, int t_max);
float			calculate_light(t_Vector *P, t_Vector *N, t_Vector V, t_Sphere	*closest_sphere);
t_Intersection	closest_intersect(t_Vector *O, t_Vector *D, float t_min, float t_max);

/***********/
/* COLORS */
/**********/

int				rgb_to_hex(t_Color color);
t_Color			hex_to_rgb(int hex_color);
t_Color			color_add(t_Color *color1, t_Color *color2);
t_Color			color_mult(t_Color *color1, float num);
t_Color			color_sub(t_Color *color1, t_Color *color2);
t_Color			color_mult(t_Color *color1, float num);

/************/
/* UTILS   */
/**********/

void			init_values(void);
t_Vector		canvas_to_viewport(int x, int y);
float			calculate_fov(void);
void			set_fov(float degrees);
void			put_pixel(int x, int y, t_Color color);
void			free_matrix(char **matrix);
void			send_error(char *error);
int				ft_atoi(const char *str);

/****************/
/* REFLECTIONS */
/**************/

void			diffuse_reflection(t_Vector norm, t_Vector lvec, float *i, int j);
void			specular_reflection(t_Vector norm, t_Vector lvec, int spec, float *i, int j, t_Vector V);

#endif