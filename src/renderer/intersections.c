/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 22:33:12 by simao             #+#    #+#             */
/*   Updated: 2023/11/03 15:08:19 by simao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/**
 * @brief It iterates over all the spheres in the scene and it returns 
 * the closest intersection point and corresponding sphere
 * @param O The origin of the ray.
 * @param D The direction of the ray.
 * @param t_min The minimum value of the distance (t).
 * @param t_max The maximum value of the distance (t).
 * @returns t_Intersection holding data about the closest intersection 
 * and the closest object we intersected with.
*/
t_Intersection	check_all_sp(t_Vector O, t_Vector D, float t_min, float t_max)
{
	t_Point			sp_t;
	t_Intersection	intsct;
	int				i;

	i = -1;
	intsct.clst_t = INT_MAX;
	intsct.clst_sp = NULL;
	intsct.clst_pl = NULL;
	intsct.clst_cy = NULL;
	while (++i < scene()->spheres_count)
	{
		sp_t = intrscts_sphr(O, D, scene()->spheres[i]);
		if (sp_t.t1 < intsct.clst_t && sp_t.t1 >= t_min && sp_t.t1 <= t_max)
		{
			intsct.clst_t = sp_t.t1;
			intsct.clst_sp = &scene()->spheres[i];
		}
		if (sp_t.t2 < intsct.clst_t && sp_t.t2 >= t_min \
			&& sp_t.t2 <= t_max)
		{
			intsct.clst_t = sp_t.t2;
			intsct.clst_sp = &scene()->spheres[i];
		}
	}
	return (intsct);
}

/**
 * @brief It iterates over all the planes in the scene and it returns 
 * the closest intersection point and corresponding plane.
 * @param O The origin of the ray.
 * @param D The direction of the ray.
 * @param t_min The minimum value of the distance (t).
 * @param t_max The maximum value of the distance (t).
 * @returns t_Intersection holding data about the closest intersection 
 * and the closest object we intersected with.
*/
t_Intersection	check_all_pl(t_Vector O, t_Vector D, float t_min, float t_max)
{
	float			pl_t;
	t_Intersection	intsct;
	int				i;

	i = -1;
	intsct.clst_t = INT_MAX;
	intsct.clst_sp = NULL;
	intsct.clst_pl = NULL;
	intsct.clst_cy = NULL;
	while (++i < scene()->plane_count)
	{
		pl_t = intrscts_pln(O, D, scene()->planes[i]);
		if (pl_t < intsct.clst_t && pl_t >= t_min && pl_t <= t_max)
		{
			intsct.clst_t = pl_t;
			intsct.clst_pl = &scene()->planes[i];
		}
	}
	return (intsct);
}

/**
 * @brief It iterates over all the cylinders in the scene and it returns 
 * the closest intersection point and corresponding cylinder
 * @param O The origin of the ray.
 * @param D The direction of the ray.
 * @param t_min The minimum value of the distance (t).
 * @param t_max The maximum value of the distance (t).
 * @returns t_Intersection holding data about the closest intersection 
 * and the closest object we intersected with.
*/
t_Intersection	check_all_cy(t_Vector O, t_Vector D, float t_min, float t_max)
{
	t_Point			cy_t;
	t_Intersection	intsct;
	int				i;

	i = -1;
	intsct.clst_t = INT_MAX;
	intsct.clst_sp = NULL;
	intsct.clst_pl = NULL;
	intsct.clst_cy = NULL;
	while (++i < scene()->cyl_count)
	{
		cy_t = intrscts_cyl(O, D, scene()->cylinders[i]);
		if (cy_t.t1 < intsct.clst_t && cy_t.t1 >= t_min && cy_t.t1 <= t_max)
		{
			intsct.clst_t = cy_t.t1;
			intsct.clst_cy = &scene()->cylinders[i];
		}
		if (cy_t.t2 < intsct.clst_t && cy_t.t2 >= t_min && cy_t.t2 <= t_max)
		{
			intsct.clst_t = cy_t.t2;
			intsct.clst_cy = &scene()->cylinders[i];
		}
	}
	return (intsct);
}

/**
 * @brief Performs the calculus to find the distance of the intersection points 
 * of a ray with a sphere.
 * @param O The origin of the ray.
 * @param D The direction of the ray.
 * @param t_min The minimum value of the distance (t).
 * @param t_max The maximum value of the distance (t).
 * @returns t_Intersection holding data about the closest intersection 
 * and the closest object we intersected with.
*/
t_Intersection	clst_intsct(t_Vector O, t_Vector D, float t_min, float t_max)
{
	t_Intersection	inter;
	t_Intersection	sp;
	t_Intersection	pl;
	t_Intersection	cy;

	inter.clst_t = INT_MAX;
	inter.clst_sp = NULL;
	inter.clst_pl = NULL;
	inter.clst_cy = NULL;
	sp = check_all_sp(O, D, t_min, t_max);
	pl = check_all_pl(O, D, t_min, t_max);
	cy = check_all_cy(O, D, t_min, t_max);
	if (sp.clst_t < pl.clst_t && sp.clst_t < cy.clst_t)
		inter = sp;
	if (pl.clst_t < sp.clst_t && pl.clst_t < cy.clst_t)
		inter = pl;
	if (cy.clst_t < sp.clst_t && cy.clst_t < pl.clst_t)
		inter = cy;
	return (inter);
}
