/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 22:46:50 by simao             #+#    #+#             */
/*   Updated: 2023/09/24 21:55:35 by simao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 - Puts the pixel on the window.
 - Changes the coordinates system:
   - (0,0) is now at the center of the screen;
   - (-960 to 960) on the x assuming 1920px.
   - (-540 to 50) on the y assuming 1080p.
*/
void	put_pixel(int x, int y, t_Color color, void *mlx, void *win)
{
	int	new_x;
	int	new_y;
	int	hex_color;

	new_x = (canvas()->width / 2) + x;
	new_y = (canvas()->height / 2) - y;
	hex_color = rgb_to_hex(color);
	mlx_pixel_put(mlx, win, new_x, new_y, hex_color);
}

/*
 - Converts canvas coordinates into viewport coordinates.
 - Stores them in raydir.
*/
void	canvas_to_viewport(int x, int y, t_Vector *ray)
{
	ray->x = x * ((float)viewport()->width / (float)canvas()->width);
	ray->y = y * ((float)viewport()->height / (float)canvas()->height);
	ray->z = 1;
}
