/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 22:46:50 by simao             #+#    #+#             */
/*   Updated: 2023/10/07 18:57:06 by simao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/*
 - Puts the pixel on the window.
 - Changes the coordinates system:
   - (0,0) is now at the center of the screen;
   - (-960 to 960) on the x assuming 1920px.
   - (-540 to 50) on the y assuming 1080p.
*/
void	put_pixel(int x, int y, t_Color color)
{
	int	new_x;
	int	new_y;
	int	hex_color;

	new_x = (canvas()->width / 2) + x;
	new_y = (canvas()->height / 2) - y;
	hex_color = rgb_to_hex(color);
	mlx_pixel_put(mlibx()->mlx, mlibx()->win, new_x, new_y, hex_color);
}

float	AngleBetweenVectors(t_Vector vector1, t_Vector vector2)
{
	float	magnitude1;
	float	magnitude2;
	float	dot;
	float	radians;
	float	degrees;

	magnitude1 = vector_magnitude(vector1);
	magnitude2 = vector_magnitude(vector2);
	dot = dot_product(vector1, vector2);
	radians = (acos(dot / (magnitude1 * magnitude2)));

	degrees = radians * (180.0 / PI);

	return (degrees);
}

/*
 - Converts canvas coordinates into viewport coordinates.
 - Stores them in raydir.
*/
t_Vector	canvas_to_viewport(int x, int y)
{
	t_Vector	ray;
	t_Vector	orientation;

	orientation.x = 0;
	orientation.y = 0;
	orientation.z = 1;
	ray.x = x * ((float)viewport()->width / (float)canvas()->width);
	ray.y = y * ((float)viewport()->height / (float)canvas()->height);
	ray.z = viewport()->dist;
	printf("Angle between ray and orientation vector: %f\n", AngleBetweenVectors(ray, orientation));
	return (ray);
}