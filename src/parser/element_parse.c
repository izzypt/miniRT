/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 16:47:20 by simao             #+#    #+#             */
/*   Updated: 2023/09/29 17:13:59 by simao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

/**
 * @brief Extract and validate ambient light values. 
 * 
 * @param **line a .rt file line splitted by spaces " " containing ambient lightning data.
 */
void	parse_ambient(char **line)
{
    t_Color color;
	float 	intensity;
	char	**rgb_string;

	if (!line[1])
		send_error("Ambient lightning intensity value must be provided\n");
	intensity = ft_atoi(line[1]);
	if (intensity < 0 || intensity > 1)
		send_error("Ambient lightning valid intensity must be between 0.0 and 1.0\n");
	if (!line[2])
		send_error("Ambient lightning RGB colors must be provided\n");
	rgb_string = ft_split(line[2], ',');
	if (!rgb_string[0] || !rgb_string[1] || !rgb_string[2])
		send_error("Ambient light colors must be between 0-255 in format: 255,255,255\n");
	color.r = ft_atoi(rgb_string[0]);
	color.g = ft_atoi(rgb_string[1]);
	color.b = ft_atoi(rgb_string[2]);
	if (color.r > 255 || color.g > 255 || color.b > 255 \
        || color.r < 0 || color.g < 0 || color.b < 0)
		send_error("Ambient lightning RGB colors must be between 0-255\n");
}

/**
 * @brief Extract and validate camera values from the given line.
 * 
 * @param line a file line splitted by spaces " " containing camera data.
 */
void	parse_camera(char **line)
{
	char	**camera_pos;
	t_Vector cam_pos;
	int		fov;

	if (!line[1])
		send_error("Camera position value must be provided\n");
	camera_pos = ft_split(line[1], ',');
	if (!camera_pos[0] || !camera_pos[1] || !camera_pos[2])
		send_error("Camera values must be provided in format: x,y,z\n");
	cam_pos.x = ft_atoi(camera_pos[0]);
	cam_pos.y = ft_atoi(camera_pos[1]);
	cam_pos.z = ft_atoi(camera_pos[2]);
	
}