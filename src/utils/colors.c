/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 16:47:20 by simao             #+#    #+#             */
/*   Updated: 2023/10/08 17:12:49 by simao            ###   ########.fr       */
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

/**
 * @brief Converts a color from hexadecimal to RGB values..
 * 
 * @param int The color in hexadecimal value of int type.
 * @returns a t_Color type represented by red, green and blue values.
 */
t_Color	hex_to_rgb(int hex_color)
{
	t_Color	color;

	color.r = (hex_color >> 16) & 0xFF;
	color.g = (hex_color >> 8) & 0xFF;
	color.b = hex_color & 0xFF;

	return (color);
}

/**
 * @brief Adds two colors together and clamps the values between 0-255.
 * 
 * @param color1 The first color.
 * @param color2 The second color.
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

/**
 * @brief Substract color2 from color1. (color1 - color2)
 * and clamps the values between 0-255.
 * @param color1 The first color.
 * @param color2 The second color.
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

/**
 * @brief Multiplies color1 by num. (color1 * num)
 * and clamps the values between 0-255.
 * @param color1 The first color.
 * @param num The value to multiply by.
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
