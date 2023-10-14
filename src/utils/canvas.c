/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 22:46:50 by simao             #+#    #+#             */
/*   Updated: 2023/10/14 12:50:04 by simao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/**
 * @brief Puts a pixel in the canvas considering a new coordinate system.
 * 
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
 * @brief Converts a canvas coordinate to a viewport coordinate.
 * 
 * @param x The x coordinate from the canvas.
 * @param y The y coordinate from the canvas.
 * @returns t_Vector which - ultimately - indicates 
 * the ray direction shot from the origin.
 */
t_Vector	canvas_to_viewport(int x, int y)
{
	t_Vector	ray;

	ray.x = x * ((float)viewport()->width / (float)canvas()->width);
	ray.y = y * ((float)viewport()->height / (float)canvas()->height);
	ray.z = viewport()->dist;
	return (ray);
}

/**
 * @brief Performas all the necessary operations to rotate the camera.
 * @note The operations it performs:
 * @note 1. get the angle between vectors
 * @note 2. get the cross product between vectors
 * @note 3. create the rotation matrix from those values.
 * @returns t_RotMatrix a rotation matrix based on those values.
 */
t_RotMatrix	rotate_camera(void)
{
	t_Vector	axis;
	t_Vector	cross;
	float		angle;
	t_RotMatrix	matrix;

	angle = angle_btwn_vectors(camera()->initial_dir, camera()->dir);
	cross = cross_product(camera()->initial_dir, camera()->dir);
	axis = cross;
	matrix = create_rot_matrix(axis, angle);
	return (matrix);
}

/**
 * @brief Return a color black or white, The highest probability is black.
 * @returns t_Color to paint on the canvas.
 */
t_Color	night_sky(void)
{
	static int	randomnumber;

	randomnumber = rand() % 750 + 1;
	if (randomnumber <= 1)
		return (hex_to_rgb((WHITE)));
	else
		return (hex_to_rgb((BLACK)));
}

t_Color	blue_sky(t_Vector ray)
{
	float	intensity;
	t_Color	blue_sky_color;

	blue_sky_color.r = 115;
	blue_sky_color.g = 215;
	blue_sky_color.b = 255;

	intensity = 1.0 - (fabs(ray.y) / ((float)viewport()->height));
	blue_sky_color.r *= intensity;
	blue_sky_color.g *= intensity;
	blue_sky_color.b *= intensity;

	return (blue_sky_color);
}

t_Color	background_color(t_Vector ray)
{
	t_Color	color;

	if (!scene()->background)
		color = blue_sky(ray);
	if (scene()->background == 1)
		color = night_sky();

	return (color);
}
