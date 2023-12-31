/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 22:09:38 by simao             #+#    #+#             */
/*   Updated: 2023/11/08 18:32:34 by simao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/**
 * @brief Count and store the maximum value of objects in the scene.
 * 
 */
void	sp_max_count(void)
{
	if (scene()->spheres_count > scene()->max_obj_count)
		scene()->max_obj_count = scene()->spheres_count;
}

/**
 * @brief Allocates memory for spheres and 
 * stores the previous allocated spheres on tmp.
 */
void	allocate_more_sp(t_Sphere *tmp)
{
	tmp = scene()->spheres;
	scene()->spheres = malloc(sizeof(t_Sphere) * scene()->spheres_count);
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
 */
void	new_sphere(int i, float radius, t_Vector center, t_Color color)
{
	scene()->spheres[i].radius = radius;
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
void	set_sphere(float radius, t_Vector center, t_Color color)
{
	t_Sphere	*tmp;
	int			i;

	scene()->spheres_count++;
	sp_max_count();
	i = -1;
	if (scene()->spheres == NULL)
	{
		tmp = NULL;
		scene()->spheres = malloc(sizeof(t_Sphere) * 1);
	}
	else
		allocate_more_sp(tmp = scene()->spheres);
	while (++i < scene()->spheres_count)
	{
		if (i == scene()->spheres_count - 1)
		{
			if (tmp != NULL)
				free(tmp);
			new_sphere(i, radius, center, color);
		}
		else
			copy_sphere(i, tmp);
	}
}
