/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:05:41 by simao             #+#    #+#             */
/*   Updated: 2023/09/16 18:22:48 by simao            ###   ########.fr       */
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
 - Representa a janela através da qual vemos a scene e os raios de luz atravessam.
*/
t_Viewport	*viewport(void)
{
	static t_Viewport	viewport;

	viewport.wdth = 300;
	viewport.hght = 300;
	viewport.z = 0;
	viewport.dst = 1;

	return (&viewport);
}

/*
 - Ponto de origim a partir do qual enviamos os raios de luz.
*/
t_Vector	*camera(void)
{
	static t_Vector	camera_origin;

	camera_origin.x = 0;
	camera_origin.y = 0;
	camera_origin.z = 1;

	return (&camera_origin);
}

/*
 - Representa a esfera.
*/
t_Sphere	*sphere(void)
{
	static t_Sphere	sphere;

	sphere.radius = 95;
	sphere.center_x = 125;
	sphere.center_y = 125;
	sphere.center_z = 125;
	sphere.color = 0x964000;

	return (&sphere);
}
