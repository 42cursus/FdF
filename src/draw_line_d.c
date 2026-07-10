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

#include "ft_fdf.h"

static inline __attribute__((always_inline, used))
int	fdf_line_outside(t_img *img, t_point p1, t_point p2)
{
	int	outside;

	outside = (p1.x < 0) & (p2.x < 0);
	outside |= (p1.y < 0) & (p2.y < 0);
	outside |= (p1.x >= img->width) & (p2.x >= img->width);
	outside |= (p1.y >= img->height) & (p2.y >= img->height);
	return (outside);
}

static inline __attribute__((always_inline, used))
void	fdf_draw_pixel(t_fdf *fdf, t_point p)
{
	t_img	*img;

	img = fdf->canvas;
	if ((p.x < 0) || (p.y < 0) || (p.x >= img->width)
		|| (p.y >= img->height))
		return ;
	*(int *)(img->data + (img->size_line * p.y)
			+ (p.x * (img->bpp / 8))) = p.col;
}

static inline __attribute__((always_inline, used))
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

static inline __attribute__((always_inline, used))
void	fdf_advance_bres(t_point *p, t_bres *line)
{
	int	e2;
	int	move_x;
	int	move_y;

	e2 = line->err * 2;
	move_x = -(e2 > -line->dy);
	move_y = -(e2 < line->dx);
	line->err += (line->dx & move_y) - (line->dy & move_x);
	p->x += line->sx & move_x;
	p->y += line->sy & move_y;
}

void	draw_line_d(t_fdf *fdf, t_point p1, t_point p2)
{
	t_bres	line;
	int		col1;
	int		col2;
	int		step;

	if (fdf_line_outside(fdf->canvas, p1, p2))
		return ;
	line.dx = abs(p2.x - p1.x);
	line.dy = abs(p2.y - p1.y);
	line.sx = 1 - ((p1.x > p2.x) << 1);
	line.sy = 1 - ((p1.y > p2.y) << 1);
	line.err = line.dx - line.dy;
	line.steps = line.dx ^ ((line.dx ^ line.dy) & -(line.dx < line.dy));
	if (line.steps == 0)
		return (fdf_draw_pixel(fdf, p1));
	col1 = p1.col;
	col2 = p2.col;
	step = -1;
	while (++step <= line.steps)
	{
		p1.col = fdf_lerp_color(col1, col2, step, line.steps);
		fdf_draw_pixel(fdf, p1);
		fdf_advance_bres(&p1, &line);
	}
}
