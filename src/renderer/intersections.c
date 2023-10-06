/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 22:33:12 by simao             #+#    #+#             */
/*   Updated: 2023/10/06 11:48:19 by simao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/*
 - Calculates the closest intersection point from the origin (O) towards (D).
 - Returns t_Intersection (closes_t and closest_sphere).
*/
t_Intersection	clst_intsct(t_Vector *O, t_Vector *D, float t_min, float t_max)
{
	t_Point			sphr_intrsct;
	int				i;
	t_Intersection	inter;

	i = -1;
	inter.closest_t = INT_MAX;
	inter.closest_sphere = NULL;
	while (++i < scene()->spheres_count)
	{
		sphr_intrsct = intersects_sphere(*O, *D, scene()->spheres[i]);
		if (sphr_intrsct.t1 < inter.closest_t && sphr_intrsct.t1 >= t_min \
			&& sphr_intrsct.t1 <= t_max)
		{
			inter.closest_t = sphr_intrsct.t1;
			inter.closest_sphere = &scene()->spheres[i];
		}
		if (sphr_intrsct.t2 < inter.closest_t && sphr_intrsct.t2 >= t_min \
			&& sphr_intrsct.t2 <= t_max)
		{
			inter.closest_t = sphr_intrsct.t2;
			inter.closest_sphere = &scene()->spheres[i];
		}
	}
	return (inter);
}

/*
 - Follows ray to the intersection point (closest_t).
 - Calculates the object normal.
 - Returns t_color of intersection point multiplied by light coefficient.
*/
t_Color	trace_ray(t_Vector ray, int t_min, int t_max)
{
	t_Vector		p;
	t_Vector		n;
	t_Vector		d;
	t_Intersection	intrsct;

	intrsct = clst_intsct(&camera()->pos, &ray, t_min, t_max);
	if (intrsct.closest_sphere == NULL)
		return (hex_to_rgb(BLACK));
	d = vector_mult(&ray, intrsct.closest_t);
	p = vector_add(&camera()->pos, &d);
	n = vector_sub(&p, &intrsct.closest_sphere->center);
	return (
		color_mult(&intrsct.closest_sphere->color, \
		calc_light(&p, &n, vector_mult(&d, -1), intrsct.closest_sphere)));
}

/*
 - Checks if the ray with origin (O) and direction (D) intersects with sphere.
 - Returns a t_Point with the intersection points, if any.
*/
t_Point	intersects_sphere(t_Vector O, t_Vector D, t_Sphere sphere)
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

/*
 - Checks for intersections with a plane.
 - Returns a float with the intersection points, if any.
 - In geometric terms, denom measures how aligned the ray direction is with the plane's normal.
 - O produto escalar entre o normal do plano e a direcção do raio igual a 0 indica que o raio e o plano são paralelos, logo não intersectam.
*/
float	intersects_plane(t_Vector nmal, t_Vector plan_p, t_Vector O, t_Vector D)
{
	t_Vector	planetoorigin;
	float		denom;
	float		t;

	t = (float)INT_MAX;
	denom = dot_product(nmal, D);
	if (denom > 0)
	{
		planetoorigin = vector_sub(&plan_p, &O);
		t = dot_product(planetoorigin, nmal) / denom;
		if (t < 0)
			t = INT_MAX;
		return (t);
	}
	return (t);
}
