/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 12:58:52 by simao             #+#    #+#             */
/*   Updated: 2023/10/06 12:15:29 by simao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

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

t_Vector	vector_normalize(t_Vector *vector1)
{
	float		magnitude;
	t_Vector	normalized_vector;

	magnitude = vector_magnitude(*vector1);
	if (magnitude != 0.0)
	{
		normalized_vector.x = (vector1->x / magnitude);
		normalized_vector.y = (vector1->y / magnitude);
		normalized_vector.z = (vector1->z / magnitude);
	}
	else
	{
		normalized_vector.x = vector1->x;
		normalized_vector.y = vector1->y;
		normalized_vector.z = vector1->z;
	}	
	return (normalized_vector);
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

t_Vector	vector_mult(t_Vector *vector1, float num)
{
	t_Vector	result;

	result.x = vector1->x * num;
	result.y = vector1->y * num;
	result.z = vector1->z * num;
	return (result);
}

t_Vector	vector_div(t_Vector *vector1, float num)
{
	t_Vector	result;

	result.x = vector1->x / num;
	result.y = vector1->y / num;
	result.z = vector1->z / num;
	return (result);
}

t_Vector MultiplyMatrixVector(const t_RotationMatrix* matrix, const t_Vector* vector)
{
	t_Vector	result;

	result.x = (matrix->m[0][0] * vector->x) \
	+ (matrix->m[0][1] * vector->y) + (matrix->m[0][2] * vector->z);
	result.y = (matrix->m[1][0] * vector->x) \
	+ matrix->m[1][1] * vector->y + matrix->m[1][2] * vector->z;
	result.z = matrix->m[2][0] * vector->x + matrix->m[2][1] * vector->y + matrix->m[2][2] * vector->z;

	return (result);
}
