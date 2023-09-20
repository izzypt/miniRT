/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 20:54:28 by simao             #+#    #+#             */
/*   Updated: 2023/09/20 14:41:58 by simao            ###   ########.fr       */
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

/*************/
/* DEFINES  */
/***********/

# define PI 3.1415926
# define BLUE 0x0000FF
# define GREEN 0x00FF00
# define RED 0xFF0000
# define WHITE 0xFFFFFF 

/**************/
/* STRUCTS   */
/************/

typedef struct t_mlz
{
	void		*mlx;
	void		*win;
}	t_mlx;

typedef struct t_camera
{
	float	x;
	float	y;
	float	z;
}	t_Camera;

typedef struct t_vector
{
	float	x;
	float	y;
	float	z;
}	t_Vector;

typedef struct t_viewport
{
	float	width;
	float	height;
	float	dist;
	float	aspect_ratio;
}	t_Viewport;

typedef struct t_canvas
{
	int	width;
	int	height;
}	t_Canvas;

typedef struct t_sphere
{
	float		radius;
	int			color;
	t_Vector	coord;
}	t_Sphere;

/**************/
/* OBJECTS   */
/************/

t_Vector	*camera(void);
t_Viewport	*viewport(void);
t_Sphere	*sphere(void);
t_Canvas	*canvas(void);

/**************/
/* VECTORS   */
/************/

float		dot_product(t_Vector vector1, t_Vector vector2);
void		vector_normalize(t_Vector *vector1);
float		vector_magnitude(t_Vector vector1);
t_Vector	vector_sub(t_Vector *vector1, t_Vector *vector2);
t_Vector	vector_add(t_Vector *vector1, t_Vector *vector2);
t_Vector	vector_mult(t_Vector *vector1, int num);

/*******************/
/* INTERSECTIONS  */
/*****************/

int			intersects_sphere(t_Vector pos);
int			intersects_circle(int x, int y);

/************/
/* UTILS   */
/**********/

void		init_values(void);
void		canvas_to_viewport(int x, int y, t_Vector *ray_dir);
float		calculate_fov(void);
void		set_fov(float degrees);
void		put_pixel(int x, int y, int color, void *mlx, void *win);

#endif