/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 13:55:50 by smagalha          #+#    #+#             */
/*   Updated: 2023/09/28 00:38:09 by simao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(void)
{
	void		*mlx;
	void		*window;
	t_Color		color;
	int			x;
	int			y;
	t_Vector	D;

	init_values();
	x = ((canvas()->width / 2) * -1);
	y = (canvas()->height / 2);
	set_fov(75);
	mlx = mlx_init();
	window = mlx_new_window(mlx, canvas()->width, canvas()->height, "MiniRT");
	while (--y >= (canvas()->height / 2) * -1)
	{
		while (++x <= (canvas()->width / 2))
		{
			D = canvas_to_viewport(x, y);
			color = trace_ray(D, 1, INT_MAX);
			put_pixel(x, y, color, mlx, window);
		}
		x = ((canvas()->width / 2) * -1);
	}
	mlx_loop(mlx);
	return (1);
}
