/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_unit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rolandkaiser <rolandkaiser@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:36:11 by rolandkaise       #+#    #+#             */
/*   Updated: 2024/09/23 16:41:31 by rolandkaise      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_vec	unit(t_vec vec)
{
	double length;

	length = vlengthIII(vec);
	if(length == 0)
	{
		printf("Error: The length of the vector is 0");
		exit (-1);
	}
	vec.x /= length;
	vec.y /= length;
	vec.z /= length;
	return (vec);
}