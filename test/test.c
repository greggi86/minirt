/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rolandkaiser <rolandkaiser@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:01:34 by rolandkaise       #+#    #+#             */
/*   Updated: 2024/09/23 18:15:57 by rolandkaise      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mlx/mlx.h"
#include <stdlib.h>

int main(void)
{
    void	*mlx_ptr;

    mlx_ptr = mlx_init();
    //mlx_destroy_display(mlx_ptr);
    free(mlx_ptr);
}