/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial_values.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 22:09:38 by simao             #+#    #+#             */
/*   Updated: 2023/10/10 11:38:11 by simao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../inc/minirt.h"

/**
 * @brief Defines the canvas width and height.
 * 
 * @param width The width of the canvas.
 * @param height The height of the canvas.
 * 
 * @note A few options for some of the possible 16:9 resolutions:
 * @note ```640 x	360 	nHD```
 * @note ```854 x	480 	FWVGA```
 * @note ```960 x	540 	qHD```
 * @note ```1024 x	576 	WSVGA```
 * @note ```1280 x	720 	HD```
 * @note ```1366 x	768 	FWXGA```
 * @note ```1600 x	900 	HD+```
 * @note ```1920 x	1080 	Full HD```
 */
void	set_canvas(int width, int height)
{
	canvas()->width = width;
	canvas()->height = height;
}

/**
 * @brief Defines the viewport width and height.
 * 
 * @note The default is set to 1. 
 * @note The objects position inside the scene must be 
 * coherent with the viewport.
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
	camera()->initial_dir.x = 0.0;
	camera()->initial_dir.y = 0.0;
	camera()->initial_dir.z = viewport()->dist;
	set_fov(fov);
}

/**
 * @brief Creates a mlx instance. 
 * 
 * @note The pointer to the mlx instance is saved on ```mlibx()->mlx```
 * @note The pointerto the window is saved on ```mlibx()->win```
 */
void	set_mlx(void)
{
	void	*mlx_window;
	void	*mlx_addr;
	void	*mlx_img;
	void	*mlx_menu;
	int		wdth;
	int     hght;

	wdth = 5;
	hght = 15;
	mlibx()->mlx = mlx_init();
	mlx_window = mlx_new_window(mlibx()->mlx, \
	canvas()->width, canvas()->height, "MiniRT");
	mlx_img = mlx_new_image(mlibx()->mlx, canvas()->width, canvas()->height);
	mlibx()->img = mlx_img;
	mlx_addr = mlx_get_data_addr(mlibx()->img, \
	&(mlibx()->bpp), &(mlibx()->line_len), &(mlibx()->endian));
	mlibx()->addr = mlx_addr;
	mlibx()->win = mlx_window;
	mlx_menu = mlx_xpm_file_to_image(mlibx()->mlx, \
	"scenes/menu.xpm", &wdth, &hght);
	mlibx()->menu_img = mlx_menu;
}
