/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 16:47:20 by simao             #+#    #+#             */
/*   Updated: 2023/10/14 22:30:15 by simao            ###   ########.fr       */
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
	fov = ft_atof(line[3]);
	if (fov < 0 || fov > 180)
		send_error("Camera field of view must be between 0 and 180\n");
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

/**
 * @brief Extract and validate sphere values. 
 * 
 * @param **line a .rt file line splitted by spaces " " containing sphere data.
 */
void	parse_sphere(char **line)
{
	char		**sphere_pos;
	char		**sphere_color;
	t_Sphere	sphr;

	sphere_pos = ft_split(line[1], ',');
	if (!sphere_pos[0] || !sphere_pos[1] || !sphere_pos[2])
		send_error("Sphere center values must be provided in format: x,y,z\n");
	sphr.center.x = ft_atof(sphere_pos[0]);
	sphr.center.y = ft_atof(sphere_pos[1]);
	sphr.center.z = ft_atof(sphere_pos[2]);
	sphr.radius = ft_atof(line[2]) / 2;
	sphere_color = ft_split(line[3], ',');
	if (!sphere_color[0] || !sphere_color[1] || !sphere_color[2])
		send_error("Color values must be in format: R,G,B. range 0-255.\n");
	sphr.color.r = ft_atof(sphere_color[0]);
	sphr.color.g = ft_atof(sphere_color[1]);
	sphr.color.b = ft_atof(sphere_color[2]);
	validate_rgb_values(sphr.color.r, sphr.color.g, sphr.color.b);
	set_sphere(sphr.radius, sphr.center, sphr.color);
	free_matrix(sphere_pos);
	free_matrix(sphere_color);
}

/**
 * @brief Extract and validate plane values. 
 * 
 * @param **line a .rt file line splitted by spaces " " containing sphere data.
 */
void	parse_plane(char **line)
{
	char		**plane_point;
	char		**plane_normal;
	char		**plane_color;
	t_Plane		pln;

	plane_point = ft_split(line[1], ',');
	if (!plane_point[0] || !plane_point[1] || !plane_point[2])
		send_error("Plane point values must be provided in format: x,y,z\n");
	pln.point.x = ft_atof(plane_point[0]);
	pln.point.y = ft_atof(plane_point[1]);
	pln.point.z = ft_atof(plane_point[2]);
	plane_normal = ft_split(line[2], ',');
	if (!plane_normal[0] || !plane_normal[1] || !plane_normal[2])
		send_error("Plane normal values must be provided in format: x,y,z\n");
	pln.normal.x = ft_atof(plane_normal[0]);
	pln.normal.y = ft_atof(plane_normal[1]);
	pln.normal.z = ft_atof(plane_normal[2]);
	validate_normal_vector(pln.normal.x, pln.normal.y, pln.normal.z);
	plane_color = ft_split(line[3], ',');
	if (!plane_color[0] || !plane_color[1] || !plane_color[2])
		send_error("Color values must be in format: R,G,B. range 0-255.\n");
	pln.color.r = ft_atof(plane_color[0]);
	pln.color.g = ft_atof(plane_color[1]);
	pln.color.b = ft_atof(plane_color[2]);
	validate_rgb_values(pln.color.r, pln.color.g, pln.color.b);
	set_plane(pln.point, pln.normal, pln.color);
	free_matrix(plane_point);
	free_matrix(plane_normal);
	free_matrix(plane_color);
}

/**
 * @brief Extract and validate cylinder value. 
 * 
 * @param **line a .rt file line splitted by spaces " " containing cylinder data.
 */
void	parse_cylinder(char **line)
{
	char		**position;
	char		**color;
	char		**normal;
	t_Cylinder	cyl;

	position = ft_split(line[1], ',');
	if (!position[0] || !position[1] || !position[2])
		send_error("cylinder values must be provided in format: x,y,z\n");
	cyl.pos.x = ft_atof(position[0]);
	cyl.pos.y = ft_atof(position[1]);
	cyl.pos.z = ft_atof(position[2]);
	normal = ft_split(line[2], ',');
	if (!normal[0] || !normal[1] || !normal[2])
		send_error("cylinder normal must be provided in format: x,y,z\n");
	cyl.normal.x = ft_atof(normal[0]);
	cyl.normal.y = ft_atof(normal[1]);
	cyl.normal.z = ft_atof(normal[2]);
	cyl.radius = ft_atof(line[3]) / 2;
	cyl.height = ft_atof(line[4]);
	color = ft_split(line[5], ',');
	if (!color[0] || !color[1] || !color[2])
		send_error("Color values must be in format: R,G,B. range 0-255.\n");
	cyl.color.r = ft_atof(color[0]);
	cyl.color.g = ft_atof(color[1]);
	cyl.color.b = ft_atof(color[2]);
	validate_rgb_values(cyl.color.r, cyl.color.g, cyl.color.b);
	set_cylinder(cyl);
	free_matrix(color);
	free_matrix(position);
}
