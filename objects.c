/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:05:41 by simao             #+#    #+#             */
/*   Updated: 2023/09/19 14:20:22 by simao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 - Representa a nossa tela MLX.
*/
t_Canvas	*canvas(void)
{
	static t_Canvas	canvas;

	return (&canvas);
}

/*
- A janela através da qual observamos a scene.
*/
t_Viewport	*viewport(void)
{
	static t_Viewport	viewport;

	return (&viewport);
}

/*
 - Ponto de origim a partir do qual enviamos os raios de luz.
*/
t_Vector	*camera(void)
{
	static t_Vector	camera;

	return (&camera);
}

/*
 - Representa a esfera.
*/
t_Sphere	*sphere(void)
{
	static t_Sphere	sphere;

	return (&sphere);
}
