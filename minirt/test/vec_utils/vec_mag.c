/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_mag.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rolandkaiser <rolandkaiser@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:29:31 by rolandkaise       #+#    #+#             */
/*   Updated: 2024/09/22 21:43:18 by rolandkaise      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

double		vlength2III(t_vec vec)
{
	return (vec.x * vec.x + vec.y * vec.y + vec.z + vec.z);
}

double		vlengthIII(t_vec vec)
{	
	return (sqrt(vlength2III(vec)));
}