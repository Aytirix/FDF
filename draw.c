/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmouty <thmouty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 19:14:49 by thmouty           #+#    #+#             */
/*   Updated: 2024/05/15 04:05:20 by thmouty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	get_color(t_point a, t_point b, double ratio)
{
	int	color;
	int	r;
	int	g;
	int	bl;

	r = (a.color >> 16) + ((b.color >> 16) - (a.color >> 16)) * ratio;
	g = (a.color >> 8 & 0xFF) + ((b.color >> 8 & 0xFF) - (a.color >> 8 & 0xFF))
		* ratio;
	bl = (a.color & 0xFF) + ((b.color & 0xFF) - (a.color & 0xFF)) * ratio;
	color = r << 16 | g << 8 | bl;
	return (color);
}

t_point	*convert_point(int x, int y, t_mlx *mlx)
{
	t_point	*point;
	int		temp;

	point = (t_point *)malloc(sizeof(t_point));
	if (!point)
		stop(*mlx);
	point->z = mlx->map.numbers[y][x];
	if (point->z != 0)
		point->z = point->z / 5 + mlx->map.upper;
	point->z *= mlx->map.zoom;
	point->x = (x - mlx->map.columns / 2) * mlx->map.zoom;
	point->y = (y - mlx->map.lines / 2) * mlx->map.zoom;
	temp = iso_x(point->x, point->y);
	point->y = iso_y(point->x, point->y, point->z) + mlx->map.move_y
		+ mlx->height / 2;
	point->x = temp + mlx->map.move_x + mlx->width / 2;
	choice_color(x, y, mlx, point);
	return (point);
}

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

void	choice_color(int x, int y, t_mlx *mlx, t_point *point)
{
	if (mlx->map.numbers[y][x] == 0)
		point->color = 0x6a329f;
	else if (mlx->map.numbers[y][x] <= 10)
		point->color = 0xf1c232;
	else if (mlx->map.numbers[y][x] <= 20)
		point->color = 0x00FF00;
	else if (mlx->map.numbers[y][x] <= 30)
		point->color = 0xff8200;
	else
		point->color = 0x148feb;
}
