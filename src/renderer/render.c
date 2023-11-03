/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 22:33:12 by simao             #+#    #+#             */
/*   Updated: 2023/11/03 13:39:16 by simao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/**
 * @brief Puts a pixel in the canvas considering a new coordinate system.
 * @param x The x coordinate from the canvas.
 * @param y The y coordinate from the canvas.
 * @param color The color of the pixel.
 * 
 * @note To put pixel by pixel, instead of writing to image first, 
 * replace the last two lines with:
 * ```
 * mlx_pixel_put(mlibx()->mlx, mlibx()->win, new_x, new_y, hex_color);
 * ```
 * @note Also comment the line:
 * ```
 * mlx_put_image_to_window(mlibx()->mlx, mlibx()->win, mlibx()->img, 0, 0);
 * ```
 * in the render() function
 */
void	put_pixel(int x, int y, t_Color color)
{
	int		new_x;
	int		new_y;
	int		hex_color;
	char	*dst;

	new_x = (canvas()->width / 2) + x;
	new_y = (canvas()->height / 2) - y;
	hex_color = rgb_to_hex(color);
	dst = mlibx()->addr + \
	(new_y * mlibx()->line_len + new_x * (mlibx()->bpp / 8));
	*(unsigned int *)dst = hex_color;
}

/**
 * @brief Renders the scene, iterating through each pixel in the canvas.
*/
void	render(void)
{
	t_Color		color;
	int			x;
	int			y;
	t_Vector	d;
	t_RotMatrix	rotation_matrix;

	rotation_matrix = rotate_camera();
	x = ((canvas()->width / 2) * -1);
	y = (canvas()->height / 2);
	while (--y >= (canvas()->height / 2) * -1)
	{
		while (++x <= (canvas()->width / 2))
		{
			d = mult_mtrx_vector(&rotation_matrix, canvas_to_viewport(x, y));
			color = trace_ray(d, 1, INT_MAX);
			put_pixel(x, y, color);
		}
		x = ((canvas()->width / 2) * -1);
	}
	mlx_put_image_to_window(mlibx()->mlx, mlibx()->win, mlibx()->img, 0, 0);
	mlx_put_image_to_window(mlibx()->mlx, \
	mlibx()->win, mlibx()->menu_img, 0, 0);
}
