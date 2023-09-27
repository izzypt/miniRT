/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 22:09:38 by simao             #+#    #+#             */
/*   Updated: 2023/09/27 16:14:57 by simao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minirt.h"

void	init_values(void)
{
	int	i = 0;

	canvas()->width = 960;
	canvas()->height = 540;
	viewport()->width = 1;
	viewport()->height = 1;
	viewport()->dist = 1;
	viewport()->aspect_ratio = (float)16 / (float)9;
	camera()->x = 0;
	camera()->y = 0;
	camera()->z = 0;
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
			scene()->lights[i].intensity = 0.4;
		}
		if (i == 1)
		{
			scene()->lights[i].type = 'P';
			scene()->lights[i].intensity = 0.4;
			scene()->lights[i].position.x = 2;
			scene()->lights[i].position.y = 1;
			scene()->lights[i].position.z = 0;
		}
		if (i == 2)
		{
			scene()->lights[i].type = 'D';
			scene()->lights[i].intensity = 0.1;
			scene()->lights[i].direction.x = 1;
			scene()->lights[i].direction.y = 4;
			scene()->lights[i].direction.z = 4;
		}
		i++;
	}
}
