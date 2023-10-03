/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 16:47:20 by simao             #+#    #+#             */
/*   Updated: 2023/10/03 12:42:36 by simao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/**
 * @brief Extract and validate ambient light values. 
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
	intensity = ft_atoi(line[1]);
	if (intensity < 0 || intensity > 1)
		send_error("Ambient light intensity must be between 0.0 and 1.0\n");
	if (!line[2])
		send_error("Ambient light RGB colors must be provided\n");
	rgb_string = ft_split(line[2], ',');
	if (!rgb_string[0] || !rgb_string[1] || !rgb_string[2])
		send_error("A.Light colors must be between 0-255: 255,255,255\n");
	color.r = ft_atoi(rgb_string[0]);
	color.g = ft_atoi(rgb_string[1]);
	color.b = ft_atoi(rgb_string[2]);
	validate_rgb_values(color.r, color.g, color.b);
	set_ambient_light(intensity);
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
	validate_normal_vector(cam_dir.x, cam_dir.y, cam_dir.z);
	fov = ft_atoi(line[3]);
	if (fov < 0 || fov > 180)
		send_error("Camera field of view must be between 0 and 180\n");
	set_camera(cam_pos.x, cam_pos.y, cam_pos.z);
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
		send_error("Camera values must be provided in format: x,y,z\n");
	light_position.x = ft_atoi(light_pos[0]);
	light_position.y = ft_atoi(light_pos[1]);
	light_position.z = ft_atoi(light_pos[2]);
	intensity = ft_atof(line[2]);
	if (intensity < 0.0 || intensity > 1.0)
		send_error("Point Light intensity value must be between 0.0 and 1.0\n");
	set_point_light(intensity, light_position);
	free_matrix(light_pos);
}

/**
 * @brief Extract and validate sphere values. 
 * 
 * @param **line a .rt file line splitted by spaces " " containing sphere data.
 */
void	parse_sphere(char **line)
{
	char		**sphere_pos;
	char		**sphere_color;
	float		diameter;
	t_Color		color;
	t_Vector	center;

	if (!line[1] || !line[2] || !line[3])
		send_error("One or more sphere values are missing\n");
	sphere_pos = ft_split(line[1], ',');
	if (!sphere_pos[0] || !sphere_pos[1] || !sphere_pos[2])
		send_error("Sphere center values must be provided in format: x,y,z\n");
	center.x = ft_atoi(sphere_pos[0]);
	center.y = ft_atoi(sphere_pos[1]);
	center.z = ft_atoi(sphere_pos[2]);
	diameter = ft_atoi(line[2]);
	sphere_color = ft_split(line[3], ',');
	if (!sphere_color[0] || !sphere_color[1] || !sphere_color[2])
		send_error("Color values must be in format: R,G,B. range 0-255.\n");
	color.r = ft_atoi(sphere_color[0]);
	color.g = ft_atoi(sphere_color[1]);
	color.b = ft_atoi(sphere_color[2]);
	validate_rgb_values(color.r, color.g, color.b);
	set_sphere(diameter, center, color);
	free_matrix(sphere_pos);
	free_matrix(sphere_color);
}
