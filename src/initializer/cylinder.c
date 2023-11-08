/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 22:09:38 by simao             #+#    #+#             */
/*   Updated: 2023/11/08 18:09:32 by simao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/**
 * @brief Count and store the maximum value of cylinders.
 * 
 */
void	cy_max_count(void)
{
	if (scene()->cyl_count > scene()->max_obj_count)
		scene()->max_obj_count = scene()->cyl_count;
}

/**
 * @brief Allocates memory for cylinders and 
 * stores the previous allocated cylinders on tmp.
 */
void	allocate_more_cy(t_Cylinder *tmp)
{
	tmp = scene()->cylinders;
	scene()->cylinders = malloc(sizeof(t_Cylinder) * scene()->cyl_count);
}

/**
 * @brief Copies the data of the cylinder from temporary buffer to the scene.
 * 
 * @param i The index of the sphere in the temporary buffer.
 * @param tmp The temporary buffer.
 */
void	copy_cylinder(int i, t_Cylinder *tmp)
{
	scene()->cylinders[i].pos.x = tmp[i].pos.x;
	scene()->cylinders[i].pos.y = tmp[i].pos.y;
	scene()->cylinders[i].pos.z = tmp[i].pos.z;
	scene()->cylinders[i].normal.x = tmp[i].normal.x;
	scene()->cylinders[i].normal.y = tmp[i].normal.y;
	scene()->cylinders[i].normal.z = tmp[i].normal.z;
	scene()->cylinders[i].normal.z = tmp[i].normal.z;
	scene()->cylinders[i].radius = tmp[i].radius;
	scene()->cylinders[i].height = tmp[i].height;
	scene()->cylinders[i].color.r = tmp[i].color.r;
	scene()->cylinders[i].color.g = tmp[i].color.g;
	scene()->cylinders[i].color.b = tmp[i].color.b;
	scene()->cylinders[i].spec = tmp[i].spec;
}

/**
 * @brief Creates a new cylinder with the given values.
 * 
 * @param i The index of the new cylinder in the array.
 * @param diameter The cylinder diameter.
 * @param center The cylinder diameter.
 * @param color The cylinder color.
 */
void	new_cylinder(int i, t_Cylinder cylinder)
{
	scene()->cylinders[i].pos.x = cylinder.pos.x;
	scene()->cylinders[i].pos.y = cylinder.pos.y;
	scene()->cylinders[i].pos.z = cylinder.pos.z;
	scene()->cylinders[i].normal.x = cylinder.normal.x;
	scene()->cylinders[i].normal.y = cylinder.normal.y;
	scene()->cylinders[i].normal.z = cylinder.normal.z;
	scene()->cylinders[i].radius = cylinder.radius;
	scene()->cylinders[i].height = cylinder.height;
	scene()->cylinders[i].color.r = cylinder.color.r;
	scene()->cylinders[i].color.g = cylinder.color.g;
	scene()->cylinders[i].color.b = cylinder.color.b;
	scene()->cylinders[i].spec = 500 + i;
}

/**
 * @brief Stores the value of a cylinder in the scene. 
 * It allocates memory if necessary 
 * or realocates the memory to adapt a new cylinder.
 * 
 * @param point A point in the cylinder.
 * @param normal The normal vector of the cylinder.
 * @param color The cylinder color.
 */
void	set_cylinder(t_Cylinder cylinder)
{
	t_Cylinder		*tmp;
	int				i;

	scene()->cyl_count++;
	cy_max_count();
	i = -1;
	if (scene()->cylinders == NULL)
	{
		tmp = NULL;
		scene()->cylinders = malloc(sizeof(t_Cylinder) * 1);
	}
	else
		allocate_more_cy(tmp = scene()->cylinders);
	while (++i < scene()->cyl_count)
	{
		if (i == scene()->cyl_count - 1)
		{
			if (tmp != NULL)
				free(tmp);
			new_cylinder(i, cylinder);
		}
		else
			copy_cylinder(i, tmp);
	}
}
