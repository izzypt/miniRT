/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 12:58:52 by simao             #+#    #+#             */
/*   Updated: 2023/09/16 16:13:06 by simao            ###   ########.fr       */
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

t_Vector	vector_normalize(t_Vector vector1)
{
	float	magnitude;

	magnitude = vector_magnitude(vector1);
	vector1.x = (vector1.x / magnitude);
	vector1.y = (vector1.y / magnitude);
	vector1.z = (vector1.z / magnitude);

	return (vector1);
}
