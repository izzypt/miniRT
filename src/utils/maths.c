/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 12:37:11 by simao             #+#    #+#             */
/*   Updated: 2023/10/07 12:20:06 by simao            ###   ########.fr       */
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
	printf("Redefining viewport:\nNew Width: %f\n", viewport()->width);
	calculate_fov();
}

t_RotMatrix	CreateRotationMatrix(float angle_x, float angle_y, float angle_z)
{
	t_RotMatrix	matrix;

	float cos_x = cos(angle_x);
	float sin_x = sin(angle_x);
	float cos_y = cos(angle_y);
	float sin_y = sin(angle_y);
	float cos_z = cos(angle_z);
	float sin_z = sin(angle_z);

	matrix.m[0][0] = cos_y * cos_z;
	matrix.m[0][1] = -cos_x * sin_z + sin_x * sin_y * cos_z;
	matrix.m[0][2] = sin_x * sin_z + cos_x * sin_y * cos_z;

	matrix.m[1][0] = cos_y * sin_z;
	matrix.m[1][1] = cos_x * cos_z + sin_x * sin_y * sin_z;
	matrix.m[1][2] = -sin_x * cos_z + cos_x * sin_y * sin_z;

	matrix.m[2][0] = -sin_y;
	matrix.m[2][1] = sin_x * cos_y;
	matrix.m[2][2] = cos_x * cos_y;

	return (matrix);
}

t_Vector	MultiplyMatrixVector(t_RotMatrix *matrix, t_Vector vector)
{
	t_Vector	result;

	result.x = matrix->m[0][0] * vector.x + matrix->m[0][1] * vector.y + matrix->m[0][2] * vector.z;
	result.y = matrix->m[1][0] * vector.x + matrix->m[1][1] * vector.y + matrix->m[1][2] * vector.z;
	result.z = matrix->m[2][0] * vector.x + matrix->m[2][1] * vector.y + matrix->m[2][2] * vector.z;

	return (result);
}

t_RotMatrix	matrixFromVector(t_Vector *vector)
{
	t_RotMatrix	matrix;

    float cos_theta = cos(acos(vector->z)); // Cosine of the angle between the input vector and the positive z-axis
    float sin_theta = sin(acos(vector->z)); // Sine of the angle
    
    if (fabs(1.0 - cos_theta) < 1e-6) {
        // Special case when the input vector is aligned with the positive z-axis
        matrix.m[0][0] = 1.0;
        matrix.m[0][1] = 0.0;
        matrix.m[0][2] = 0.0;

        matrix.m[1][0] = 0.0;
        matrix.m[1][1] = 1.0;
        matrix.m[1][2] = 0.0;

        matrix.m[2][0] = 0.0;
        matrix.m[2][1] = 0.0;
        matrix.m[2][2] = 1.0;
    } else {
        // General case
        float one_minus_cos = 1.0 - cos_theta;
        
		matrix.m[0][0] = cos_theta + vector->x * vector->x * one_minus_cos;
		matrix.m[0][1] = vector->x * vector->y * one_minus_cos - vector->z * sin_theta;
		matrix.m[0][2] = vector->x * vector->z * one_minus_cos + vector->y * sin_theta;

		matrix.m[1][0] = vector->y * vector->x * one_minus_cos + vector->z * sin_theta;
		matrix.m[1][1] = cos_theta + vector->y * vector->y * one_minus_cos;
		matrix.m[1][2] = vector->y * vector->z * one_minus_cos - vector->x * sin_theta;

		matrix.m[2][0] = vector->z * vector->x * one_minus_cos - vector->y * sin_theta;
		matrix.m[2][1] = vector->z * vector->y * one_minus_cos + vector->x * sin_theta;
		matrix.m[2][2] = cos_theta + vector->z * vector->z * one_minus_cos;
    }

    return matrix;
}
