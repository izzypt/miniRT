/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 22:33:12 by simao             #+#    #+#             */
/*   Updated: 2023/10/17 16:13:28 by simao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

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
			color = trace_ray(d, T_MIN, T_MAX);
			put_pixel(x, y, color);
		}
		x = ((canvas()->width / 2) * -1);
	}
	mlx_put_image_to_window(mlibx()->mlx, mlibx()->win, mlibx()->img, 0, 0);
	mlx_put_image_to_window(mlibx()->mlx, \
	mlibx()->win, mlibx()->menu_img, 0, 0);
}
