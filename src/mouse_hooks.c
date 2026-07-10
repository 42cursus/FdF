/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 18:30:00 by abelov            #+#    #+#             */
/*   Updated: 2026/07/10 18:35:28 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sysexits.h>
#include "ft_fdf.h"

int	mouse_win(int button, int x, int y, void *p)
{
	t_fdf *const	fdf = p;
	double			next_zoom;

	fdf->view.mouse_active = 1;
	fdf->view.mouse_x = x;
	fdf->view.mouse_y = y;
	if (button == FDF_MOUSE_MIDDLE)
		fdf->view.drag = 1;
	if (button != FDF_SCROLL_DOWN && button != FDF_SCROLL_UP)
		return (EX_OK);
	next_zoom = fdf->view.zoom + fdf->view.zoom / FDF_PERCENT_DIVISOR;
	if (button == FDF_SCROLL_DOWN)
		next_zoom = fdf->view.zoom - fdf->view.zoom / FDF_PERCENT_DIVISOR;
	fdf_zoom_at(fdf, next_zoom, x, y);
	refresh_image(fdf);
	return (EX_OK);
}

int	mouse_release_win(int button, int x, int y, void *p)
{
	t_fdf *const	fdf = p;

	((void)x, (void)y);
	if (button == FDF_MOUSE_MIDDLE)
		fdf->view.drag = 0;
	return (EX_OK);
}

int	mouse_move_win(int x, int y, void *p)
{
	t_fdf *const	fdf = p;

	fdf->view.mouse_active = 1;
	if (fdf->view.drag)
	{
		fdf_pan(fdf, x - fdf->view.mouse_x, y - fdf->view.mouse_y);
		fdf->view.mouse_x = x;
		fdf->view.mouse_y = y;
		refresh_image(fdf);
		return (EX_OK);
	}
	fdf->view.mouse_x = x;
	fdf->view.mouse_y = y;
	return (EX_OK);
}
