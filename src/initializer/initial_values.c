/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial_values.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 22:09:38 by simao             #+#    #+#             */
/*   Updated: 2023/10/04 14:10:49 by simao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../inc/minirt.h"

/**
 * @brief Calls the functions that set the value for 
 * the canvas, viewport and mlx.
 * 
 */
void	init_windows(void)
{
	set_canvas(960, 540);
	set_viewport();
}

/**
 * @brief Defines the canvas width and height.
 * 
 * @param width The width of the canvas.
 * @param height The height of the canvas.
 */
void	set_canvas(int width, int height)
{
	canvas()->width = width;
	canvas()->height = height;
}

/**
 * @brief Defines the viewport width and height.
 * The default is set to 1. 
 * The objects inside the scene must be coherent with the viewport.
 */
void	set_viewport(void)
{
	viewport()->width = 1;
	viewport()->height = 1;
	viewport()->dist = 1;
	viewport()->aspect_ratio = (float)16 / (float)9;
}

/**
 * @brief Defines the camera position and field of view.
 * 
 * @param x The x coordinate of the camera.
 * @param y The y coordinate of the camera.
 * @param z The z coordinate of the camera.
 * @param fov The field of view of the camera.
 */
void	set_camera(t_Vector cam_pos, t_Vector cam_dir, float fov)
{
	camera()->pos.x = cam_pos.x;
	camera()->pos.y = cam_pos.y;
	camera()->pos.z = cam_pos.z;
	camera()->dir.x = cam_dir.x;
	camera()->dir.y = cam_dir.y;
	camera()->dir.z = cam_dir.z;
	set_fov(fov);
}

/**
 * @brief Creates a mlx instance. 
 * The pointer to the mlx instance and the window are saved on mlibx struct.
 * 
 */
void	set_mlx(void)
{
	mlibx()->mlx = mlx_init();
	mlibx()->win = mlx_new_window(mlibx()->mlx, \
					canvas()->width, canvas()->height, TITLE);
}
