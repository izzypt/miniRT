/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:05:41 by simao             #+#    #+#             */
/*   Updated: 2023/09/18 22:07:31 by simao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 - Representa a nossa tela MLX.
*/
t_Canvas	*canvas(void)
{
	static t_Canvas	canvas;

	canvas.width = 1920;
	canvas.height = 1080;

	return (&canvas);
}

/*
- A janela através da qual observamos a scene.
*/
t_Viewport	*viewport(void)
{
	static t_Viewport	viewport;

	viewport.width = 1;
	viewport.height = 1;
	viewport.aspect_ratio = 16 / 9;
	viewport.z = 1;
	viewport.dst = 1;

	return (&viewport);
}

/*
 - Ponto de origim a partir do qual enviamos os raios de luz.
*/
t_Vector	*camera(void)
{
	static t_Vector	camera;

	camera.x = 2;
	camera.y = 2;
	camera.z = 10;

	return (&camera);
}

/*
 - Representa a esfera.
*/
t_Sphere	*sphere(void)
{
	static t_Sphere	sphere;

	sphere.radius = 1;
	sphere.coord.x = 0;
	sphere.coord.y = 0;
	sphere.coord.z = 0;
	sphere.color = 0x964000;

	return (&sphere);
}
