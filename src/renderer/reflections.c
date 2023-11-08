/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 22:33:12 by simao             #+#    #+#             */
/*   Updated: 2023/11/08 00:04:19 by simao            ###   ########.fr       */
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
	t_LightInfo		lightinfo;
	float			t_max;
	t_Vector		l_vector;
	t_Intersection	sh;

	i = 0.0;
	lightinfo.intensity = &i;
	lightinfo.index = -1;
	while (++(lightinfo.index) < 2)
	{
		*(lightinfo.intensity) = add_ambient_light(i, lightinfo.index);
		if (scene()->lights[lightinfo.index].type == 'P')
		{
			l_vector = vector_sub(scene()->lights[lightinfo.index].position, P);
			t_max = 1;
		}
		sh = clst_intsct(P, l_vector, 0.001, t_max);
		if (sh.clst_sp != NULL || sh.clst_pl != NULL || sh.clst_cy != NULL)
			continue ;
		diff_reflection(N, l_vector, lightinfo.intensity, lightinfo.index);
		spec_reflection(N, l_vector, &lightinfo, V);
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

void	spec_reflection(t_Vector norm, t_Vector lvec, \
						t_LightInfo *info, t_Vector V)
{
	float		r_dot_v;
	t_Vector	normal_double;
	t_Vector	temp;
	t_Vector	r;
	int			spec;

	spec = 200;
	normal_double = vector_mult(norm, 2);
	temp = vector_mult(normal_double, dot_product(norm, lvec));
	if (spec != -1)
	{
		r = vector_sub(temp, lvec);
		r_dot_v = dot_product(r, V);
		if (r_dot_v > 0)
			*(info->intensity) += scene()->lights[info->index].intensity * \
			pow(r_dot_v / (vector_magnitude(r) * vector_magnitude(V)), spec);
	}
}
