/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rolandkaiser <rolandkaiser@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 14:15:02 by rolandkaise       #+#    #+#             */
/*   Updated: 2024/09/29 18:35:33 by rolandkaise      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"


void	add_sphere(t_vecIII center, float r, t_vecIII color, t_rt *rt)
{
	if (rt->obj_count < MAX_OBJECTS)
	{
		rt->object[rt->obj_count].type = SPHERE;
		rt->object[rt->obj_count].sphere.radius = r;
		rt->object[rt->obj_count].sphere.center = center;
		rt->object[rt->obj_count].color = color;
		rt->obj_count++;
	}
	
}

void	add_plane(t_vecIII point, t_vecIII normal, t_vecIII color, t_rt *rt)
{
	if (rt->obj_count < MAX_OBJECTS)
	{
		rt->object[rt->obj_count].type = PLANE;
		rt->object[rt->obj_count].plane.point = point;
		rt->object[rt->obj_count].plane.normal = normal;
		rt->obj_count++;
	}
}


void	create_cam(t_cam *camera, t_vecIII pos, t_vecIII look_at, float FOV, float aspect_ratio)
{
	t_vecIII	temp_up;
	t_vecIII	right;
	
	camera->pos = pos;
	camera->fov = FOV;
	camera->pos = unit(vec_sub(look_at, pos));
	temp_up = vec_create(0, 1, 0);
	right = unit(xprod(camera->dir, temp_up));
	camera->up = unit(xprod(right, camera->dir));
	camera->fov = FOV;
	camera->aspect_ratio = aspect_ratio;
}


int main(void)
{
	t_rt *rt;

	rt->obj_count = 0;
	rt->lght_count = 0;
	rt->res_x = 1920;
	rt->res_y = 1080;

	create_cam(rt->cam, vec_create(0, 0, 0), vec_create(0, 0, -1), 90, (rt->res_x / rt->res_y));
	add_plane(vec_create(0, -1, 0), vec_create(0, 1, 0), vec_create(0.5, 0.5, 0.5), rt);
	add_sphere(vec_create(0, 0, -3), vec_create())
}