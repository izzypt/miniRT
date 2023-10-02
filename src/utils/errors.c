/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 16:47:20 by simao             #+#    #+#             */
/*   Updated: 2023/10/02 12:50:00 by simao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/**
 * @brief Displays an error message and exits the program. 
 * 
 * @param error the error message to display on the console.
 */
void	send_error(char *error)
{
    ft_putstr("\n", 2);
	ft_putstr("Error: ", 2);
	ft_putstr(error, 2);
	ft_putstr("\n", 2);
    exit(0);
}