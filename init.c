/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 22:09:38 by simao             #+#    #+#             */
/*   Updated: 2023/09/20 22:01:27 by simao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minirt.h"

void	init_values(void)
{
	int	i = 0;

	canvas()->width = 1920;
	canvas()->height = 1080;
	viewport()->width = 1;
	viewport()->height = 1;
	viewport()->dist = 1;
	viewport()->aspect_ratio = (float)16 / (float)9;
	camera()->x = 0;
	camera()->y = 0;
	camera()->z = -5;
	scene()->spheres = malloc(sizeof(t_Sphere) * 3);
	while (i < 3)
	{
		scene()->spheres[i].radius = 0.5 + i / 2;
		scene()->spheres[i].center.x = 0.5 + i * 2;
		scene()->spheres[i].center.y = 2 * i;
		scene()->spheres[i].center.z = 2 * i;
		if (i == 1)
			scene()->spheres[i].color = RED;
		else if (i == 0)
			scene()->spheres[i].color = GREEN;
		else
			scene()->spheres[i].color = BLUE;
		i++;
	}
}
