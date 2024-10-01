/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_xprod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rolandkaiser <rolandkaiser@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:46:45 by rolandkaise       #+#    #+#             */
/*   Updated: 2024/09/23 16:41:38 by rolandkaise      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_vec		xprod(t_vec vec, t_vec vec2)
{
	t_vec	new;
	
	new.x = vec.y * vec2.z - vec2.y * vec.z;
	new.y = vec.x * vec2.z - vec2.x * vec.z;
	new.z = vec.x * vec2.y - vec2.x * vec.y;
	
	return (new);
}