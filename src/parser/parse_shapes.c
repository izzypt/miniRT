/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shapes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:13:10 by simao             #+#    #+#             */
/*   Updated: 2023/11/03 15:13:28 by simao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

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
	plane_normal = ft_split(line[2], ',');
	plane_color = ft_split(line[3], ',');
	validate_plane_values(plane_point, plane_normal, plane_color);
	pln.point.x = ft_atof(plane_point[0]);
	pln.point.y = ft_atof(plane_point[1]);
	pln.point.z = ft_atof(plane_point[2]);
	pln.normal.x = ft_atof(plane_normal[0]);
	pln.normal.y = ft_atof(plane_normal[1]);
	pln.normal.z = ft_atof(plane_normal[2]);
	validate_normal_vector(pln.normal.x, pln.normal.y, pln.normal.z);
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
	normal = ft_split(line[2], ',');
	color = ft_split(line[5], ',');
	validate_cyl_values(position, normal, color);
	cyl.pos.x = ft_atof(position[0]);
	cyl.pos.y = ft_atof(position[1]);
	cyl.pos.z = ft_atof(position[2]);
	cyl.normal.x = ft_atof(normal[0]);
	cyl.normal.y = ft_atof(normal[1]);
	cyl.normal.z = ft_atof(normal[2]);
	cyl.radius = ft_atof(line[3]) / 2;
	cyl.height = ft_atof(line[4]);
	cyl.color.r = ft_atof(color[0]);
	cyl.color.g = ft_atof(color[1]);
	cyl.color.b = ft_atof(color[2]);
	validate_rgb_values(cyl.color.r, cyl.color.g, cyl.color.b);
	set_cylinder(cyl);
	free_matrix(color);
	free_matrix(position);
}
