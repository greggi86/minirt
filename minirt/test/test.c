/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rolandkaiser <rolandkaiser@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:01:34 by rolandkaise       #+#    #+#             */
/*   Updated: 2024/09/29 13:40:50 by rolandkaise      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"



void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void create_cam(t_rt *rt,t_vecIII pos, t_vecIII look_at, float FOV, float aspect_ratio)
{
    t_vecIII    temp_up;
    t_vecIII    right;    
    rt->cam->pos = pos;
    rt->cam->dir = unit(vec_sub(look_at, pos));
    
    temp_up.x = 0;
    temp_up.y = 1;
    temp_up.z = 0;
    
    right = unit(xprod(rt->cam->dir, temp_up));
    
    rt->cam->up = unit(xprod(right, rt->cam->dir));

    rt->cam->fov = FOV;
    rt->cam->aspect_ratio = aspect_ratio;
}


t_ray create_ray(t_rt *rt, float u, float v)
{
    t_vecIII    ray_direction;
    t_ray       ray;
    
    float theta = rt->cam->fov * M_PI / 180;
    float half_height = tan(theta / 2);
    float half_width = rt->cam->aspect_ratio * half_height;
    
    rt->vport->w = neg_vec(rt->cam->dir);
    rt->vport->u_vec = unit(xprod(rt->cam->dir, rt->cam->up));
    rt->vport->v_vec = xprod(rt->vport->w, rt->vport->u_vec);
    rt->vport->lower_left_corner = vec_sub(rt->cam->pos, 
                                    vecIII_add(vec_smult(rt->vport->u_vec, half_width),
                                    vecIII_add(vec_smult(rt->vport->v_vec, half_height), rt->vport->w)));
    rt->vport->horizontal = vec_smult(rt->vport->u_vec, 2 * half_width);
    rt->vport->vertical = vec_smult(rt->vport->vertical, 2 * half_height);

    ray_direction = vecIII_add(rt->vport->lower_left_corner,
                                vecIII_add(vec_smult(rt->vport->horizontal, u),
                                vecIII_add(vec_smult(rt->vport->vertical, v),
                                neg_vec(rt->cam->pos))));
    ray.orgin = rt->cam->pos;
    ray.direction = unit(ray_direction);

    return (ray);
}


int main(void)
{
    t_rt *rt;
    rt->res_x = 1920;
    rt->res_y = 1080;
    rt->FOV = 70;
    
        
    create_cam(
        rt,
        vec_create(0.0f, 0.0f, -1.0f),
        vec_create(0.0f, 0.0f, 0.0f),
        90,
        ((float)(rt->res_x / rt->res_y))
    );
    //viewport height converts degrees to radians in the last clamp!
    
    for (int y = 0; y < rt->res_y; y++)
    {
        for (int x = 0; x < rt->res_x; x++)
        {
            float u = (float)x / (rt->res_x - 1);
            float v = (float)y / (rt->res_y - 1);
            t_ray ray = create_ray(&rt->cam, u, v);
        }    
    }
}



/*
int interp_color(int c1, int c2, int x, int xmax) {
    float t = (float)x / (float)xmax;
    float ti = (1.0 - t);
    int r1 = ((c1 >> 16) & 0xFF) * ti;
    int g1 = ((c1 >> 8) & 0xFF) * ti;
    int b1 = (c1 & 0xFF) * ti;
    int r2 = ((c2 >> 16) & 0xFF) * t;
    int g2 = ((c2 >> 8) & 0xFF) * t;
    int b2 = (c2 & 0xFF) * t;
    
    int a = r1 << 16 | g1 << 8 | b1;
    int b = r2 << 16 | g2 << 8 | b2;
    //printf("%f ", t);
    return a + b;
}


int	main(void)
{
    const int height = 1080;
    const int width = 1920;
    void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, width, height, "Hello world!");
	img.img = mlx_new_image(mlx, width, height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);

    const int yfrom = 300;
    const int yto = 600;
    int y = yfrom;
    int x = 0;
    int c1 = 0x00FFAAFF;
    int c2 = 0x00FF4400;
    while (y < yto)
    {
        x = 0;
        while(x < 1920)
        {
            if (y > yfrom && y < yto) {
                int c = interp_color(c1, c2, y - yfrom, yto - yfrom);
        	    my_mlx_pixel_put(&img, x, y, c);
            }
            x++;
        }
        y ++;
    }
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
*/