/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmouty <thmouty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 19:14:49 by thmouty           #+#    #+#             */
/*   Updated: 2024/05/15 02:44:47 by thmouty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	draw_map(t_mlx *mlx)
{
	int		xy[2];
	t_point	*point_xy[2];

	xy[0] = -1;
	while (++xy[0] < mlx->map.lines)
	{
		xy[1] = -1;
		while (++xy[1] < mlx->map.columns)
		{
			point_xy[0] = convert_point(xy[1], xy[0], mlx);
			if (xy[1] + 1 < mlx->map.columns)
			{
				point_xy[1] = convert_point(xy[1] + 1, xy[0], mlx);
				draw_line(mlx, *point_xy[0], *point_xy[1]);
				free(point_xy[1]);
			}
			if (xy[0] + 1 < mlx->map.lines)
			{
				point_xy[1] = convert_point(xy[1], xy[0] + 1, mlx);
				draw_line(mlx, *point_xy[0], *point_xy[1]);
				free(point_xy[1]);
			}
			free(point_xy[0]);
		}
	}
}

void	draw_line(t_mlx *mlx, t_point a, t_point b)
{
	t_point	temp;
	double	ratio;

	if (a.y > b.y || (a.y == b.y && a.x > b.x))
	{
		temp = a;
		a = b;
		b = temp;
	}
	temp.y = a.y;
	while (temp.y <= b.y)
	{
		ratio = (double)(temp.y - a.y) / (b.y - a.y);
		temp.x = a.x + (b.x - a.x) * ratio;
		temp.z = a.z + (b.z - a.z) * ratio;
		temp.color = get_color(a, b, ratio);
		if (temp.x >= 0 && temp.x < mlx->width && temp.y >= 0
			&& temp.y < mlx->height)
			cpy_pixel(mlx, temp.x, temp.y, temp.color);
		temp.y++;
	}
}

void	cpy_pixel(t_mlx *mlx, int x, int y, int color)
{
	ft_memcpy(mlx->img_data + y * mlx->map.size_line + x
		* mlx->map.bits_per_pixel / 8, &color, mlx->map.bits_per_pixel / 8);
	if (mlx->map.lines > 100 || mlx->map.columns > 100)
		return ;
	ft_memcpy(mlx->img_data + y * mlx->map.size_line + (x + 1)
		* mlx->map.bits_per_pixel / 8, &color, mlx->map.bits_per_pixel / 8);
	ft_memcpy(mlx->img_data + (y + 1) * mlx->map.size_line + x
		* mlx->map.bits_per_pixel / 8, &color, mlx->map.bits_per_pixel / 8);
	ft_memcpy(mlx->img_data + (y + 1) * mlx->map.size_line + (x + 1)
		* mlx->map.bits_per_pixel / 8, &color, mlx->map.bits_per_pixel / 8);
}
