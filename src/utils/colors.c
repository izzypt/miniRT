/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 16:47:20 by simao             #+#    #+#             */
/*   Updated: 2023/10/02 12:49:57 by simao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/*
 - Converts a given t_Color from rgb to hex.
 - Returns an int hex color.
*/
int	rgb_to_hex(t_Color color)
{
	int	hex_color;

	hex_color = ((int)color.r << 16) | ((int)color.g << 8) | (int)color.b;

	hex_color &= 0x00FFFFFF;

	return (hex_color);
}

/*
 - Converts a given int from hex to rgb.
 - Returns a rbg t_Color.
*/
t_Color	hex_to_rgb(int hex_color)
{
	t_Color	color;

	color.r = (hex_color >> 16) & 0xFF;
	color.g = (hex_color >> 8) & 0xFF;
	color.b = hex_color & 0xFF;

	return (color);
}

/*
 - Adds color1 and color2.
 - Max value is 255. 
 - Min value is 0.
 - Returns t_Color.
*/
t_Color	color_add(t_Color *color1, t_Color *color2)
{
	t_Color	result;

	result.r = color1->r + color2->r;
	result.g = color1->g + color2->g;
	result.b = color1->b + color2->b;
	if (result.r > 255)
		result.r = 255;
	if (result.r < 0)
		result.r = 0;
	if (result.g > 255)
		result.g = 255;
	if (result.g < 0)
		result.g = 0;
	if (result.b > 255)
		result.b = 255;
	if (result.b < 0)
		result.b = 0;
	return (result);
}

/*
 - Subtracts color1 and color2.
 - Max value is 255. 
 - Min value is 0.
 - Returns t_Color.
*/
t_Color	color_sub(t_Color *color1, t_Color *color2)
{
	t_Color	result;

	result.r = color1->r - color2->r;
	result.g = color1->g - color2->g;
	result.b = color1->b - color2->b;
	if (result.r > 255)
		result.r = 255;
	if (result.r < 0)
		result.r = 0;
	if (result.g > 255)
		result.g = 255;
	if (result.g < 0)
		result.g = 0;
	if (result.b > 255)
		result.b = 255;
	if (result.b < 0)
		result.b = 0;
	return (result);
}

/*
 - Multiplies color1 by num.
 - Max value is 255. 
 - Min value is 0.
 - Returns t_Color.
*/
t_Color	color_mult(t_Color *color1, float num)
{
	t_Color	result;

	result.r = color1->r * num;
	result.g = color1->g * num;
	result.b = color1->b * num;

	if (result.r > 255)
		result.r = 255;
	if (result.r < 0)
		result.r = 0;
	if (result.g > 255)
		result.g = 255;
	if (result.g < 0)
		result.g = 0;
	if (result.b > 255)
		result.b = 255;
	if (result.b < 0)
		result.b = 0;
	return (result);
}