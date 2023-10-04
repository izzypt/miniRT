/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements_values.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 22:09:38 by simao             #+#    #+#             */
/*   Updated: 2023/10/03 18:57:35 by simao            ###   ########.fr       */
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

/**
 * @brief Copies the data of the spheres from temporary buffer to the scene.
 * 
 * @param i The index of the sphere in the temporary buffer.
 * @param tmp The temporary buffer.
 */
void	copy_sphere(int i, t_Sphere *tmp)
{
	scene()->spheres[i].radius = tmp[i].radius;
	scene()->spheres[i].center.x = tmp[i].center.x;
	scene()->spheres[i].center.y = tmp[i].center.y;
	scene()->spheres[i].center.z = tmp[i].center.z;
	scene()->spheres[i].color.r = tmp[i].color.r;
	scene()->spheres[i].color.g = tmp[i].color.g;
	scene()->spheres[i].color.b = tmp[i].color.b;
	scene()->spheres[i].spec = tmp[i].spec;
}

/**
 * @brief Creates a new sphere with the given values.
 * 
 * @param i The index of the new sphere in the array.
 * @param diameter The sphere diameter.
 * @param center The sphere diameter.
 * @param color The sphere color.
 * @param spheres_num The number of spheres in the scene.
 */
void	new_sphere(int i, float diameter, t_Vector center, t_Color color)
{
	scene()->spheres[i].radius = diameter / 2;
	scene()->spheres[i].center.x = center.x;
	scene()->spheres[i].center.y = center.y;
	scene()->spheres[i].center.z = center.z;
	scene()->spheres[i].color.r = color.r;
	scene()->spheres[i].color.g = color.g;
	scene()->spheres[i].color.b = color.b;
	scene()->spheres[i].spec = 500 + i;
}

/**
 * @brief Defines the value of a sphere in the scene. 
 * It allocates memory if necessary 
 * or realocates the memory to adapt a new sphere.
 * 
 * @param diameter The sphere diameter.
 * @param center The sphere diameter.
 * @param color The sphere color.
 * @param spheres_num The number of spheres in the scene.
 */
void	set_sphere(float diameter, t_Vector center, t_Color color)
{
	t_Sphere	*tmp;
	int			i;

	scene()->spheres_count++;
	i = -1;
	if (scene()->spheres == NULL)
		scene()->spheres = malloc(sizeof(t_Sphere) * 1);
	else
	{
		tmp = scene()->spheres;
		scene()->spheres = malloc(sizeof(t_Sphere) * scene()->spheres_count);
	}
	while (++i < scene()->spheres_count)
	{
		if (i == scene()->spheres_count - 1)
			new_sphere(i, diameter, center, color);
		else
			copy_sphere(i, tmp);
	}
}


/*
	scene()->lights[i].type = 'D';
	scene()->lights[i].intensity = 0.2;
	scene()->lights[i].direction.x = 1;
	scene()->lights[i].direction.y = 4;
	scene()->lights[i].direction.z = 4;
*/