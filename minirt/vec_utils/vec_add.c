/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rolandkaiser <rolandkaiser@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 12:56:11 by rolandkaise       #+#    #+#             */
/*   Updated: 2024/09/23 16:39:42 by rolandkaise      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_vec		vecIII_add(t_vec vec1, t_vec vec2)
{
	vec1.x += vec2.x;
	vec1.y += vec2.y;
	vec1.z += vec2.z;
	return (vec1);	
}

t_vec		vecIII_sadd(t_vec vec, int x, int y, int z)
{
	vec.x += x;
	vec.y += y;
	vec.z += z;
	return (vec);	
}