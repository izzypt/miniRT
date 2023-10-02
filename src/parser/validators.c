/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validators.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 16:47:20 by simao             #+#    #+#             */
/*   Updated: 2023/10/02 14:49:59 by simao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void    validate_rgb_values(int r, int g, int b)
{
	if (r > 255 || g > 255 || b > 255 || r < 0 || g < 0 || b < 0)
		send_error("Ambient lightning RGB colors must be between 0-255\n");
}

void    validate_normal_vector(int x, int y, int z)
{
	if (x > 1.0 || y > 1.0 || z > 1.0 || x < 0.0 || y < 0.0 || z < 0.0)
		send_error("Normal vectors must be between 0.0-1.0\n");
}
