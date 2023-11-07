/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validators2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 22:40:48 by simao             #+#    #+#             */
/*   Updated: 2023/11/07 23:03:22 by simao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/**
* @brief Chek if all the necessary values are present. It throws error if not
* @param line THe line to check if all the values are present
*/
void	validate_line_values(char **line)
{
	if ((!ft_strncmp(line[0], "sp", 2)) && (!line[1] || !line[2] || !line[3]))
		send_error("One or more sphere values are missing\n");
	if ((!ft_strncmp(line[0], "pl", 2)) && (!line[1] || !line[2] || !line[3]))
		send_error("One or more plane values are missing\n");
	if (!ft_strncmp(line[0], "cy", 2) && \
		(!line[1] || !line[2] || !line[3] || !line[4] || !line[5]))
		send_error("One or more plane values are missing\n");
}
