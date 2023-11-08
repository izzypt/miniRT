/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 12:58:52 by simao             #+#    #+#             */
/*   Updated: 2023/11/07 21:47:31 by simao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_Vector	vector_sub(t_Vector vector1, t_Vector vector2)
{
	t_Vector	result;

	result.x = vector1.x - vector2.x;
	result.y = vector1.y - vector2.y;
	result.z = vector1.z - vector2.z;
	return (result);
}

t_Vector	vector_mult(t_Vector vector1, float num)
{
	t_Vector	result;

	result.x = vector1.x * num;
	result.y = vector1.y * num;
	result.z = vector1.z * num;
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
