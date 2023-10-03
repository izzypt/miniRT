/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 22:33:12 by simao             #+#    #+#             */
/*   Updated: 2023/10/03 15:44:46 by simao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/*
 - Calculates the closest intersection point from the origin (O) towards (D).
 - Returns t_Intersection (closes_t and closest_sphere).
*/
t_Intersection	closest_intersect(t_Vector *O, t_Vector *D, float t_min, float t_max)
{
	t_Point			intersections;
	t_Sphere		*closest_sphere;
	float			closest_t;
	int				i;
	t_Intersection	inter;

	i = -1;
	closest_t = INT_MAX;
	closest_sphere = NULL;
	while (++i < 4)
	{
		intersections = intersects_sphere(*O, *D, scene()->spheres[i]);
		if (intersections.t1 < closest_t && intersections.t1 >= t_min \
			&& intersections.t1 <= t_max)
		{
			closest_t = intersections.t1;
			closest_sphere = &scene()->spheres[i];
		}
		if (intersections.t2 < closest_t && intersections.t2 >= t_min \
			&& intersections.t2 <= t_max)
		{
			closest_t = intersections.t2;
			closest_sphere = &scene()->spheres[i];
		}
	}
	inter.closest_sphere = closest_sphere;
	inter.closest_t = closest_t;
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

	intrsct = closest_intersect(camera(), &ray, t_min, t_max);
	if (intrsct.closest_sphere == NULL)
		return (hex_to_rgb(BLACK));
	d = vector_mult(&ray, intrsct.closest_t);
	p = vector_add(camera(), &d);
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
