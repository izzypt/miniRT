/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 13:55:50 by smagalha          #+#    #+#             */
/*   Updated: 2023/09/15 17:57:32 by simao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	Equaçao do circulo :
		(a - x)² + (b - y)² - r² = 0
*/
int	intersects_circle(int x, int y)
{
	float	sph_x_squared;
	float	sph_y_squared;
	float	radius_squared;

	sph_x_squared = pow(x - sphere()->center_x, 2);
	sph_y_squared = pow(y - sphere()->center_y, 2);
	radius_squared = pow(sphere()->radius, 2);

	if (sph_x_squared + sph_y_squared - radius_squared <= 0)
		return (1);
	else
		return (0);
}

int	main( void )
{
	void		*mlx;
	void		*mlx_win;
	int			x;
	int			y;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Ray Tracing");
	x = 0;
	y = 0;
	while (y <= viewport()->height)
	{
		while (x <= viewport()->width)
		{
			if (intersects_circle(x, y))
				mlx_pixel_put(mlx, mlx_win, x, y, 0x964000);
			else
				mlx_pixel_put(mlx, mlx_win, x, y, 0xFFA500);
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
