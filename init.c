/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 22:09:38 by simao             #+#    #+#             */
/*   Updated: 2023/09/20 15:11:21 by simao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minirt.h"

void	init_values(void)
{
	canvas()->width = 1920;
	canvas()->height = 1080;
	viewport()->width = 1;
	viewport()->height = 1;
	viewport()->dist = 1;
	viewport()->aspect_ratio = (float)16 / (float)9;
	camera()->x = 0;
	camera()->y = 0;
	camera()->z = -5;
	sphere()->radius = 0.5;
	sphere()->coord.x = 0;
	sphere()->coord.y = 0;
	sphere()->coord.z = 0;
	sphere()->color = 0x964000;
}
