/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_sub.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rolandkaiser <rolandkaiser@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 15:37:40 by rolandkaise       #+#    #+#             */
/*   Updated: 2024/09/23 16:41:15 by rolandkaise      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_vec	vec_sub(t_vec vec, t_vec vec2)
{
	vec.x -= vec2.x;
	vec.y -= vec2.y;
	vec.z -= vec2.z;
	return (vec);	
}

t_vec	vec_ssub(t_vec vec, int x, int y, int z)
{
	vec.x -= x;
	vec.y -= y;
	vec.z -= z;
	return (vec);	
}