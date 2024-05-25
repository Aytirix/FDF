/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmouty <thmouty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 03:06:01 by thmouty           #+#    #+#             */
/*   Updated: 2024/05/15 03:50:42 by thmouty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	init_hook(t_mlx *mlx)
{
	mlx_key_hook(mlx->win, key_hook, mlx);
	mlx_mouse_hook(mlx->win, mouse_hook, mlx);
	mlx_hook(mlx->win, 17, 0, close_window, mlx);
	return (0);
}

int	key_hook(int key, t_mlx *mlx)
{
	if (key == ESC)
	{
		ft_printf("Key ESC pressed\n");
		stop(*mlx);
	}
	else if (key == R)
		return (mlx_start(mlx, 1, 1));
	else if (key == U)
		mlx->map.upper += 2;
	else if (key == J)
		mlx->map.upper -= 2;
	else
		return (key_hook2(key, mlx));
	return (mlx_start(mlx, 0, 1));
}

int	key_hook2(int key, t_mlx *mlx)
{
	if (key == A || key == LEFT)
		mlx->map.move_x -= 50;
	else if (key == D || key == RIGHT)
		mlx->map.move_x += 50;
	else if (key == W || key == UP)
		mlx->map.move_y -= 50;
	else if (key == S || key == DOWN)
		mlx->map.move_y += 50;
	else
		return (1);
	return (mlx_start(mlx, 0, 1));
}

// souris
int	mouse_hook(int button, int x, int y, t_mlx *mlx)
{
	(void)x;
	(void)y;
	if (button == SCROLL_UP)
		mlx->map.zoom += 4;
	else if (button == SCROLL_DOWN && mlx->map.zoom - 4 > 0)
		mlx->map.zoom -= 4;
	else
		return (0);
	mlx_start(mlx, 0, 1);
	return (0);
}

int	close_window(t_mlx *mlx)
{
	ft_printf("Window closed\n");
	stop(*mlx);
	return (0);
}
