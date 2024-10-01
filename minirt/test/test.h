/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rolandkaiser <rolandkaiser@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 12:18:34 by rolandkaise       #+#    #+#             */
/*   Updated: 2024/10/01 16:31:30 by rolandkaise      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

#include "./mlx/mlx.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define MAX_OBJECTS = 10

typedef enum { SPHERE, PLANE } ObjectType;

typedef struct {
    ObjectType type;
    union {
        struct { t_vecIII center; float radius; } sphere;
        struct { t_vecIII point; t_vecIII normal; } plane;
    };
    t_vecIII color;
} Object;

typedef struct s_ray 
{
    t_vecIII    orgin;
    t_vecIII    direction;
}   t_ray;

typedef struct {
    t_vecIII center;
    float radius;
    t_vecIII color;
} Sphere;

typedef struct {
    t_vecIII ambient_color;
    float ambient_intensity;
} Light;

typedef struct s_vport
{
    float   viewport_width;
    float   viewport_height;
    t_vecIII    w;
    t_vecIII    u_vec;
    t_vecIII    v_vec;
    t_vecIII    lower_left_corner;
    t_vecIII    horizontal;
    t_vecIII    vertical;
}   t_vport;

typedef struct s_vecIII
{
    float   x;  x
    float   y;  y
    float   z;  z
}   t_vecIII;

typedef struct s_rt
{
	t_data	*scene;
    t_cam   *cam;
    t_vport *vport;
    Object  object[MAX_OBJECTS];
    int     obj_count;
    int     lght_count;
	int		*mlx;
	int		res_x;
	int		res_y;
	int		save;
}	t_rt;


typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_cam
{
    t_vecIII      pos;
    t_vecIII      dir;
    t_vecIII      up;
    float       fov;
    float       aspect_ratio;
}   t_cam;


//vec_add.c
t_vecIII	vecIII_add(t_vecIII vec1, t_vecIII vec2);
t_vecIII	vecIII_sadd(t_vecIII vec, int x, int y, int z);
//vec_div.c
t_vecIII	vec_sdiv(t_vecIII vec, int t);
//vec_dprod
double	    dprodIII(t_vecIII vec);
//vec_mag
double		vlength2III(t_vecIII vec);
double		vlengthIII(t_vecIII vec);
//vec_mult
t_vecIII	vec_mult(t_vecIII vec1, t_vecIII vec2);
t_vecIII	vec_smult(t_vecIII vec, int t);
//vec_neg
t_vecIII	neg_vec(t_vecIII vec);
//vec_sub
t_vecIII	vec_sub(t_vecIII vec, t_vecIII vec2);
t_vecIII	vec_ssub(t_vecIII vec, int x, int y, int z);
//vec_unit
t_vecIII	unit(t_vecIII vec);
//vec_xprod
t_vecIII	xprod(t_vecIII vec, t_vecIII vec2);
//vec_create
t_vecIII	vec_create(float x, float y, float z);



#endif