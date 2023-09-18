/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 13:55:50 by smagalha          #+#    #+#             */
/*   Updated: 2023/09/18 13:28:15 by simao            ###   ########.fr       */
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

int		main(void)
{
	void		*mlx;
	void		*mlx_win;
	int			x;
	int			y;
	t_Vector	pos;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, canvas()->width, canvas()->height, "MiniRT");
	x = 0;
	y = 0;
	while (y <= canvas()->height)
	{
		while (x <= canvas()->width)
		{
			pos.x = (x / (float)canvas()->width - 0.5) * 2.0;
			pos.y = (y / (float)canvas()->height - 0.5) * 2.0;
			pos.z = 4;
			if (intersects_sphere(pos))
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

	/*t_Vector A;
	t_Vector B;
	t_Vector C;
	t_Vector D;
	t_Vector E;
	t_Vector Z;

	float a;
	float b;
	float c;
	float d;
	float e;


	A.x = 2;
	A.y = 3;
	A.z = 6;
	B.x = -1;
	B.y = 4;
	B.z = -5;

	Z = sub_vectors(&A, &B);

	printf("Valor do vetor Z: %f %f %f\n", Z.x, Z.y, Z.z);

	C.x = 0;
	C.y = 0;
	C.z = 0;
	D.x = 3;
	D.y = -2;
	D.z = 7;
	E.x = -4;
	E.y = -1;
	E.z = -8;

	a = vector_magnitude(A);
	b = vector_magnitude(B);
	c = vector_magnitude(C);
	d = vector_magnitude(D);
	e = vector_magnitude(E);

	printf("Magnitude dos vetores A, B, C, D, E: %f, %f, %f, %f, %f\n",a,b,c,d,e);

	a = dot_product(A, A);
	b = dot_product(B, B);
	c = dot_product(C, C);
	d = dot_product(D, D);
	e = dot_product(E, E);

	printf("Dot Product vector A: %f\n", a);
	printf("Dot Product vector B: %f\n", b);
	printf("Dot Product vector C: %f\n", c);
	printf("Dot Product vector D: %f\n", d);
	printf("Dot Product vector E: %f\n", e);

	vector_normalize(&A);
	vector_normalize(&B);
	vector_normalize(&C);
	vector_normalize(&D);
	vector_normalize(&E);

	printf("Normalized vector A: %f , %f, %f\n", A.x, A.y, A.z);
	printf("Normalized vector B: %f , %f, %f\n", B.x, B.y, B.z);
	printf("Normalized vector C: %f , %f, %f\n", C.x, C.y, C.z);
	printf("Normalized vector D: %f , %f, %f\n", D.x, D.y, D.z);
	printf("Normalized vector E: %f , %f, %f\n", E.x, E.y, E.z);*/
}


/*
A foŕmula abaixo é o resultado da manipulação da equação do círculo e do raio/ray:

(bx² + by²)t² + (2(axbx + ayby))t + (ax² + ay² - r²) = 0

a = origem do ray light.
b = ray light direction
r = radius of circle/sphere
t = hit distance

O resultado indica-nos se existe alguma intersecção entre o raio que disparamos da câmara e o circulo na nossa scene para a distãncia t.

*/
