/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 22:33:12 by simao             #+#    #+#             */
/*   Updated: 2023/09/27 16:51:48 by simao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	calculate_light(t_Vector *P, t_Vector *N, t_Vector V, int specular)
{
	float		i;
	int			j;
	t_Vector	l_vector;

	j = 0;
	i = 0.0;
	while (j < 3)
	{
		if (scene()->lights[j].type == 'A')
			i = i + scene()->lights[j].intensity;
		else
		{
			if (scene()->lights[j].type == 'P')
				l_vector = vector_sub(&scene()->lights[j].position, P);
			if (scene()->lights[j].type == 'D')
				l_vector = scene()->lights[j].direction;
		}
		diffuse_reflection(*N, l_vector, &i, j);
		specular_reflection(*N, l_vector, specular, &i, j, V);
		j++;
	}
	return (i);
}

t_Color	color_to_paint(t_Sphere	*closest_sphere, float closest_t, t_Vector ray)
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
		calculate_light(&p, &n, vector_mult(&d, -1), closest_sphere->spec)));
}

t_Color	trace_ray(t_Vector ray, int t_min, int t_max)
{
	float		closest_t;
	t_Sphere	*closest_sphere;
	int			i;
	t_Point		intersections;

	i = -1;
	closest_t = INT_MAX;
	closest_sphere = NULL;
	while (++i < 4)
	{
		intersections = intersects_sphere(ray, scene()->spheres[i]);
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
	return (color_to_paint(closest_sphere, closest_t, ray));
}

t_Point	intersects_sphere(t_Vector D, t_Sphere sphere)
{
	float		a;
	float		b;
	float		c;
	float		discriminant;
	t_Point		intersections;

	a = dot_product(D, D);
	b = 2 * dot_product(vector_sub(camera(), &sphere.center), D);
	c = dot_product(vector_sub(camera(), &sphere.center), \
	vector_sub(camera(), &sphere.center)) - sphere.radius * sphere.radius;

	discriminant = b * b - 4.0f * a * c;
	if (discriminant < 0)
	{
		intersections.t1 = INT_MAX;
		intersections.t2 = INT_MAX;
	}
	intersections.t1 = (-b + sqrt(discriminant)) / (2 * a);
	intersections.t2 = (-b - sqrt(discriminant)) / (2 * a);
	return (intersections);
}
