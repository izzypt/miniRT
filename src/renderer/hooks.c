/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 22:09:38 by simao             #+#    #+#             */
/*   Updated: 2023/10/09 15:57:41 by simao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/**
 * @brief Callback function for mlx_hook when 
 * you press 'X' button of the window top right corner.
 */
int	close_window(void)
{
	end_program();
	return (0);
}

/**
 * @brief Callback function for mlx?hook when you press ESC.
 * 
 * @param keycode The code of the key to be pressed.
 */
int	key_press(int keycode)
{
	if (keycode == 65307)
		end_program();
	if (keycode == KEY_D)
		camera()->pos.x += 0.5;
	if (keycode == KEY_A)
		camera()->pos.x -= 0.5;
	if (keycode == KEY_W)
		camera()->pos.z += 0.5;
	if (keycode == KEY_S)
		camera()->pos.z -= 0.5;
	if (keycode == ARROW_LEFT)
		camera()->dir.x -= 0.1;
	if (keycode == ARROW_RIGHT)
		camera()->dir.x += 0.1;
	if (keycode == ARROW_UP)
		camera()->dir.y += 0.1;
	if (keycode == ARROW_DOWN)
		camera()->dir.y -= 0.1;
	render();
	return (1);
}
