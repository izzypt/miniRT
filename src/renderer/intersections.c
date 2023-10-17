/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 22:33:12 by simao             #+#    #+#             */
/*   Updated: 2023/10/17 21:44:33 by simao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	check_sp_intsct(t_Point sphr_intrsct, t_Intersection *intsct, int i)
{
	if (sphr_intrsct.t1 < intsct->clst_t && sphr_intrsct.t1 >= T_MIN \
		&& sphr_intrsct.t1 <= T_MAX)
	{
		intsct->clst_t = sphr_intrsct.t1;
		intsct->clst_sp = &scene()->spheres[i];
	}
	if (sphr_intrsct.t2 < intsct->clst_t && sphr_intrsct.t2 >= T_MIN \
		&& sphr_intrsct.t2 <= T_MAX)
	{
		intsct->clst_t = sphr_intrsct.t2;
		intsct->clst_sp = &scene()->spheres[i];
	}
}

void	check_cy_intsct()
{
	
}

void	check_pl_intsct()
{
	
}

/**
 * @brief Compare all the objects intersection distance in the scene
 * and determine which one is closest to the camera
 * @param O The origin of the ray.
 * @param D The direction of the ray.
 * @param t_min The minimum value of the distance (t).
 * @param t_max The maximum value of the distance (t).
 * @returns t_Intersection holding data about the closest intersection 
 * and the closest object we intersected with.
*/
t_Intersection	clst_intsct(t_Vector O, t_Vector D, float t_min, float t_max)
{
	t_Point			sphr_intrsct;
	t_Point			cyl_intrsct;
	float			pln_intsct;
	int				i;
	t_Intersection	inter;

	i = -1;
	inter.clst_t = INT_MAX;
	pln_intsct = INT_MAX;
	inter.clst_sp = NULL;
	inter.clst_pl = NULL;
	inter.clst_cy = NULL;
	while (++i < 10)
	{
		if (i < scene()->spheres_count)
			sphr_intrsct = intrscts_sphr(O, D, scene()->spheres[i]);
		if (i < scene()->plane_count)
			pln_intsct = intrscts_pln(O, D, scene()->planes[i]);
		if (i < scene()->cyl_count)
			cyl_intrsct = intrscts_cyl(O, D, scene()->cylinders[i]);
		//check_sp_intsct(sphr_intrsct, &inter, i);
		if (sphr_intrsct.t1 < inter.clst_t && sphr_intrsct.t1 >= t_min \
			&& sphr_intrsct.t1 <= t_max)
		{
			inter.clst_t = sphr_intrsct.t1;
			inter.clst_sp = &scene()->spheres[i];
		}
		if (sphr_intrsct.t2 < inter.clst_t && sphr_intrsct.t2 >= t_min \
			&& sphr_intrsct.t2 <= t_max)
		{
			inter.clst_t = sphr_intrsct.t2;
			inter.clst_sp = &scene()->spheres[i];
		}
		if (pln_intsct < inter.clst_t && pln_intsct >= t_min && pln_intsct <= t_max)
		{
			inter.clst_t = pln_intsct;
			inter.clst_pl = &scene()->planes[i];
		}
		if (cyl_intrsct.t1 < inter.clst_t && cyl_intrsct.t1 >= t_min \
			&& cyl_intrsct.t1 <= t_max)
		{
			inter.clst_t = cyl_intrsct.t1;
			inter.clst_cy = &scene()->cylinders[i];
		}
		if (cyl_intrsct.t2 < inter.clst_t && cyl_intrsct.t2 >= t_min \
			&& cyl_intrsct.t2 <= t_max)
		{
			inter.clst_t = cyl_intrsct.t2;
			inter.clst_cy = &scene()->cylinders[i];
		}
	}
	return (inter);
}
