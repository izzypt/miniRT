/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 20:54:28 by simao             #+#    #+#             */
/*   Updated: 2023/09/15 12:51:55 by simao            ###   ########.fr       */
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

typedef struct t_viewport
{
	int		width;
	int		height;
	float	aspect_ratio;
}	t_Viewport;

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
	int	color_r;
	int	color_g;
	int	color_b;
}	t_Sphere;

/* FUNCTIONS */
t_Camera	*camera(void);
t_Viewport	*viewport(void);
t_Sphere	*sphere(void);


#endif