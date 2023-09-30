/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 22:09:38 by simao             #+#    #+#             */
/*   Updated: 2023/09/29 13:00:02 by simao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/minirt.h"

void	set_viewport(void)
{
	viewport()->width = 1;
	viewport()->height = 1;
	viewport()->dist = 1;
	viewport()->aspect_ratio = (float)16 / (float)9;
}

void	set_camera(int x, int y, int z)
{
	camera()->x = x;
	camera()->y = y;
	camera()->z = z;
}

void	set_canvas(int width, int height)
{
	canvas()->width = width;
	canvas()->height = height;
}

void	set_scene(void)
{
	int	i = 0;
	
	scene()->spheres = malloc(sizeof(t_Sphere) * 4);
	scene()->lights = malloc(sizeof(t_Light) * 3);
	scene()->spheres[3].radius = 5000;
	scene()->spheres[3].center.x = 0;
	scene()->spheres[3].center.y = -5001;
	scene()->spheres[3].center.z = 3;
	scene()->spheres[3].color = hex_to_rgb(YELLOW);
	scene()->spheres[3].spec = 1000;
	while (i < 3)
	{

		if (i == 1)
		{
			scene()->spheres[i].radius = 1;
			scene()->spheres[i].center.x = 0;
			scene()->spheres[i].center.y = -1;
			scene()->spheres[i].center.z = 3;
			scene()->spheres[i].color = hex_to_rgb(RED);
			scene()->spheres[i].spec = 500;
		}
		else if (i == 0)
		{
			scene()->spheres[i].radius = 1;
			scene()->spheres[i].center.x = 2;
			scene()->spheres[i].center.y = 0;
			scene()->spheres[i].center.z = 4;
			scene()->spheres[i].color = hex_to_rgb(BLUE);
			scene()->spheres[i].spec = 500;
		}
		else
		{
			scene()->spheres[i].radius = 1;
			scene()->spheres[i].center.x = -2;
			scene()->spheres[i].center.y = 0;
			scene()->spheres[i].center.z = 4;
			scene()->spheres[i].color = hex_to_rgb(GREEN);
			scene()->spheres[i].spec = 10;
		}
		if (i == 0)
		{
			scene()->lights[i].type = 'A';
			scene()->lights[i].intensity = 0.2;
		}
		if (i == 1)
		{
			scene()->lights[i].type = 'P';
			scene()->lights[i].intensity = 0.6;
			scene()->lights[i].position.x = 2;
			scene()->lights[i].position.y = 1;
			scene()->lights[i].position.z = 0;
		}
		if (i == 2)
		{
			scene()->lights[i].type = 'D';
			scene()->lights[i].intensity = 0.2;
			scene()->lights[i].direction.x = 1;
			scene()->lights[i].direction.y = 4;
			scene()->lights[i].direction.z = 4;
		}
		i++;
	}
}

void	init_values(void)
{
	set_canvas(960, 540);
	set_viewport();
	set_camera(0, 0, 0);
	mlibx()->mlx = mlx_init();
	mlibx()->win = mlx_new_window(mlibx()->mlx, canvas()->width, canvas()->height, "MiniRT");
	set_scene();
}
