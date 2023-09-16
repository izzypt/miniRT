/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 13:55:50 by smagalha          #+#    #+#             */
/*   Updated: 2023/09/16 18:22:25 by simao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	Equaçao da esfera:
	 _______________________________________________________________
	|																|
	|	(a - x)² + (b - y)² + (c - z)² - r² = 0						|
	|_______________________________________________________________|
	
	Equção da esfera + Equação do raio:
	 ____________________________________________________________________
	|																	|
	|	(bx² + by² + bz²)t² + (2(axbx + ayby))t + (ax² + ay² - r²) = 0	|
	|___________________________________________________________________|

	a = origem do raio de luz.
	b = direcção do raio de luz.
	r = raio da esfera.
	t = hit distance.
*/
int	intersects_sphere(int x, int y)
{
	float		a;
	float		b;
	float		c;
	float		discriminant;
	t_Vector	ray_dir;

	ray_dir.x = x;
	ray_dir.y = y;
	ray_dir.z = 0;

	ray_dir = vector_normalize(ray_dir);
	a = dot_product(ray_dir, ray_dir);
	b = 2 * dot_product(*camera(), ray_dir);
	c = dot_product(*camera(), *camera()) - pow(sphere()->radius, 2);

	printf("VAlue of a, b , c: %f %f %f\n", a, b, c);
	discriminant = b * b - 4.0 * a * c;
	printf("VAlue of discriminant: %f\n", discriminant);
	if (discriminant >= 0)
		return (1);
	else
		return (0);
}

/*
	Equaçao da esfera:
	 _______________________________________________________________
	|																|
	|	(a - x)² + (b - y)² + (c - z)² - r² = 0						|
	|_______________________________________________________________|
	
	Equção da esfera + Equação do raio:
	 _______________________________________________________________
	|																|
	|	(bx² + by²)t² + (2(axbx + ayby))t + (ax² + ay² - r²) = 0	|
	|_______________________________________________________________|

	a = origem do raio de luz.
	b = direcção do raio de luz.
	r = raio da esfera.
	t = hit distance.
*/
int	intersects_circle(int x, int y)
{
	float	sph_x_squared;
	float	sph_y_squared;
	//float	sph_z_squared;
	float	radius_squared;

	sph_x_squared = pow(x - sphere()->center_x, 2);
	sph_y_squared = pow(y - sphere()->center_y, 2);
	//sph_z_squared = pow(y - sphere()->center_z, 2);
	radius_squared = pow(sphere()->radius, 2);

	if (sph_x_squared + sph_y_squared - radius_squared <= 0)
		return (1);
	else
		return (0);
}

/*
	Necessitamos fazer a correspondência entre o nosso viewport e o nosso canvas.
*/
void	viewport_to_canvas(int *x, int *y)
{
	*x = *x * canvas()->width / viewport()->wdth;
	*y = *y * canvas()->height / viewport()->hght;
}

int	main(void)
{
	void		*mlx;
	void		*mlx_win;
	int			x;
	int			y;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, canvas()->width, canvas()->height, "MiniRT");
	x = 0;
	y = 0;
	while (y <= viewport()->hght)
	{
		while (x <= viewport()->wdth)
		{
			if (intersects_circle(x, y))
				mlx_pixel_put(mlx, mlx_win, x, y, 0x0000FF);
			else
				mlx_pixel_put(mlx, mlx_win, x, y, 0xFFFFFF);
			x++;
		}
		x = 0;
		y++;
	}
	mlx_loop(mlx);
	return (1);
}


/*
A foŕmula abaixo é o resultado da manipulação da equação do círculo e do raio/ray:

(bx² + by²)t² + (2(axbx + ayby))t + (ax² + ay² - r²) = 0

a = origem do ray light.
b = ray light direction
r = radius of circle/sphere
t = hit distance

O resultado indica-nos se existe alguma intersecção entre o raio que disparamos da câmara e o circulo na nossa scene para a distãncia t.

Equação do raio/ray:

P = O + tR

- P is somewhere on the ray defined by its origin (O) and its direction (R).
- t is the distance from the ray origin to P.

Equação do círculo:

(a - x)² + (b - y)² - r² = 0

- a e b representam algum ponto no nosso plano cartesiano.
- x e y representam o centro do nosso círculo.

*/
