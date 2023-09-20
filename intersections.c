/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 22:33:12 by simao             #+#    #+#             */
/*   Updated: 2023/09/20 22:03:39 by simao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	trace_ray(t_Vector pos, int t_min, int t_max)
{
	int			closest_t;
	t_Sphere	*closest_sphere;
	int			i;
	t_Point		intersections;

	i = 0;
	closest_sphere = NULL;
	closest_t = INT_MAX;
	while (i < 3)
	{
		intersections = intersects_sphere(pos, scene()->spheres[i]);
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
		return (WHITE);
	return (closest_sphere->color);
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

t_Point	intersects_sphere(t_Vector pos, t_Sphere sphere)
{
	float		a;
	float		b;
	float		c;
	float		discriminant;
	t_Point		intersections;

	a = dot_product(pos, pos);
	b = 2 * dot_product(vector_sub(camera(), &sphere.center), pos);
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
*/
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
}
