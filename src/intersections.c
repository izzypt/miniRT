/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 22:33:12 by simao             #+#    #+#             */
/*   Updated: 2023/09/29 13:00:08 by simao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

/*t_Color	color_to_paint(t_Sphere	*closest_sphere, float closest_t, t_Vector ray)
{
	t_Vector	n;
	t_Vector	p;
	t_Vector	d;

	if (closest_sphere == NULL)
		return (hex_to_rgb(WHITE));
	d = vector_mult(&ray, closest_t);
	p = vector_add(camera(), &d);
	n = vector_sub(&p, &closest_sphere->center);
	return (
		color_mult(&closest_sphere->color, \
		calculate_light(&p, &n, vector_mult(&d, -1), closest_sphere)));
}*/

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

t_Color	trace_ray(t_Vector ray, int t_min, int t_max)
{
	t_Vector		p;
	t_Vector		n;
	t_Vector		d;
	t_Intersection	intersect;

	intersect = closest_intersect(camera(), &ray, t_min, t_max);
	if (intersect.closest_sphere == NULL)
		return (hex_to_rgb(WHITE));
	d = vector_mult(&ray, intersect.closest_t);
	p = vector_add(camera(), &d);
	n = vector_sub(&p, &intersect.closest_sphere->center);
	return (
		color_mult(&intersect.closest_sphere->color, \
		calculate_light(&p, &n, vector_mult(&d, -1), intersect.closest_sphere)));
}

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
