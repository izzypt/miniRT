/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 22:09:38 by simao             #+#    #+#             */
/*   Updated: 2023/10/18 13:51:45 by simao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/**
 * @brief Copies the data of the spheres from temporary buffer to the scene.
 * 
 * @param i The index of the sphere in the temporary buffer.
 * @param tmp The temporary buffer.
 */
void	copy_plane(int i, t_Plane *tmp)
{
	scene()->planes[i].point.x = tmp[i].point.x;
	scene()->planes[i].point.y = tmp[i].point.y;
	scene()->planes[i].point.z = tmp[i].point.z;
	scene()->planes[i].normal.x = tmp[i].normal.x;
	scene()->planes[i].normal.y = tmp[i].normal.y;
	scene()->planes[i].normal.z = tmp[i].normal.z;
	scene()->planes[i].color.r = tmp[i].color.r;
	scene()->planes[i].color.g = tmp[i].color.g;
	scene()->planes[i].color.b = tmp[i].color.b;
}

/**
 * @brief Creates a new sphere with the given values.
 * 
 * @param i The index of the new sphere in the array.
 * @param diameter The sphere diameter.
 * @param center The sphere diameter.
 * @param color The sphere color.
 */
void	new_plane(int i, t_Vector point, t_Vector normal, t_Color color)
{
	scene()->planes[i].point.x = point.x;
	scene()->planes[i].point.y = point.y;
	scene()->planes[i].point.z = point.z;
	scene()->planes[i].normal.x = normal.x;
	scene()->planes[i].normal.y = normal.y;
	scene()->planes[i].normal.z = normal.z;
	scene()->planes[i].color.r = color.r;
	scene()->planes[i].color.g = color.g;
	scene()->planes[i].color.b = color.b;
	scene()->planes[i].spec = 500 + i;
}

/**
 * @brief Stores the value of a plane in the scene. 
 * It allocates memory if necessary 
 * or realocates the memory to adapt a new plane.
 * 
 * @param point A point in the plane.
 * @param normal The normal vector of the plane.
 * @param color The plane color.
 */
void	set_plane(t_Vector point, t_Vector normal, t_Color color)
{
	t_Plane		*tmp;
	int			i;

	scene()->plane_count++;
	if (scene()->plane_count > scene()->max_obj_count)
		scene()->max_obj_count = scene()->plane_count;
	i = -1;
	if (scene()->planes == NULL)
		scene()->planes = malloc(sizeof(t_Plane) * 1);
	else
	{
		tmp = scene()->planes;
		scene()->planes = malloc(sizeof(t_Plane) * scene()->plane_count);
	}
	while (++i < scene()->plane_count)
	{
		if (i == scene()->plane_count - 1)
			new_plane(i, point, normal, color);
		else
			copy_plane(i, tmp);
	}
}
