/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 13:55:50 by smagalha          #+#    #+#             */
/*   Updated: 2023/10/02 13:16:00 by simao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

int	main(int argc, char **argv)
{
	t_Color		color;
	int			x;
	int			y;
	t_Vector	D;

	parse_file(argv);
	init_values();
	x = ((canvas()->width / 2) * -1);
	y = (canvas()->height / 2);
	set_fov(75);
	while (--y >= (canvas()->height / 2) * -1)
	{
		while (++x <= (canvas()->width / 2))
		{
			D = canvas_to_viewport(x, y);
			color = trace_ray(D, 1, INT_MAX);
			put_pixel(x, y, color);
		}
		x = ((canvas()->width / 2) * -1);
	}
	mlx_loop(mlibx()->mlx);
	return (1);
}
