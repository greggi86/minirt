/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rolandkaiser <rolandkaiser@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 21:46:44 by rolandkaise       #+#    #+#             */
/*   Updated: 2024/09/23 17:05:08 by rolandkaise      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int		parse_input(char **av)
{
	char 	*check;
	char	*line;
	int 	i;

	i = 0;

	line = get_next_line(open(av[1], O_RDONLY));
	
}

int	check_input(char **av, t_scene *scene)
{
	int	i;

	i = 0;
	while(*av[i])
	{
		if(av[i][0] == 'A')
		
	}
}