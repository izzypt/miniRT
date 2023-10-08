/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 22:46:50 by simao             #+#    #+#             */
/*   Updated: 2023/10/08 16:53:42 by simao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/**
 * @brief Puts a pixel in the canvas considering a new coordinate system.
 * 
 * @param x The x coordinate from the canvas.
 * @param y The y coordinate from the canvas.
 * @param color The color of the pixel.
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

	//printf("Angle between ray and newOrientation is %f\n",angle);
	//printf("Cross product vector is %f %f %f\n", cross.x, cross.y, cross.z);
