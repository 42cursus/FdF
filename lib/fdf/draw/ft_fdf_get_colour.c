/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf_get_colour.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 05:22:34 by abelov            #+#    #+#             */
/*   Updated: 2024/05/26 05:22:35 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf/fdf_lib.h>

t_rgb ft_fdf_int_to_color(int color)
{
	t_rgb col;

	col.r = color >> 16;
	col.g = (color >> 8) % 256;
	col.b = color % 256;
	return col;
}

t_rgb ft_fdf_get_colour(int x1, int color1, int color2, int curr_pos, int delta)
{
	t_rgb c;

	t_rgb c1 = ft_fdf_int_to_color(color1);
	t_rgb c2 = ft_fdf_int_to_color(color2);
	c.r = c1.r + (curr_pos - x1) * (c2.r - c1.r) / delta;
	c.g = c1.g + (curr_pos - x1) * (c2.g - c1.g) / delta;
	c.b = c1.b + (curr_pos - x1) * (c2.b - c1.b) / delta;
	return c;
}
