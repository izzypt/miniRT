/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simao <simao@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 22:33:12 by simao             #+#    #+#             */
/*   Updated: 2023/10/18 13:52:47 by simao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/**
 * @brief Performs the calculus to find the distance of the intersection points 
 * of a ray with a sphere.
 * @param O The origin of the ray.
 * @param D The direction of the ray.
 * @param t_min The minimum value of the distance (t).
 * @param t_max The maximum value of the distance (t).
 * @returns t_Intersection holding data about the closest intersection 
 * and the closest object we intersected with.
*/
t_Intersection	clst_intsct(t_Vector O, t_Vector D, float t_min, float t_max)
{
	t_Point			sphr_intrsct;
	t_Point			cyl_intrsct;
	float			pln_intsct;
	int				i;
	t_Intersection	inter;

	i = -1;
	inter.clst_t = INT_MAX;
	pln_intsct = INT_MAX;
	inter.clst_sphr = NULL;
	inter.clst_pln = NULL;
	inter.clst_cyl = NULL;
	while (++i < scene()->max_obj_count)
	{
		if (i < scene()->spheres_count)
			sphr_intrsct = intrscts_sphr(O, D, scene()->spheres[i]);
		if (i < scene()->plane_count)
			pln_intsct = intrscts_pln(O, D, scene()->planes[i]);
		if (i < scene()->cyl_count)
			cyl_intrsct = intrscts_cyl(O, D, scene()->cylinders[i]);
		if (sphr_intrsct.t1 < inter.clst_t && sphr_intrsct.t1 >= t_min \
			&& sphr_intrsct.t1 <= t_max)
		{
			inter.clst_t = sphr_intrsct.t1;
			inter.clst_sphr = &scene()->spheres[i];
		}
		if (sphr_intrsct.t2 < inter.clst_t && sphr_intrsct.t2 >= t_min \
			&& sphr_intrsct.t2 <= t_max)
		{
			inter.clst_t = sphr_intrsct.t2;
			inter.clst_sphr = &scene()->spheres[i];
		}
		if (pln_intsct < inter.clst_t && pln_intsct >= t_min && pln_intsct <= t_max)
		{
			inter.clst_t = pln_intsct;
			inter.clst_pln = &scene()->planes[i];
		}
		if (cyl_intrsct.t1 < inter.clst_t && cyl_intrsct.t1 >= t_min \
			&& cyl_intrsct.t1 <= t_max)
		{
			inter.clst_t = cyl_intrsct.t1;
			inter.clst_cyl = &scene()->cylinders[i];
		}
		if (cyl_intrsct.t2 < inter.clst_t && cyl_intrsct.t2 >= t_min \
			&& cyl_intrsct.t2 <= t_max)
		{
			inter.clst_t = cyl_intrsct.t2;
			inter.clst_cyl = &scene()->cylinders[i];
		}
	}
	return (inter);
}

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

	n = vector_sub(p, itsct.clst_cyl->pos);
	color = color_mult(itsct.clst_cyl->color, \
			calc_light(p, n, vector_mult(dt, -1), \
						itsct.clst_cyl->spec) \
			);
	return (color);
}

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
 * @brief Multiplies the color of the object by the cooeficient of light
 * @param itsct the intersection object
 * @param ray the ray vector we shot from the camera
 * @param p the point of intersection. It is the origin plus dt.
 * @param dt the direction of the ray times the distance of "t".
*/
t_Color	sphr_color(t_Intersection itsct, t_Vector ray, t_Vector p, t_Vector dt)
{
	t_Vector	n;

	n = vector_sub(p, itsct.clst_sphr->center);
	return (
		color_mult(itsct.clst_sphr->color, \
		calc_light(p, n, vector_mult(dt, -1), itsct.clst_sphr->spec)));
}

/*
 - Follows ray to the intersection point (clst_t).
 - Calculates the object normal.
 - Returns t_color of intersection point multiplied by light coefficient.
*/
t_Color	trace_ray(t_Vector ray, int t_min, int t_max)
{
	t_Intersection	itsct;
	t_Vector		p;
	t_Vector		dt;

	itsct = clst_intsct(camera()->pos, ray, t_min, t_max);
	dt = vector_mult(ray, itsct.clst_t);
	p = vector_add(camera()->pos, dt);
	if (itsct.clst_cyl != NULL)
		return (cyl_color(itsct, ray, p, dt));
	if (itsct.clst_pln != NULL)
		return (pln_color(itsct, ray, p, dt));
	if (itsct.clst_sphr != NULL)
		return (sphr_color(itsct, ray, p, dt));
	return (background_color(ray));
}

/**
 * @brief Performs the calculus to find the distance of the intersection points 
 * of a ray with a sphere.
 * @param O The origin of the ray.
 * @param D The direction of the ray.
 * @param sphere The sphere to intersect with.
 * @returns t_Point (t1 and t2). The intersection points.
*/
t_Point	intrscts_sphr(t_Vector O, t_Vector D, t_Sphere sphere)
{
	float		a;
	float		b;
	float		c;
	float		discriminant;
	t_Point		intersections;

	a = dot_product(D, D);
	b = 2 * dot_product(vector_sub(O, sphere.center), D);
	c = dot_product(vector_sub(O, sphere.center), \
	vector_sub(O, sphere.center)) - sphere.radius * sphere.radius;

	discriminant = b * b - 4.0f * a * c;
	intersections.t1 = (-b + sqrt(discriminant)) / (2 * a);
	intersections.t2 = (-b - sqrt(discriminant)) / (2 * a);
	if (discriminant < 0)
	{
		intersections.t1 = INT_MAX;
		intersections.t2 = INT_MAX;
	}
	return (intersections);
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
 * @brief Performs the calculus to find the distance of the intersection points 
 * of a ray with a cylinder.
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
