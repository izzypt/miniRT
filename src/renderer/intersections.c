/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 22:33:12 by simao             #+#    #+#             */
/*   Updated: 2023/10/19 21:36:54 by simao            ###   ########.fr       */
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
	intsct.clst_sphr = NULL;
	intsct.clst_pln = NULL;
	intsct.clst_cyl = NULL;
	while (++i < scene()->spheres_count)
	{
		sp_t = intrscts_sphr(O, D, scene()->spheres[i]);
		if (sp_t.t1 < intsct.clst_t && sp_t.t1 >= t_min && sp_t.t1 <= t_max)
		{
			intsct.clst_t = sp_t.t1;
			intsct.clst_sphr = &scene()->spheres[i];
		}
		if (sp_t.t2 < intsct.clst_t && sp_t.t2 >= t_min \
			&& sp_t.t2 <= t_max)
		{
			intsct.clst_t = sp_t.t2;
			intsct.clst_sphr = &scene()->spheres[i];
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
	intsct.clst_sphr = NULL;
	intsct.clst_pln = NULL;
	intsct.clst_cyl = NULL;
	while (++i < scene()->plane_count)
	{
		pl_t = intrscts_pln(O, D, scene()->planes[i]);
		if (pl_t < intsct.clst_t && pl_t >= t_min && pl_t <= t_max)
		{
			intsct.clst_t = pl_t;
			intsct.clst_pln = &scene()->planes[i];
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
	intsct.clst_sphr = NULL;
	intsct.clst_pln = NULL;
	intsct.clst_cyl = NULL;
	while (++i < scene()->cyl_count)
	{
		cy_t = intrscts_cyl(O, D, scene()->cylinders[i]);
		if (cy_t.t1 < intsct.clst_t && cy_t.t1 >= t_min && cy_t.t1 <= t_max)
		{
			intsct.clst_t = cy_t.t1;
			intsct.clst_cyl = &scene()->cylinders[i];
		}
		if (cy_t.t2 < intsct.clst_t && cy_t.t2 >= t_min && cy_t.t2 <= t_max)
		{
			intsct.clst_t = cy_t.t2;
			intsct.clst_cyl = &scene()->cylinders[i];
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
	inter.clst_sphr = NULL;
	inter.clst_pln = NULL;
	inter.clst_cyl = NULL;
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

/*
 - Follows ray to the intersection point (clst_t).
 - Calculates the object normal.
 - Returns t_color of intersection point multiplied by light coefficient.
*/
t_Color	trace_ray(t_Vector ray, int t_min, int t_max)
{
	t_Intersection	itsct;
	t_Vector		p;
	t_Vector		dt;

	itsct = clst_intsct(camera()->pos, ray, t_min, t_max);
	dt = vector_mult(ray, itsct.clst_t);
	p = vector_add(camera()->pos, dt);
	if (itsct.clst_cyl != NULL)
		return (cyl_color(itsct, ray, p, dt));
	if (itsct.clst_pln != NULL)
		return (pln_color(itsct, ray, p, dt));
	if (itsct.clst_sphr != NULL)
		return (sphr_color(itsct, ray, p, dt));
	return (background_color(ray));
}



	/*
	t_Intersection	inter;
	t_Intersection	sp;
	t_Intersection	pl;
	t_Intersection	cy;

	inter.clst_t = INT_MAX;
	inter.clst_sphr = NULL;
	inter.clst_pln = NULL;
	inter.clst_cyl = NULL;
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
	*/

	/*
	t_Point			sphr_intrsct;
	t_Point			cyl_intrsct;
	float			pln_intsct;
	int				i;
	t_Intersection	inter;

	i = -1;
	inter.clst_t = INT_MAX;
	pln_intsct = INT_MAX;
	inter.clst_sphr = NULL;
	inter.clst_pln = NULL;
	inter.clst_cyl = NULL;
	while (++i < scene()->max_obj_count)
	{
		if (i < scene()->spheres_count)
			sphr_intrsct = intrscts_sphr(O, D, scene()->spheres[i]);
		if (i < scene()->plane_count)
			pln_intsct = intrscts_pln(O, D, scene()->planes[i]);
		if (i < scene()->cyl_count)
			cyl_intrsct = intrscts_cyl(O, D, scene()->cylinders[i]);
		if (sphr_intrsct.t1 < inter.clst_t && sphr_intrsct.t1 >= t_min \
			&& sphr_intrsct.t1 <= t_max)
		{
			inter.clst_t = sphr_intrsct.t1;
			inter.clst_sphr = &scene()->spheres[i];
		}
		if (sphr_intrsct.t2 < inter.clst_t && sphr_intrsct.t2 >= t_min \
			&& sphr_intrsct.t2 <= t_max)
		{
			inter.clst_t = sphr_intrsct.t2;
			inter.clst_sphr = &scene()->spheres[i];
		}
		if (pln_intsct < inter.clst_t && pln_intsct >= t_min && pln_intsct <= t_max)
		{
			inter.clst_t = pln_intsct;
			inter.clst_pln = &scene()->planes[i];
		}
		if (cyl_intrsct.t1 < inter.clst_t && cyl_intrsct.t1 >= t_min \
			&& cyl_intrsct.t1 <= t_max)
		{
			inter.clst_t = cyl_intrsct.t1;
			inter.clst_cyl = &scene()->cylinders[i];
		}
		if (cyl_intrsct.t2 < inter.clst_t && cyl_intrsct.t2 >= t_min \
			&& cyl_intrsct.t2 <= t_max)
		{
			inter.clst_t = cyl_intrsct.t2;
			inter.clst_cyl = &scene()->cylinders[i];
		}
	}
	return (inter);
	*/