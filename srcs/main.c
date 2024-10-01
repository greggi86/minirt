/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rolandkaiser <rolandkaiser@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 21:14:45 by rolandkaise       #+#    #+#             */
/*   Updated: 2024/09/23 16:50:24 by rolandkaise      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int main(int ac, char **av)
{
	t_rt	rt;

	
	
	if(ac == 2 || ac == 3)
	{
		parse_input(&av[1], rt.scene);
		//check_input();
	}
	return (0);
}