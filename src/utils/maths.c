/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 12:37:11 by simao             #+#    #+#             */
/*   Updated: 2023/10/02 12:51:11 by simao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/*
 - Calculates viewport field of view in degrees.

*/
float	calculate_fov(void)
{
	float	hipo;
	float	sine;
	float	fov;

	hipo = sqrt(pow(viewport()->width / 2, 2) \
				+ pow(viewport()->dist, 2));
	sine = (viewport()->width / 2) / hipo;
	fov = (asin(sine) * 2) * 180 / PI;

	printf("Viewport fov is %f\n", fov);
	return (fov);
}

void	set_fov(float degrees)
{
	float	radians;

	if (degrees < 0 || degrees > 180)
	{
		ft_printf("Invalid degrees. Valid range is between 0 and 180.\n");
		return ;
	}
	radians = (degrees * (PI / 180)) / 2;
	viewport()->width = (tan(radians) * viewport()->dist) * 2;
	viewport()->height = viewport()->width / viewport()->aspect_ratio;
	printf("Redefining viewport:\nNew Width: %f\n", viewport()->width);
	calculate_fov();
}

