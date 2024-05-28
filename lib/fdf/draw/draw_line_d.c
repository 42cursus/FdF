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

t_cont *ft_init_tab(int tab_size);

void ft_swap_xy(t_point *p) {
	int tmp;

	tmp = p->x;
	p->x = p->y;
	p->y = tmp;
}

t_cont	*ft_fdf_intep_d(t_fdf *fdf, t_point p1, t_point p2, int orientation)
{
	t_points *res;
	t_point p3;
	int curr;
	int inc;
	int i;

	inc = 1;
	if (p2.x < p1.x)
		inc = -1;
	res = (t_points *) ft_init_tab(((p2.x - p1.x) * inc));
	p3 = (t_point) {.x = p1.x, .y = p2.y, .col = p2.col};
	curr = p1.x;
	i = -1;
	while (++i < res->size) //	while (curr * inc <= p2.x * inc)
	{
		p3.y = curr;
		p3.x = p1.y + ((p2.y - p1.y) * (curr - p1.x)) / (p2.x - p1.x);
		p3.col = ft_fdf_get_color(p1, p2, curr);
		if (orientation == 0)
			ft_swap_xy(&p3);
		res->data[i] = p3; //		((t_point *) (res->data))[i] = p3;
		curr += inc;
	}
	return (t_cont *) (res);
}

t_cont	*ft_init_tab(int tab_size) {
	t_point *tab;
	t_cont *cont;

	tab = (t_point *) malloc(sizeof(t_point) * tab_size);
	if (!tab) {
		errno = ENOMEM;
		return (NULL);
	}
	cont = (t_cont *) malloc(sizeof(t_cont));
	if (!cont) {
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
t_cont *draw_line_d(t_fdf *fdf, t_point p1, t_point p2) {
	t_cont *res;
	int orientation;

	orientation = (abs(p2.x - p1.x) < abs(p2.y - p1.y));
	if (orientation)
		(ft_swap_xy(&p1), ft_swap_xy(&p2));
	if ((p2.x == p1.x) && (p2.y == p1.y))
	{
		res = ft_init_tab(1);
		*(t_point *) (res->data) = (t_point) {.x = p1.x, .y = p2.y,
												  .col = p2.col};
	}
	else
		res = ft_fdf_intep_d(fdf, p1, p2, orientation);
	return (res);
}
