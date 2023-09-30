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

void	end_file(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (i != 0)
		buffer[i] = '\0';
}

int	line_info(char *buffer)
{
	char	**line;

	end_file(buffer);
	line = ft_split(buffer, ' ');
	if (!line)
		return (0);
	if (!ft_strncmp(line[0], "C", 1) || ft_strncmp(line[0], "A", 1) || !ft_strncmp(line[0], "L", 1) || !ft_strncmp(line[0], "sp", 2) )
	{
		printf("Value of line(0) is %s\n", line[0]);
		printf("Value of line(0) is valid\n");
	}
	else
		printf("Value of line(0) is invalid : %s\n", line[0]);
	free_matrix(line);
	return (1);
}

int	valid_file(char *file)
{
	int	i;

	i = 0;
	while (file[i])
		i++;
	if (file[i - 3] == '.' && file[i - 2] == 'r' && file[i - 1] == 't')
		return (1);
	return (0);
}

int	parse_file(char **argv)
{
	int		fd;
	char	*buffer;

    if (!argv[1] || argv[2])
        send_error("Please provide only a .rt file as program input\n");
	fd = open(argv[1], O_RDONLY);
	if (valid_file(argv[1]) == 0 || fd == -1)
	{
		send_error("Please provice a .rt file");
		close(fd);
		return (0);
	}
	buffer = get_next_line(fd);
	while (buffer)
	{
       if (!line_info(buffer))
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