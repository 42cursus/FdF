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

#include <ft_fdf.h>

typedef struct s_fdd_colour
{
	int r;
	int g;
	int b;
}	t_rgb;

t_rgb int_to_color(int color)
{
	t_rgb colour;

	colour.r = color >> 16;
	colour.g = (color >> 8) % 256;
	colour.b = color % 256;
	return colour;
}


void sub_draw_line_d(t_fdf *fdf, int x1, int y1, int x2, int y2,
					 int color1, int color2, int orientation)
{
	int colour;
	int curr_pos;
	int neg;
	int delta = x2 - x1;

	t_rgb c;
	t_rgb c1;
	t_rgb c2;

	c1 = int_to_color(color1);
	c2 = int_to_color(color2);

	neg = 1;
	if (x2 < x1)
		neg = -1;
	curr_pos = x1;
	while (curr_pos * neg <= x2 * neg) {
		c.r = c1.r + (curr_pos - x1) * (c2.r - c1.r) / delta;
		c.g = c1.g + (curr_pos - x1) * (c2.g - c1.g) / delta;
		c.b = c1.b + (curr_pos - x1) * (c2.b - c1.b) / delta;
		colour = (c.r << 16) | (c.g << 8) | c.b;
		int x = y1 + ((y2 - y1) * (curr_pos - x1)) / (x2 - x1);
		if (orientation == 0)
			mlx_pixel_put(fdf->mlx, fdf->main_win,
						  x, curr_pos,
						  colour);
		else
			mlx_pixel_put(fdf->mlx, fdf->main_win, curr_pos,
						  x, colour);
		curr_pos = neg + curr_pos;
	}
}

void draw_line_d(t_fdf *fdf, int x1, int y1, int x2, int y2, int color1,
				 int color2) {
	int y_diff;
	int x_diff;

	x_diff = x2 - x1;
	y_diff = y2 - y1;
	if (x2 - x1 < 0)
		x_diff = -(x2 - x1);
	if (y2 - y1 < 0)
		y_diff = -(y2 - y1);
	if (x_diff < y_diff)
		sub_draw_line_d(fdf, y1, x1, y2, x2, color1, color2, 0);
	else if ((x1 == x2) && (y1 == y2))
		mlx_pixel_put(fdf->mlx, fdf->main_win, x1, y2, color2);
	else
		sub_draw_line_d(fdf, x1, y1, x2, y2, color1, color2, 1);
}
