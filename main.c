/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 13:55:50 by smagalha          #+#    #+#             */
/*   Updated: 2023/09/26 02:27:22 by simao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(void)
{
	void		*mlx;
	void		*window;
	t_Color		color;
	int			x;
	int			y;
	t_Vector	D;

	init_values();
	x = ((canvas()->width / 2) * -1);
	y = (canvas()->height / 2);
	set_fov(75);
	mlx = mlx_init();
	window = mlx_new_window(mlx, canvas()->width, canvas()->height, "MiniRT");
	while (--y >= (canvas()->height / 2) * -1)
	{
		while (++x <= (canvas()->width / 2))
		{
			D = canvas_to_viewport(x, y);
			color = trace_ray(D, 1, INT_MAX);
			put_pixel(x, y, color, mlx, window);
		}
		x = ((canvas()->width / 2) * -1);
	}
	mlx_loop(mlx);
	return (1);
}


/*
 - Mudar o sistema de coordenadas (0,0) |.			|
										|    .		|
										|			|
 -
*/

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

/*int	main(void)
{
    // Create a sample RGB color
	t_Color	originalColor;

	originalColor.r = 100;
	originalColor.g = 150;
	originalColor.b = 200;

    // Test rgb_to_hex function
    int hexValue = rgb_to_hex(originalColor);
    printf("Original RGB Color (R:%f, G:%f, B:%f) as Hex: 0x%X\n", originalColor.r, originalColor.g, originalColor.b, hexValue);

    // Test hex_to_rgb function
    t_Color convertedColor = hex_to_rgb(hexValue);
    printf("Converted Hex (0x%X) to RGB (R:%f, G:%f, B:%f)\n", hexValue, convertedColor.r, convertedColor.g, convertedColor.b);

	// Test color_add function
	t_Color color1 = {50, 75, 100};
	t_Color color2 = {25, 40, 60};
	t_Color addedColor = color_add(&color1, &color2);
	printf("Color1 + Color2 = (R:%f, G:%f, B:%f)\n", addedColor.r, addedColor.g, addedColor.b);

    // Test color_sub function
    t_Color subtractedColor = color_sub(&color1, &color2);
    printf("Color1 - Color2 = (R:%f, G:%f, B:%f)\n", subtractedColor.r, subtractedColor.g, subtractedColor.b);

    // Test color_mult function
    float scale = 0.5; // Scale factor
    t_Color scaledColor = color_mult(&color1, scale);
    printf("Color1 * %.2f = (R:%f, G:%f, B:%f)\n", scale, scaledColor.r, scaledColor.g, scaledColor.b);

    return 0;
}*/
