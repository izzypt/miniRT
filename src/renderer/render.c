/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 22:33:12 by simao             #+#    #+#             */
/*   Updated: 2023/10/17 20:06:13 by simao            ###   ########.fr       */
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

/*
 - Follows ray to the intersection point (clst_t).
 - Calculates the object normal.
 - Returns t_color of intersection point multiplied by light coefficient.
*/
t_Color	trace_ray(t_Vector ray, int t_min, int t_max)
{
	t_Intersection	itsct;
	t_Vector		p;
	t_Vector		dt;

	itsct = clst_intsct(camera()->pos, ray, t_min, t_max);
	dt = vector_mult(ray, itsct.clst_t);
	p = vector_add(camera()->pos, dt);
	if (itsct.clst_cy != NULL)
		return (cyl_color(itsct, ray, p, dt));
	if (itsct.clst_pl != NULL)
		return (pln_color(itsct, ray, p, dt));
	if (itsct.clst_sp != NULL)
		return (sphr_color(itsct, ray, p, dt));
	return (background_color(ray));
}