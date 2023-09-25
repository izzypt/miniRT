/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 22:33:12 by simao             #+#    #+#             */
/*   Updated: 2023/09/25 11:53:42 by simao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	calculate_light(t_Vector *P, t_Vector *N)
{
	float		i;
	float		n_dot_l;
	int			j;
	t_Vector	L;

	j = 0;
	i = 0.0;
	while (j < 3)
	{
		if (scene()->lights[j].type == 'A')
			i = i + scene()->lights[j].intensity;
		else
		{
			if (scene()->lights[j].type == 'P')
				L = vector_sub(&scene()->lights[j].position, P);
			if (scene()->lights[j].type == 'D')
			{
				L = vector_normalize(&scene()->lights[j].direction);
			}
		}
		n_dot_l = dot_product(*N, L);
		if (n_dot_l > 0)
		{
			i = i + \
			(scene()->lights[j].intensity * n_dot_l / (vector_magnitude(*N) * vector_magnitude(L)));
		}
		j++;
	}
	printf("Intensity %f\n", i);
	return (i);
}

t_Color	trace_ray(t_Vector ray, int t_min, int t_max)
{
	float		closest_t;
	t_Sphere	*closest_sphere;
	int			i;
	t_Point		intersections;
	t_Vector	N;
	t_Vector	P;
	t_Vector	D;

	i = 0;
	closest_t = INT_MAX;
	closest_sphere = NULL;
	while (i < 4)
	{
		intersections = intersects_sphere(ray, scene()->spheres[i]);
		if (intersections.t1 < closest_t \
			&& intersections.t1 >= t_min \
			&& intersections.t1 <= t_max)
		{
			closest_t = intersections.t1;
			closest_sphere = &scene()->spheres[i];
		}
		if (intersections.t2 < closest_t \
			&& intersections.t2 >= t_min \
			&& intersections.t2 <= t_max)
		{
			closest_t = intersections.t2;
			closest_sphere = &scene()->spheres[i];
		}
		i++;
	}
	if (closest_sphere == NULL)
		return (hex_to_rgb(WHITE));
	D = vector_mult(&ray, closest_t);
	P = vector_add(camera(), &D);
	N = vector_sub(&P, &closest_sphere->center);
	N = vector_normalize(&N);
	//return (closest_sphere->color);
	return (color_mult(&closest_sphere->color, calculate_light(&P, &N)));
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
	intersections.t1 = (-b + sqrt(discriminant) / (2 * a));
	intersections.t2 = (-b - sqrt(discriminant) / (2 * a));
	return (intersections);
}

/*
	Equação do raio/ray:
	 _______________________________________________________
	|														|
	|	P = O + tR											|
	|_______________________________________________________|

	O = origem do raio ( camera )
	t = distância
	R = direcção ( ponto final - ponto inicial, normalizado)

	Equaçao da esfera:
	 _______________________________________________________   
	|														|
	|	(a - x)² + (b - y)² + (c - z)² - r² = 0				|
	|_______________________________________________________|

	- a e b e c representam algum ponto no nosso plano cartesiano.
	- x e y e z representam o centro da nossa esfera.
*/

/*
	Equação do raio/ray:
	 ________________________________________________________________
	|																|
	|	P = O + tR													|
	|_______________________________________________________________|

	O = origem do raio ( vetor 2D, indica posição inicial)
	t = distância
	R = direcção (vetor unitário )

	Equaçao da circulo:
	 _______________________________________________________________
	|																|
	|	(a - x)² + (b - y)² - r² = 0								|
	|_______________________________________________________________|
	
	Equaçao da esfera:
	 _______________________________________________________________
	|																|
	|	(a - x)² + (b - y)² + (c - z)² - r² = 0						|
	|_______________________________________________________________|

	- a e b representam algum ponto no nosso plano cartesiano.
	- x e y representam o centro do nosso círculo.

int	intersects_circle(int x, int y)
{
	float	sph_x_squared;
	float	sph_y_squared;
	float	sph_z_squared;
	float	radius_squared;

	sph_x_squared = pow(x - sphere()->center.x, 2);
	sph_y_squared = pow(y - sphere()->center.y, 2);
	sph_z_squared = pow(y - sphere()->center.z, 2);
	radius_squared = pow(sphere()->radius, 2);

	if (sph_x_squared + sph_y_squared + sph_z_squared - radius_squared <= 0)
		return (1);
	else
		return (0);
}*/
