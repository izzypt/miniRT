/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 22:09:38 by simao             #+#    #+#             */
/*   Updated: 2023/10/06 11:45:36 by simao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/**
 * @brief Defines the value of ambient light. It allocates memory if necessary.
 * 
 * @param intensity The intensity of the ambient light.
 */
void	set_ambient_light(float intensity)
{
	if (scene()->lights == NULL)
		scene()->lights = malloc(sizeof(t_Light) * 2);
	scene()->lights[0].type = 'A';
	scene()->lights[0].intensity = intensity;
}

/**
 * @brief Defines the value of point light. It allocates memory if necessary.
 * 
 * @param intensity The intensity of the point light.
 * @param position The coordinates of the point light.
 */
void	set_point_light(float intensity, t_Vector position)
{
	if (scene()->lights == NULL)
		scene()->lights = malloc(sizeof(t_Light) * 2);
	scene()->lights[1].type = 'P';
	scene()->lights[1].intensity = intensity;
	scene()->lights[1].position.x = position.x;
	scene()->lights[1].position.y = position.y;
	scene()->lights[1].position.z = position.z;
}

/*
	scene()->lights[i].type = 'D';
	scene()->lights[i].intensity = 0.2;
	scene()->lights[i].direction.x = 1;
	scene()->lights[i].direction.y = 4;
	scene()->lights[i].direction.z = 4;
*/