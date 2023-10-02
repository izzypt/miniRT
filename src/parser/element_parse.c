/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 16:47:20 by simao             #+#    #+#             */
/*   Updated: 2023/10/02 12:30:48 by simao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/**
 * @brief Extract and validate ambient light values. 
 * 
 * @param **line a .rt file line splitted by spaces " " containing ambient light data.
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
	char		**camera_pos;
	char		**camera_dir;
	t_Vector	cam_pos;
	t_Vector	cam_dir;
	int			fov;

	if (!line[1] || !line[2] || !line[3])
		send_error("One or more camera values are missing\n");
	camera_pos = ft_split(line[1], ',');
	if (!camera_pos[0] || !camera_pos[1] || !camera_pos[2])
		send_error("Camera values must be provided in format: x,y,z\n");
	cam_pos.x = ft_atoi(camera_pos[0]);
	cam_pos.y = ft_atoi(camera_pos[1]);
	cam_pos.z = ft_atoi(camera_pos[2]);
	camera_dir = ft_split(line[2], ',');
	if (!camera_dir[0] || !camera_dir[1] || !camera_dir[2])
		send_error("Camera values must be provided in format: x,y,z\n");
	cam_dir.x = ft_atoi(camera_dir[0]);
	cam_dir.y = ft_atoi(camera_dir[1]);
	cam_dir.z = ft_atoi(camera_dir[2]);
	if (cam_dir.x < 0.0 || cam_dir.y < 0.0 || cam_dir.z < 0.0 \
		|| cam_dir.x > 1.0 || cam_dir.y > 1.0 || cam_dir.z > 1.0 )
		send_error("Camera orientation vector must be between 0.0 and 1.0\n");
	fov = ft_atoi(line[3]);
	if (fov < 0 || fov > 180)
		send_error("Camera field of view must be between 0 and 180\n");
}

/**
 * @brief Extract and validate point light values. 
 * 
 * @param **line a .rt file line splitted by spaces " " containing point light data.
 */
void	parse_light(char **line)
{
	char		**light_pos;
	t_Vector	light;
	float		intensity;

	if (!line[1] || !line[2] || !line[3])
		send_error("One or more light values are missing\n");
	light_pos = ft_split(line[1], ',');
	if (!light_pos[0] || !light_pos[1] || !light_pos[2])
		send_error("Camera values must be provided in format: x,y,z\n");
	light.x = ft_atoi(light_pos[0]);
	light.y = ft_atoi(light_pos[1]);
	light.z = ft_atoi(light_pos[2]);
	intensity = ft_atoi(line[2]);
	if (intensity < 0.0 || intensity > 1.0)
		send_error("Point Light intensity value must be between 0.0 and 1.0\n");
}
