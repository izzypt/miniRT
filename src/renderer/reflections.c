/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 22:33:12 by simao             #+#    #+#             */
/*   Updated: 2023/10/05 16:37:27 by simao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

float	calc_light(t_Vector *P, t_Vector *N, t_Vector V, t_Sphere *clst_s)
{
	float			i;
	int				j;
	float			t_max;
	t_Vector		l_vector;
	t_Intersection	shadow;

	j = -1;
	i = 0.0;
	while (++j < 2)
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
		}
		shadow = clst_intsct(P, &l_vector, 0.001, t_max);
		if (shadow.closest_sphere != NULL)
			continue ;
		diff_reflection(*N, l_vector, &i, j);
		spec_reflection(*N, l_vector, clst_s->spec, &i, j, V);
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
