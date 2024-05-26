/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf_get_colour.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 05:22:34 by abelov            #+#    #+#             */
/*   Updated: 2024/05/26 23:50:05 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf/fdf_lib.h>

t_rgb	ft_fdf_int_to_color(int color)
{
	t_rgb	col;

	col.r = color >> 16;
	col.g = (color >> 8) % 256;
	col.b = color % 256;
	return (col);
}

int	ft_fdf_get_color(t_point p1, t_point p2, int curr_pos)
{
	int		delta;
	t_rgb	c;
	t_rgb	c1;
	t_rgb	c2;

	delta = p2.x - p1.x;
	c1 = ft_fdf_int_to_color(p1.col);
	c2 = ft_fdf_int_to_color(p2.col);
	c.r = c1.r + (curr_pos - p1.x) * (c2.r - c1.r) / delta;
	c.g = c1.g + (curr_pos - p1.x) * (c2.g - c1.g) / delta;
	c.b = c1.b + (curr_pos - p1.x) * (c2.b - c1.b) / delta;
	return ((c.r << 16) | (c.g << 8) | c.b);
}
