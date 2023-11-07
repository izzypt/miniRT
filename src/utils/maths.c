/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 12:37:11 by simao             #+#    #+#             */
/*   Updated: 2023/11/07 17:03:47 by simao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/**
 * @brief Calculates and prints the current viewport angle.
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
	return (fov);
}

/**
 * @brief Defines the field of view.
 * @details Defines a width for the viewport that will end up 
 * creating the desired angle.
 * 
 * @param degrees The desired field of view in degrees.
 */
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
	calculate_fov();
}

/**
 * @brief Finds the angle between 2 vectors.
 * 
 * @param vector1 The first vector.
 * @param vector2 The second vector.
 */
float	angle_btwn_vectors(t_Vector vector1, t_Vector vector2)
{
	float	magnitude1;
	float	magnitude2;
	float	dot;
	float	radians;

	magnitude1 = vector_magnitude(vector1);
	magnitude2 = vector_magnitude(vector2);
	dot = dot_product(vector1, vector2);
	radians = (acos(dot / (magnitude1 * magnitude2)));
	return (radians);
}

/**
 * @brief Appplies rotation matrix to a vector and returns the result.
 * 
 * @param matrix The matrix.
 * @param vector2 The vector to apply the rotation matrix to.
 */
t_Vector	mult_mtrx_vector(t_RotMatrix *matrix, t_Vector vector)
{
	t_Vector	result;

	result.x = matrix->m[0][0] * vector.x + matrix->m[0][1] * \
	vector.y + matrix->m[0][2] * vector.z;
	result.y = matrix->m[1][0] * vector.x + matrix->m[1][1] * \
	vector.y + matrix->m[1][2] * vector.z;
	result.z = matrix->m[2][0] * vector.x + matrix->m[2][1] * \
	vector.y + matrix->m[2][2] * vector.z;
	return (result);
}

/**
 * @brief Creates a rotation matrix from the given axis and angle.
 * 
 * @param axis The axis we want to rotate around.
 * @param angle The angle between the two vectors from wich we want to rotate.
 */
t_RotMatrix	create_rot_matrix(t_Vector axis, float angle)
{
	t_RotMatrix	matrix;
	float		cos_theta;
	float		sin_theta;
	float		one_minus_cos_theta;

	cos_theta = cos(angle);
	sin_theta = sin(angle);
	one_minus_cos_theta = 1.0 - cos_theta;
	matrix.m[0][0] = cos_theta + axis.x * axis.x * one_minus_cos_theta;
	matrix.m[0][1] = axis.x * axis.y * one_minus_cos_theta - axis.z * sin_theta;
	matrix.m[0][2] = axis.x * axis.z * one_minus_cos_theta + axis.y * sin_theta;
	matrix.m[1][0] = axis.y * axis.x * one_minus_cos_theta + axis.z * sin_theta;
	matrix.m[1][1] = cos_theta + axis.y * axis.y * one_minus_cos_theta;
	matrix.m[1][2] = axis.y * axis.z * one_minus_cos_theta - axis.x * sin_theta;
	matrix.m[2][0] = axis.z * axis.x * one_minus_cos_theta - axis.y * sin_theta;
	matrix.m[2][1] = axis.z * axis.y * one_minus_cos_theta + axis.x * sin_theta;
	matrix.m[2][2] = cos_theta + axis.z * axis.z * one_minus_cos_theta;
	return (matrix);
}

/*t_Vector	rotate_x(t_Vector old, float angle)
{
	t_Vector	new;

	new.x = old.x;
	new.y = old.x * cos(angle) - old.z * sin(angle);
	new.z = old.y * sin(angle) + old.x * cos(angle);

	return (new);
}

t_Vector	rotate_y(t_Vector old, float  angle)
{
	t_Vector	new;

	new.x = old.z * sin(angle) + old.x * cos(angle);
	new.y = old.y;
	new.z = old.y * cos(angle) - old.x * sin(angle);

	return (new);
}

t_Vector	rotate_z(t_Vector old, float  angle)
{
	t_Vector	new;

	new.x = old.x * cos(angle) - old.y * sin(angle);
	new.y = old.x * sin(angle) + old.y * cos(angle);
	new.z = old.z;

	return (new);
}*/