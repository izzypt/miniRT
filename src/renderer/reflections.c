/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 22:33:12 by simao             #+#    #+#             */
/*   Updated: 2023/11/03 15:18:43 by simao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

float	add_ambient_light(float i, int j)
{
	if (scene()->lights[j].type == 'A')
		i = i + scene()->lights[j].intensity;
	return (i);
}

/**
 * @brief Calculate the light and shadow at a given point in the scene.
 * @param P Any point on the scene that we will check for light 
 * and shadow by casting a ray backwards from this point to the light point.
 * @param N the normal vector of the geometrical shape.
 * @param V the light vector from P to the camera origin.
 * @param spec the specular reflection coefficient of the object material.
 * @returns The calculated intensity of a light for point P.
*/
float	calc_light(t_Vector P, t_Vector N, t_Vector V, float spec)
{
	float			i;
	int				j;
	float			t_max;
	t_Vector		l_vector;
	t_Intersection	sh;


	j = -1;
	i = 0.0;
	while (++j < 2)
	{
		i = add_ambient_light(i, j);
		if (scene()->lights[j].type == 'P')
		{
			l_vector = vector_sub(scene()->lights[j].position, P);
			t_max = 1;
		}
		sh = clst_intsct(P, l_vector, 0.001, t_max);
		if (sh.clst_sp != NULL || sh.clst_pl != NULL || sh.clst_cy != NULL)
			continue ;
		diff_reflection(N, l_vector, &i, j);
		spec_reflection(N, l_vector, spec, &i, j, V);
	}
	return (i);
}

void	diff_reflection(t_Vector norm, t_Vector lvec, float *i, int j)
{
	float		n_dot_l;

	n_dot_l = dot_product(norm, lvec);
	if (n_dot_l > 0)
	{
		*i += (scene()->lights[j].intensity * n_dot_l / \
		(vector_magnitude(norm) * vector_magnitude(lvec)));
	}
}

void	spec_reflection(t_Vector norm, t_Vector lvec, int spec, float *i, int j, t_Vector V)
{
	float		r_dot_v;
	t_Vector	normal_double;
	t_Vector	temp;
	t_Vector	R;

	normal_double = vector_mult(norm, 2);
	temp = vector_mult(normal_double, dot_product(norm, lvec));
	if (spec != -1)
	{
		R = vector_sub(temp, lvec);
		r_dot_v = dot_product(R, V);
		if (r_dot_v > 0)
			*i += scene()->lights[j].intensity * \
			pow(r_dot_v / (vector_magnitude(R) * vector_magnitude(V)), spec);
	}
}
