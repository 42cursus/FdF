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
#include <errno.h>

t_cont	*ft_init_tab(int tab_size);
void	ft_draw_pix(t_fdf *fdf, t_cont *ptr);

void	ft_swap_xy(t_point *p)
{
	int	tmp;

	tmp = p->x;
	p->x = p->y;
	p->y = tmp;
}

t_cont	*ft_fdf_intep_d(t_fdf *fdf, t_point p1, t_point p2, int orientation)
{
	t_points	*res;
	t_point		p3;
	int			curr;
	int			inc;
	int			i;

	inc = 1;
	if (p2.x < p1.x)
		inc = -1;
	res = (t_points *) ft_init_tab(((p2.x - p1.x) * inc));
	curr = p1.x;
	i = -1;
	while (++i < res->size)
	{
		p3.y = curr;
		p3.x = p1.y + ((p2.y - p1.y) * (curr - p1.x)) / (p2.x - p1.x);
		p3.col = ft_fdf_get_color(p1, p2, curr);
		if (orientation == 0)
			ft_swap_xy(&p3);
		res->data[i] = p3;
		curr += inc;
	}
	return ((t_cont *)(res));
}

t_cont	*ft_init_tab(int tab_size)
{
	t_point	*tab;
	t_cont	*cont;

	tab = (t_point *)malloc(sizeof(t_point) * tab_size);
	if (!tab)
	{
		errno = ENOMEM;
		return (NULL);
	}
	cont = (t_cont *) malloc(sizeof(t_cont));
	if (!cont)
	{
		free(tab);
		errno = ENOMEM;
		return (NULL);
	}
	cont->data = tab;
	cont->size = tab_size;
	return (cont);
}

/**
 * How detect malloc failure?
 * 	https://stackoverflow.com/questions/6325940/
 */
void	draw_line_d(t_fdf *fdf, t_point p1, t_point p2)
{
	t_cont	*res;
	int		orientation;

	orientation = (abs(p2.x - p1.x) < abs(p2.y - p1.y));
	if (orientation)
		(ft_swap_xy(&p1), ft_swap_xy(&p2));
	if ((p2.x == p1.x) && (p2.y == p1.y))
	{
		res = ft_init_tab(1);
		*(t_point *)(res->data) = (t_point){.x = p1.x,
			.y = p2.y, .col = p2.col};
	}
	else
		res = ft_fdf_intep_d(fdf, p1, p2, orientation);
	ft_draw_pix(fdf, res);
}

/**
 * From the X11 protocol specification
 * (XYFormat):
 *	The data for a pixmap is said to be in XY format if it is organized as
 *	a set of bitmaps representing individual bit planes, with the planes
 *	appearing from most-significant to least-significant in bit order.
 *	Which means for an RGB image you have all the red channel data followed
 *	by the green and then blue instead of the more traditional
 *	RGB triplets (ZPixmap).
 * (ZFormat):
 * 	The data for a pixmap is said to be in Z format if it is organized as
 * 	a set of pixel values in scanline order.
 *	See:
 *		https://www.x.org/releases/X11R7.7/doc/xproto/x11protocol.html
 */

void	ft_draw_pix(t_fdf *fdf, t_cont *ptr)
{
	int		i;
	int		size;
	t_img	*img;
	t_point	p;
	t_point	*pts;

	img = fdf->canvas;
	size = ptr->size;
	pts = (t_point *) ptr->data;
	i = -1;
	while (++i < size)
	{
		p = pts[i];
		if ((p.x <= 0) || (p.y <= 0) || (p.x >= fdf->canvas->width)
			|| (p.y >= fdf->canvas->height))
			continue ;
		*(int *)(img->data + (img->size_line * p.y)
				+ (p.x * (img->bpp / 8))) = p.col;
	}
}
