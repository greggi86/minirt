/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rolandkaiser <rolandkaiser@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 12:56:59 by rolandkaise       #+#    #+#             */
/*   Updated: 2024/09/27 13:17:22 by rolandkaise      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "../mlx/mlx.h"


typedef struct s_vec
{
	double x;
	double y;
	double z;
}	t_vec;

typedef struct	s_img
{
	void			*ptr;
	char			*addr;
	int				bpp;
	int				size;
	int				endian;
}	t_img;

typedef struct s_obj
{
	float	x;
	float	y;
	float	z;
	float	diameter;
	float	brightness;
	float	norm_x;
	float	norm_y;
	float	norm_z;
	int		r;
	int		g;
	int		b;
}	t_obj;

typedef struct s_cam
{
	float	vp_x;
	float	vp_y;
	float	vp_z;
	float	ov_x;
	float	ov_y;
	float	ov_z;
	int		fov;
}	t_cam;

typedef struct s_al
{
	float	brightness;
	int		r;
	int		g;
	int		b;
}	t_al;

typedef struct s_chk
{
	int		A;
	int		L;
	int		C;
	int		R;
}	t_chk;

typedef	struct s_scene
{
	t_chk	*check;
	char	*line;
	t_al	*alight;
	t_obj	*sp;
	t_obj	*pl;
	t_obj	*cy;
	t_obj	*tr;
	t_obj	*light;
	t_cam	*cam;
}	t_scene;

typedef struct s_rt
{
	t_scene	*scene;
	int		*mlx;
	int		res_x;
	int		res_y;
	int		save;
}	t_rt;

////////////////// VECTOR_UTILS ////////////////////////////

double		vlength2III(t_vec vec);
double		vlengthIII(t_vec vec);

t_vec		vecIII_add(t_vec vec1, t_vec vec2);
t_vec		vecIII_sadd(t_vec vec, int x, int y, int z);

t_vec		vecIII_sub(t_vec vec1, t_vec vec2);
t_vec		vecIII_ssub(t_vec vec, int x, int y, int z);

t_vec		vecIII_div(t_vec vec1, t_vec vec2);
t_vec		vecIII_sdiv(t_vec vec, int x, int y, int z);

////////////////// PARSE ////////////////////////////

int			parse_input(char **av, t_scene *scene);

#endif