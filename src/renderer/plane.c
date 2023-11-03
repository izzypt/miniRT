/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:34:54 by simao             #+#    #+#             */
/*   Updated: 2023/10/19 15:53:23 by simao            ###   ########.fr       */
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
t_Color	pln_color(t_Intersection itsct, t_Vector ray, t_Vector p, t_Vector dt)
{
	t_Color		color;

	color = color_mult(itsct.clst_pln->color, \
			calc_light(p, itsct.clst_pln->normal, \
			vector_mult(dt, -1), itsct.clst_pln->spec));
	return (color);
}

/**
 * @brief Checks for intersections with a plane.
 * @param nmal The normal of the plane.
 * @param plan_p A point on the plane.
 * @param D the direction of the ray.
 * @returns Returns a float with the intersection points, if any.
 * @note The equation of the plane is ```(p - a) * n = 0``` , where:
 * @note ```a``` is a point on the plane
 * @note ```n``` is the normal of the plane. 
 * @note ```P``` is the point we are testing for intersection with the plane.
 * @note ``` ```
 * @note In order for ```P``` to intersect with the plane, 
 * the vector from ```a``` to ```P``` has to be perpendicular to ```n```.
 * @note i.e , the dot product of vector from ```a``` to ```P``` and ```n``` 
 * has to be zero.
*/
float	intrscts_pln(t_Vector O, t_Vector D, t_Plane pln)
{
	t_Vector	planetoorigin;
	float		denom;
	float		t;

	t = (float)INT_MAX;
	denom = dot_product(pln.normal, D);
	if (fabs(denom) > 0.001)
	{
		planetoorigin = vector_sub(pln.point, O);
		t = dot_product(planetoorigin, pln.normal) / denom;
		if (t < 0)
			t = INT_MAX;
		return (t);
	}
	return (t);
}
