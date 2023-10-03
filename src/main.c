/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 13:55:50 by smagalha          #+#    #+#             */
/*   Updated: 2023/10/03 17:16:58 by simao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

int	main(int argc, char **argv)
{

	if (argc != 2)
		send_error("Please provide only a .rt file as program input\n");
	init_windows();
	parse_file(argv);
	render();
	mlx_loop(mlibx()->mlx);
	return (1);
}
