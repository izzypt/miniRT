/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:05:41 by simao             #+#    #+#             */
/*   Updated: 2023/09/15 17:42:47 by simao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


t_Camera	*camera(void)
{
	static t_Camera	camera_origin;

	camera_origin.x = 3;
	camera_origin.y = 4;
	camera_origin.z = 0;

	return (&camera_origin);
}

t_Viewport	*viewport(void)
{
	static t_Viewport	viewport;

	viewport.width = 300;
	viewport.height = 300;

	return (&viewport);
}

t_Sphere	*sphere(void)
{
	static t_Sphere	sphere;

	sphere.radius = 80;
	sphere.center_x = 125;
	sphere.center_y = 125;

	return (&sphere);
}
