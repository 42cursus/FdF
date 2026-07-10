/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 18:30:00 by abelov            #+#    #+#             */
/*   Updated: 2026/07/10 18:35:39 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

void	init_view(t_fdf *fdf)
{
	fdf->view.projection = FDF_PROJ_ISO;
	fdf->view.zoom = fdf->xy_scale;
	fdf->view.pan_x = 0;
	fdf->view.pan_y = 0;
	fdf->view.rot_x = 0;
	fdf->view.rot_y = 0;
	fdf->view.rot_z = 0;
	fdf->view.z_factor = 1.0;
	fdf->view.dirty = 1;
	fdf->view.mouse_active = 0;
	fdf->view.drag = 0;
	fdf->view.mouse_x = fdf->win.width / 2;
	fdf->view.mouse_y = fdf->win.height / 2;
}

void	fdf_pan(t_fdf *fdf, double dx, double dy)
{
	fdf->view.pan_x += dx;
	fdf->view.pan_y += dy;
	fdf->view.dirty = 1;
}

void	fdf_reset_view(t_fdf *fdf)
{
	fdf->view.zoom = fdf->xy_scale;
	fdf->view.pan_x = 0;
	fdf->view.pan_y = 0;
	fdf->view.rot_x = 0;
	fdf->view.rot_y = 0;
	fdf->view.rot_z = 0;
	fdf->view.z_factor = 1.0;
	fdf->view.mouse_active = 0;
	fdf->view.drag = 0;
	fdf->view.mouse_x = fdf->win.width / 2;
	fdf->view.mouse_y = fdf->win.height / 2;
	fdf->view.dirty = 1;
}

void	fdf_adjust_z_factor(t_fdf *fdf, double delta)
{
	double	next_factor;

	next_factor = fdf->view.z_factor + delta;
	if (next_factor < FDF_Z_FACTOR_MIN || next_factor > FDF_Z_FACTOR_MAX)
		return ;
	fdf->view.z_factor = next_factor;
	fdf->view.dirty = 1;
}

void	fdf_zoom_at(t_fdf *fdf, double next_zoom, int x, int y)
{
	double	ratio;

	if (next_zoom < FDF_ZOOM_MIN || next_zoom > FDF_ZOOM_MAX)
		return ;
	if (!fdf->view.mouse_active)
	{
		x = fdf->win.width / 2;
		y = fdf->win.height / 2;
	}
	ratio = next_zoom / fdf->view.zoom;
	fdf->view.pan_x = x - fdf->win.width / 2
		- ratio * (x - fdf->win.width / 2 - fdf->view.pan_x);
	fdf->view.pan_y = y - fdf->win.height / 2
		- ratio * (y - fdf->win.height / 2 - fdf->view.pan_y);
	fdf->view.zoom = next_zoom;
	fdf->view.dirty = 1;
}
