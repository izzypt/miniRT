/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 22:33:12 by simao             #+#    #+#             */
/*   Updated: 2023/10/16 15:10:34 by simao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/*
 - Calculates the closest intersection point from the origin (O) towards (D).
 - Returns t_Intersection (closes_t and closest_sphere/plane).
*/
t_Intersection	clst_intsct(t_Vector *O, t_Vector *D, float t_min, float t_max)
{
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
	while (++i < scene()->spheres_count)
	{
		sphr_intrsct = intrscts_sphr(*O, *D, scene()->spheres[i]);
		pln_intsct = intrscts_pln(*O, *D, scene()->planes[i]);
		cyl_intrsct = intrscts_cyl(*O, *D, scene()->cylinders[i]);
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
}

/*
 - Follows ray to the intersection point (clst_t).
 - Calculates the object normal.
 - Returns t_color of intersection point multiplied by light coefficient.
*/
t_Color	trace_ray(t_Vector ray, int t_min, int t_max)
{
	t_Vector		p;
	t_Vector		n;
	t_Vector		dt;
	t_Intersection	intrsct;

	intrsct = clst_intsct(&camera()->pos, &ray, t_min, t_max);
	if (intrsct.clst_sphr == NULL && intrsct.clst_pln == NULL)
		return (background_color(ray));
	dt = vector_mult(&ray, intrsct.clst_t);
	p = vector_add(&camera()->pos, &dt);
	if (intrsct.clst_cyl != NULL)
		return (intrsct.clst_cyl->color);
	if (intrsct.clst_pln != NULL)
		return (color_mult(&intrsct.clst_pln->color, \
		calc_light(&p, &intrsct.clst_pln->normal, vector_mult(&dt, -1), intrsct.clst_pln->spec)));
	n = vector_sub(&p, &intrsct.clst_sphr->center);
	return (
		color_mult(&intrsct.clst_sphr->color, \
		calc_light(&p, &n, vector_mult(&dt, -1), intrsct.clst_sphr->spec)));
}

/*
 - Checks if the ray with origin (O) and direction (D) intersects with sphere.
 - Returns a t_Point with the intersection points, if any.
*/
t_Point	intrscts_sphr(t_Vector O, t_Vector D, t_Sphere sphere)
{
	float		a;
	float		b;
	float		c;
	float		discriminant;
	t_Point		intersections;

	a = dot_product(D, D);
	b = 2 * dot_product(vector_sub(&O, &sphere.center), D);
	c = dot_product(vector_sub(&O, &sphere.center), \
	vector_sub(&O, &sphere.center)) - sphere.radius * sphere.radius;

	discriminant = b * b - 4.0f * a * c;
	intersections.t1 = (-b + sqrt(discriminant)) / (2 * a);
	intersections.t2 = (-b - sqrt(discriminant)) / (2 * a);
	if (discriminant < 0)
	{
		intersections.t1 = INT_MAX;
		intersections.t2 = INT_MAX;
	}
	return (intersections);
}

/**
 * @brief Checks for intersections with a plane.
 * @param nmal The normal of the plane.
 * @param plan_p A point on the plane.
 * @param D the direction of the ray.
 * @returns Returns a float with the intersection points, if any.
 * @note The equation of the plane is ```(p - a) * n = 0``` , where:
 * @note ```a``` is a point on the plane
 * @note ```n``` is the normal of the plane. 
 * @note ```P``` is the point we are testing for intersection with the plane.
 * @note ``` ```
 * @note In order for ```P``` to intersect with the plane, 
 * the vector from ```a``` to ```P``` has to be perpendicular to ```n```.
 * @note i.e , the dot product of vector from ```a``` to ```P``` and ```n``` 
 * has to be zero.
*/
float	intrscts_pln(t_Vector O, t_Vector D, t_Plane pln)
{
	t_Vector	planetoorigin;
	float		denom;
	float		t;

	t = (float)INT_MAX;
	denom = dot_product(pln.normal, D);
	if (fabs(denom) > 0.001)
	{
		planetoorigin = vector_sub(&pln.point, &O);
		t = dot_product(planetoorigin, pln.normal) / denom;
		if (t < 0)
			t = INT_MAX;
		return (t);
	}
	return (t);
}

/*
 - Checks if the ray with origin (O) and direction (D) intersects with a cylinder.
 - Returns a t_Point with the intersection points, if any.
*/
t_Point	intrscts_cyl(t_Vector O, t_Vector D, t_Cylinder cylinder)
{
	t_Vector	result;
	t_Point		intersections;
	t_Vector	delta_p;
	float		discriminant;

	delta_p = vector_sub(&O, &cylinder.pos);
	result.x = dot_product(D, D) - pow(dot_product(D, cylinder.normal), 2);
	result.y = 2 * (dot_product(D, delta_p) - dot_product(D, cylinder.normal) * dot_product(delta_p, cylinder.normal));
	result.z = dot_product(delta_p, delta_p) - pow(dot_product(delta_p, cylinder.normal), 2) - pow(cylinder.radius, 2);

	discriminant = result.y * result.y - 4.0f * result.x * result.x;
	if (discriminant < 0)
	{
		intersections.t1 = INT_MAX;
		intersections.t2 = INT_MAX;
	}
	else
	{
		intersections.t1 = (-result.y + sqrt(discriminant)) / (2 * result.x);
		intersections.t2 = (-result.y - sqrt(discriminant)) / (2 * result.x);
	}

	return (intersections);
}
