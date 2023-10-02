/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:05:41 by simao             #+#    #+#             */
/*   Updated: 2023/10/02 12:50:19 by simao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_mlx	*mlibx(void)
{
	static t_mlx	mlx;

	return (&mlx);
}

/**
 * @brief Represents our scene. 
 * 
 * @return A t_Scene static struct containing data about our scene.
 */
t_Scene	*scene(void)
{
	static t_Scene	scene;

	return (&scene);
}

/**
 * @brief Represents our canvas. 
 * 
 * @return A t_Canvas static struct containing data about our canvas.
 */
t_Canvas	*canvas(void)
{
	static t_Canvas	canvas;

	return (&canvas);
}

/**
 * @brief Represents our viewport. 
 * 
 * @return A t_Viewport static struct containing data about our viewport.
 */
t_Viewport	*viewport(void)
{
	static t_Viewport	viewport;

	return (&viewport);
}

/**
 * @brief Represents our camera. 
 * 
 * @return A t_Vector static struct containing data about our camera.
 */
t_Vector	*camera(void)
{
	static t_Vector	camera;

	return (&camera);
}
