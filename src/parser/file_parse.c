/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 16:47:20 by simao             #+#    #+#             */
/*   Updated: 2023/10/02 14:03:02 by simao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/**
 * @brief Redirects the given line according to the identifier to the correct parser function.
 * 
 * @param **line a .rt file line splitted by spaces " "
 */
void	redirect_line(char **line)
{
	static int num_of_spheres;
	//static int num_of_planes;
	//static int num_of_cylinder;

	if (!ft_strncmp(line[0], "C", 1)) 
		parse_camera(line);
	if (!ft_strncmp(line[0], "A", 1)) 
		parse_ambient(line);
	if (!ft_strncmp(line[0], "L", 1))
		parse_light(line);
	if (!ft_strncmp(line[0], "sp", 2))
	{
		parse_sphere(line);
		num_of_spheres++;
	}
	/*if (!ft_strncmp(line[0], "pl", 2))
	{
		parse_plane();
		num_of_planes++;
	}
	if (!ft_strncmp(line[0], "cy", 2))
	{
		parse_cylinder();
		num_of_cylinder++;
	}*/
}

/**
 * @brief Sets the end of every line to '\0'
 * 
 * @param buffer the line to which we set a null terminator.
 */
void	end_file(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (i != 0)
		buffer[i] = '\0';
}

/**
 * @brief Check if the line has one of the valid identifiers from the subject.
 * 
 * @param buffer the line read by get_next_line
 */
int	check_line_identifier(char *buffer)
{
	char	**line;

	end_file(buffer);
	line = ft_split(buffer, ' ');
	if (!line)
		return (0);
	if (!ft_strncmp(line[0], "C", 1) || !ft_strncmp(line[0], "A", 1) || !ft_strncmp(line[0], "L", 1) || !ft_strncmp(line[0], "sp", 2) )
		redirect_line(line);
	else
		send_error("The valid identifiers are :\n - A \n - C \n - L \n - sp \n - pl \n - cy\n");
	free_matrix(line);
	return (1);
}

/**
 * @brief Check if the file is the right type and extension : .rt
 * 
 * @param file the file name 
 */
int	valid_file_extension(char *file)
{
	int	i;

	i = 0;
	while (file[i])
		i++;
	if (file[i - 3] == '.' && file[i - 2] == 'r' && file[i - 1] == 't')
		return (1);
	return (0);
}

/**
 * @brief Check if file name is valid and read line after line
 * 
 * @param argv 
 */
int	parse_file(char **argv)
{
	int		fd;
	char	*buffer;

	fd = open(argv[1], O_RDONLY);
	if (valid_file_extension(argv[1]) == 0 || fd == -1)
	{
		close(fd);
		send_error("Please provice a .rt file");
	}
	buffer = get_next_line(fd);
	while (buffer)
	{
       if (!check_line_identifier(buffer))
		{
			free(buffer);
			close(fd);
			return (0);
		}
		free(buffer);
		buffer = get_next_line(fd);
	}
	free(buffer);
	close(fd);
	return (1);
}