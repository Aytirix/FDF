/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmouty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 22:53:21 by thmouty           #+#    #+#             */
/*   Updated: 2024/05/15 22:53:23 by thmouty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	clear_image(t_mlx *mlx)
{
	int	*image;
	int	i;

	image = (int *)mlx->img_data;
	i = 0;
	while (i < mlx->width * mlx->height)
	{
		image[i] = 0;
		i++;
	}
}

int	mlx_start(t_mlx *mlx, int reset, int draw)
{
	if (reset)
	{
		mlx->map.zoom = 1;
		mlx->map.toogle_map = 2;
		mlx->map.upper = 0;
		mlx->map.move_x = 0;
		mlx->map.move_y = 0;
	}
	if (draw)
	{
		clear_image(mlx);
		mlx_clear_window(mlx->mlx, mlx->win);
		draw_map(mlx);
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
		draw_menu(mlx);
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_mlx	mlx;

	mlx_start(&mlx, 1, 0);
	start(&mlx, av[1], ac, av);
	draw_map(&mlx);
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img, 0, 0);
	draw_menu(&mlx);
	mlx_loop(mlx.mlx);
	exit(0);
	return (0);
}
