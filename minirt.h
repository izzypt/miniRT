/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 20:54:28 by simao             #+#    #+#             */
/*   Updated: 2023/09/16 13:12:20 by simao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libs/get_next_line/get_next_line.h"
# include "libs/mlx_linux/mlx.h"
# include "libs/printf/ft_printf.h"
# include <math.h>

typedef struct t_camera
{
	int	x;
	int	y;
	int	z;
}	t_Camera;

typedef struct t_vector
{
	float	x;
	float	y;
	float	z;
}	t_Vector;

typedef struct t_viewport
{
	int		wdth;
	int		hght;
	int		z;
	int		dst;
	float	aspect_ratio;
}	t_Viewport;

typedef struct t_canvas
{
	int	width;
	int	height;
}	t_Canvas;

typedef struct t_renderer
{
	int	width;
	int	height;
}	t_Renderer;

typedef struct t_sphere
{
	int	radius;
	int	center_x;
	int	center_y;
	int	center_z;
	int	color;
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

float		vector_magnitude(t_Vector vector1);
float		dot_product(t_Vector vector1, t_Vector vector2);
t_Vector	vector_normalize(t_Vector vector1);

#endif