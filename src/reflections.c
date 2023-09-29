/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 22:33:12 by simao             #+#    #+#             */
/*   Updated: 2023/09/29 18:07:46 by simao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

float	calculate_light(t_Vector *P, t_Vector *N, t_Vector V, t_Sphere	*closest_sphere)
{
	float			i;
	int				j;
	float			t_max;
	t_Vector		l_vector;
	t_Intersection	shadow;

	j = -1;
	i = 0.0;
	while (++j < 3)
	{
		if (scene()->lights[j].type == 'A')
			i = i + scene()->lights[j].intensity;
		else
		{
			if (scene()->lights[j].type == 'P')
			{
				l_vector = vector_sub(&scene()->lights[j].position, P);
				t_max = 1;
			}
			if (scene()->lights[j].type == 'D')
			{
				l_vector = scene()->lights[j].direction;
				t_max = INT_MAX;
			}
		}
		shadow = closest_intersect(P, &l_vector, 0.001, t_max);
		if (shadow.closest_sphere != NULL)
			continue ;
		diffuse_reflection(*N, l_vector, &i, j);
		specular_reflection(*N, l_vector, closest_sphere->spec, &i, j, V);
	}
	return (i);
}

void	diffuse_reflection(t_Vector norm, t_Vector lvec, float *i, int j)
{
	float		n_dot_l;

	n_dot_l = dot_product(norm, lvec);
	if (n_dot_l > 0)
	{
		*i += (scene()->lights[j].intensity * n_dot_l / \
		(vector_magnitude(norm) * vector_magnitude(lvec)));
	}
}

void	specular_reflection(t_Vector norm, t_Vector lvec, int spec, float *i, int j, t_Vector V)
{
	float		r_dot_v;
	t_Vector	normal_double;
	t_Vector	temp;
	t_Vector	R;

	normal_double = vector_mult(&norm, 2);
	temp = vector_mult(&normal_double, dot_product(norm, lvec));
	if (spec != -1)
	{
		R = vector_sub(&temp, &lvec);
		r_dot_v = dot_product(R, V);
		if (r_dot_v > 0)
			*i += scene()->lights[j].intensity * \
			pow(r_dot_v / (vector_magnitude(R) * vector_magnitude(V)), spec);
	}
}
