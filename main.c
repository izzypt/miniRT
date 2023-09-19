/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 13:55:50 by smagalha          #+#    #+#             */
/*   Updated: 2023/09/19 19:37:09 by simao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_values(void)
{
	canvas()->width = 1920;
	canvas()->height = 1080;
	viewport()->width = 1;
	viewport()->height = 1;
	viewport()->dist = 1;
	viewport()->aspect_ratio = 16 / 9;
	camera()->x = 0;
	camera()->y = 0;
	camera()->z = 0;
	sphere()->radius = 3;
	sphere()->coord.x = 0;
	sphere()->coord.y = 0;
	sphere()->coord.z = 0;
	sphere()->color = 0x964000;
}

int	main(void)
{
	void		*mlx;
	void		*mlx_win;
	int			x;
	int			y;
	t_Vector	ray_dir;

	x = -1;
	y = -1;
	init_values();
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, canvas()->width, canvas()->height, "MiniRT");
	while (++y <= canvas()->height)
	{
		while (++x <= canvas()->width)
		{
			canvas_to_viewport(x, y, &ray_dir);
			if (intersects_sphere(ray_dir))
				mlx_pixel_put(mlx, mlx_win, x, y, 0x0000FF);
			else
				mlx_pixel_put(mlx, mlx_win, x, y, 0xFFFFFF);
		}
		x = 0;
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

*/

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