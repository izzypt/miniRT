/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 22:33:12 by simao             #+#    #+#             */
/*   Updated: 2023/09/18 22:33:55 by simao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
int	intersects_sphere(t_Vector pos)
{
	float		a;
	float		b;
	float		c;
	float		discriminant;

	a = dot_product(pos, pos);
	b = 2 * dot_product(*camera(), pos);
	c = dot_product(*camera(), *camera()) - sphere()->radius * sphere()->radius;

	discriminant = b * b - 4.0f * a * c;
	if (discriminant >= 0)
		return (1);
	else
		return (0);
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

	sph_x_squared = pow(x - sphere()->coord.x, 2);
	sph_y_squared = pow(y - sphere()->coord.y, 2);
	sph_z_squared = pow(y - sphere()->coord.z, 2);
	radius_squared = pow(sphere()->radius, 2);

	if (sph_x_squared + sph_y_squared + sph_z_squared - radius_squared <= 0)
		return (1);
	else
		return (0);
}
