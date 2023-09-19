/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 22:46:50 by simao             #+#    #+#             */
/*   Updated: 2023/09/19 19:42:18 by simao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minirt.h"
/*
 - Converts canvas coordinates into viewport coordinates.
 - Stores them in raydir.
*/
void	canvas_to_viewport(int x, int y, t_Vector *ray_dir)
{
	ray_dir->x = x * ((float)viewport()->width / (float)canvas()->width);
	ray_dir->y = y * ((float)viewport()->height / (float)canvas()->height);
	ray_dir->z = 2;
}
