/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 12:58:52 by simao             #+#    #+#             */
/*   Updated: 2023/09/18 22:39:33 by simao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	vector_magnitude(t_Vector vector1)
{
	float	magnitude;

	magnitude = sqrt(\
		pow(vector1.x, 2) + \
		pow(vector1.y, 2) + \
		pow(vector1.z, 2) \
	);
	return (magnitude);
}

float	dot_product(t_Vector vector1, t_Vector vector2)
{
	float	result;

	result = (vector1.x * vector2.x) \
	+ (vector1.y * vector2.y) \
	+ (vector1.z * vector2.z);

	return (result);
}

void	vector_normalize(t_Vector *vector1)
{
	float		magnitude;

	magnitude = vector_magnitude(*vector1);
	if (magnitude != 0.0)
	{
		vector1->x = (vector1->x / magnitude);
		vector1->y = (vector1->y / magnitude);
		vector1->z = (vector1->z / magnitude);
	}
}

t_Vector	vector_add(t_Vector *vector1, t_Vector *vector2)
{
	t_Vector	result;

	result.x = vector1->x + vector2->x;
	result.y = vector1->y + vector2->y;
	result.z = vector1->z + vector2->z;
	return (result);
}

t_Vector	vector_sub(t_Vector *vector1, t_Vector *vector2)
{
	t_Vector	result;

	result.x = vector1->x - vector2->x;
	result.y = vector1->y - vector2->y;
	result.z = vector1->z - vector2->z;
	return (result);
}

t_Vector	vector_mult(t_Vector *vector1, int num)
{
	t_Vector	result;

	result.x = vector1->x * num;
	result.y = vector1->y * num;
	result.z = vector1->z * num;
	return (result);
}

