/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 21:03:04 by simao             #+#    #+#             */
/*   Updated: 2023/10/17 21:04:40 by simao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/**
 * @brief Multiplies the color of the object by the cooeficient of light
 * @param itsct the intersection object
 * @param ray the ray vector we shot from the camera
 * @param p the point of intersection. It is the origin plus dt.
 * @param dt the direction of the ray times the distance of "t".
*/
t_Color	cyl_color(t_Intersection itsct, t_Vector ray, t_Vector p, t_Vector dt)
{
	t_Color		color;
	t_Vector	n;

	n = vector_sub(p, itsct.clst_cy->pos);
	color = color_mult(itsct.clst_cy->color, \
			calc_light(p, n, vector_mult(dt, -1), \
						itsct.clst_cy->spec) \
			);
	return (color);
}

/**
 * @brief Check if the intersection point lie within the cylinder height.
 * @param itsct The two intersections distance in a t_Point struct.
 * @param cy The cylinder structure containing data about the cylinder.
 * @param O The camera origin point.
 * @param D The ray direction.
*/
void	check_cy_height(t_Point *itsct, t_Cylinder cy, t_Vector O, t_Vector D)
{
	float		half_height;
	t_Vector	point1;
	t_Vector	point2;
	float		y1;
	float		y2;

	half_height = cy.height / 2.0;
	if (itsct->t1 != INT_MAX)
	{
		point1 = vector_add(O, vector_mult(D, itsct->t1));
		y1 = point1.y - cy.pos.y;
		if (y1 < -half_height || y1 > half_height)
			itsct->t1 = INT_MAX;
	}
	if (itsct->t2 != INT_MAX)
	{
		point2 = vector_add(O, vector_mult(D, itsct->t2));
		y2 = point2.y - cy.pos.y;
		if (y2 < -half_height || y2 > half_height)
			itsct->t2 = INT_MAX;
	}
}

/**
 * @brief Performs the calculus to find the distance at which the ray intersect
 * with a cylinder.
 * @param O The origin of the ray.
 * @param D The direction of the ray.
 * @param cylinder The cylinder to intersect with.
 * @returns t_Point (t1 and t2). The intersection points.
*/
t_Point	intrscts_cyl(t_Vector O, t_Vector D, t_Cylinder cylinder)
{
	float		a, b, c;
	t_Point		intersections;
	t_Vector	delta_p;
	float		discriminant;

	delta_p = vector_sub(O, cylinder.pos);
	a = dot_product(D, D) - pow(dot_product(D, cylinder.normal), 2);
	b = 2 * (dot_product(D, delta_p) \
	- dot_product(D, cylinder.normal) * dot_product(delta_p, cylinder.normal));
	c = dot_product(delta_p, delta_p) \
	- pow(dot_product(delta_p, cylinder.normal), 2) - pow(cylinder.radius, 2);

	discriminant = b * b - 4.0f * a * c;
	if (discriminant < 0)
	{
		intersections.t1 = INT_MAX;
		intersections.t2 = INT_MAX;
	}
	else
	{
		intersections.t1 = (-b + sqrt(discriminant)) / (2 * a);
		intersections.t2 = (-b - sqrt(discriminant)) / (2 * a);
	}
	check_cy_height(&intersections, cylinder, O, D);
	return (intersections);
}


