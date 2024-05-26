/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line_d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 03:13:26 by abelov            #+#    #+#             */
/*   Updated: 2024/05/25 03:13:27 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf/fdf_lib.h>
#include <ft_fdf.h>

void sub_draw_line_d(t_fdf *fdf, t_point p1, t_point p2, int orientation)
{
	int colour;
	int curr_pos;
	int neg;
	int delta = p2.x - p1.x;

	neg = 1;
	if (p2.x < p1.x)
		neg = -1;
	curr_pos = p1.x;
	while (curr_pos * neg <= p2.x * neg)
	{
		t_rgb c = ft_fdf_get_colour(p1.x, p1.col, p2.col, curr_pos, delta);
		colour = (c.r << 16) | (c.g << 8) | c.b;
		int x = p1.y + ((p2.y - p1.y) * (curr_pos - p1.x)) / (p2.x - p1.x);
		if (orientation == 0)
			mlx_pixel_put(fdf->mlx, fdf->main_win, x, curr_pos,
						  colour);
		else
			mlx_pixel_put(fdf->mlx, fdf->main_win, curr_pos, x,
						  colour);
		curr_pos = neg + curr_pos;
	}
}

void ft_swap_xy(t_point *p)
{
	int tmp;

	tmp = p->x;
	p->x = p->y;
	p->y = tmp;
}

void draw_line_d(t_fdf *fdf, t_point p1, t_point p2)
{
	int y_diff;
	int x_diff;
	int orient = 1;

	x_diff = p2.x - p1.x;
	y_diff = p2.y - p1.y;

	if (x_diff < 0)
		x_diff *= -1;
	if (y_diff < 0)
		y_diff *= -1;
	if (x_diff == 0 && y_diff == 0) /*  */
		mlx_pixel_put(fdf->mlx, fdf->main_win, p1.x, p2.y, p2.col);
	else {
		if (x_diff >= y_diff) {
			sub_draw_line_d(fdf, p1, p2, orient);
		} else {
			orient = 0;
			ft_swap_xy(&p1);
			ft_swap_xy(&p2);
			sub_draw_line_d(fdf, p1, p2, orient);
		}

	}
}
