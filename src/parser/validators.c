/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validators.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 16:47:20 by simao             #+#    #+#             */
/*   Updated: 2023/11/03 13:05:40 by simao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	validate_rgb_values(int r, int g, int b)
{
	if (r > 255 || g > 255 || b > 255 || r < 0 || g < 0 || b < 0)
		send_error("Ambient lightning RGB colors must be between 0-255\n");
}

void	validate_normal_vector(int x, int y, int z)
{
	if (x > 1.0 || y > 1.0 || z > 1.0 || x < -1.0 || y < -1.0 || z < -1.0)
		send_error("Normal vectors must be between -1.0 and 1.0\n");
}

float	validate_fov(float fov)
{
	if (fov < 0 || fov > 180)
		send_error("Camera field of view must be between 0 and 180\n");
	return (fov);
}

void	validate_plane_values(char **plane_point, char **plane_normal, \
							char **plane_color)
{
	if (!plane_point[0] || !plane_point[1] || !plane_point[2])
		send_error("Plane point values must be provided in format: x,y,z\n");
	if (!plane_normal[0] || !plane_normal[1] || !plane_normal[2])
		send_error("Plane normal values must be provided in format: x,y,z\n");
	if (!plane_color[0] || !plane_color[1] || !plane_color[2])
		send_error("Color values must be in format: R,G,B. range 0-255.\n");
}

void	validate_cyl_values(char **plane_point, char **plane_normal, \
							char **plane_color)
{
	if (!plane_point[0] || !plane_point[1] || !plane_point[2])
		send_error("Cylinder values must be provided in format: x,y,z\n");
	if (!plane_normal[0] || !plane_normal[1] || !plane_normal[2])
		send_error("Cyl normal values must be provided in format: x,y,z\n");
	if (!plane_color[0] || !plane_color[1] || !plane_color[2])
		send_error("Color values must be in format: R,G,B. range 0-255.\n");
}
