/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_colour.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 23:59:00 by abelov            #+#    #+#             */
/*   Updated: 2026/07/10 23:59:00 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

int	fdf_lerp_color(int col1, int col2, int step, int steps)
{
	t_rgb	c;
	t_rgb	c1;
	t_rgb	c2;

	c1.r = (col1 >> FDF_RGB_RED_SHIFT) % FDF_RGB_MODULO;
	c1.g = (col1 >> FDF_RGB_GREEN_SHIFT) % FDF_RGB_MODULO;
	c1.b = col1 % FDF_RGB_MODULO;
	c2.r = (col2 >> FDF_RGB_RED_SHIFT) % FDF_RGB_MODULO;
	c2.g = (col2 >> FDF_RGB_GREEN_SHIFT) % FDF_RGB_MODULO;
	c2.b = col2 % FDF_RGB_MODULO;
	c.r = c1.r + ((long)step * (c2.r - c1.r)) / steps;
	c.g = c1.g + ((long)step * (c2.g - c1.g)) / steps;
	c.b = c1.b + ((long)step * (c2.b - c1.b)) / steps;
	return ((c.r << FDF_RGB_RED_SHIFT) | (c.g << FDF_RGB_GREEN_SHIFT) | c.b);
}
