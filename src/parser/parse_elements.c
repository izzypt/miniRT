/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 16:47:20 by simao             #+#    #+#             */
/*   Updated: 2023/11/03 15:14:18 by simao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/**
 * @brief Extract and validate ambient light values. s
 * 
 * @param line a .rt file line splitted by spaces " " containing ambt light data.
 */
void	parse_ambient(char **line)
{
	t_Color	color;
	float	intensity;
	char	**rgb_string;

	if (!line[1])
		send_error("Ambient light intensity value must be provided\n");
	intensity = ft_atof(line[1]);
	if (intensity < 0 || intensity > 1)
		send_error("Ambient light intensity must be between 0.0 and 1.0\n");
	if (!line[2])
		send_error("Ambient light RGB colors must be provided\n");
	rgb_string = ft_split(line[2], ',');
	if (!rgb_string[0] || !rgb_string[1] || !rgb_string[2])
		send_error("A.Light colors must be between 0-255: 255,255,255\n");
	color.r = ft_atof(rgb_string[0]);
	color.g = ft_atof(rgb_string[1]);
	color.b = ft_atof(rgb_string[2]);
	validate_rgb_values(color.r, color.g, color.b);
	set_ambient_light(intensity);
	free_matrix(rgb_string);
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
	float		fov;

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
	cam_dir.x = ft_atof(camera_dir[0]);
	cam_dir.y = ft_atof(camera_dir[1]);
	cam_dir.z = ft_atof(camera_dir[2]);
	validate_normal_vector(cam_dir.x, cam_dir.y, cam_dir.z);
	fov = validate_fov(ft_atof(line[3]));
	set_camera(cam_pos, cam_dir, fov);
	free_matrix(camera_pos);
	free_matrix(camera_dir);
}

/**
 * @brief Extract and validate point light values. 
 * 
 * @param line a .rt file line splitted by spaces " " 
 * containing point light data.
 */
void	parse_light(char **line)
{
	char		**light_pos;
	t_Vector	light_position;
	float		intensity;

	if (!line[1] || !line[2] || !line[3])
		send_error("One or more light values are missing\n");
	light_pos = ft_split(line[1], ',');
	if (!light_pos[0] || !light_pos[1] || !light_pos[2])
		send_error("Light values must be provided in format: x,y,z\n");
	light_position.x = ft_atof(light_pos[0]);
	light_position.y = ft_atof(light_pos[1]);
	light_position.z = ft_atof(light_pos[2]);
	intensity = ft_atof(line[2]);
	if (intensity < 0.0 || intensity > 1.0)
		send_error("Point Light intensity value must be between 0.0 and 1.0\n");
	set_point_light(intensity, light_position);
	free_matrix(light_pos);
}
