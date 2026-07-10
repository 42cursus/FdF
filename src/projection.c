/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 18:30:00 by abelov            #+#    #+#             */
/*   Updated: 2026/07/10 18:35:34 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

t_point	project_iso(t_fdf *fdf, t_transform transform)
{
	t_point	out;

	out.x = (int)((transform.point.x - transform.point.y)
			* transform.scale / FDF_ISO_X_DIVISOR
			+ fdf->win.width / 2 + fdf->view.pan_x);
	out.y = (int)(fdf->win.height / 2
			- (transform.point.x + transform.point.y)
			* transform.scale / FDF_ISO_Y_DIVISOR
			- transform.point.z * transform.scale / FDF_ISO_X_DIVISOR
			+ fdf->view.pan_y);
	out.z = (int)(transform.point.z * transform.scale);
	out.col = transform.point.col;
	return (out);
}

t_point	project_parallel(t_fdf *fdf, t_transform transform)
{
	t_point	out;

	out.x = (int)((transform.point.x + transform.point.y
				/ FDF_PARALLEL_DEPTH_DIVISOR) * transform.scale
			/ FDF_PARALLEL_DIVISOR + fdf->win.width / 2
			+ fdf->view.pan_x);
	out.y = (int)((-transform.point.y / FDF_PARALLEL_DEPTH_DIVISOR
				- transform.point.z) * transform.scale / FDF_PARALLEL_DIVISOR
			+ fdf->win.height / 2 + fdf->view.pan_y);
	out.z = (int)(transform.point.z * transform.scale);
	out.col = transform.point.col;
	return (out);
}

t_point	project_cabinet(t_fdf *fdf, t_transform transform)
{
	t_point	out;

	out.x = (int)((transform.point.x + transform.point.y
				/ FDF_CABINET_DEPTH_DIVISOR) * transform.scale
			/ FDF_CABINET_X_DIVISOR + fdf->win.width / 2
			+ fdf->view.pan_x);
	out.y = (int)((-transform.point.y / FDF_CABINET_DEPTH_DIVISOR
				- transform.point.z) * transform.scale / FDF_CABINET_X_DIVISOR
			+ fdf->win.height / 2 + fdf->view.pan_y);
	out.z = (int)(transform.point.z * transform.scale);
	out.col = transform.point.col;
	return (out);
}

static t_transform	model_point(t_fdf *fdf, t_map_row *row, int col, int crow)
{
	t_transform	transform;

	transform.point.x = col - (fdf->cols - 1) / 2.0;
	transform.point.y = crow - (fdf->rows - 1) / 2.0;
	transform.point.z = row->heights[col] * fdf->z_scale / fdf->xy_scale
		* fdf->view.z_factor;
	transform.point.col = row->colours[col];
	transform.scale = fdf->xy_scale * fdf->view.zoom;
	return (transform);
}

t_point	get_point(t_fdf *fdf, t_map_row *row, int col, int crow)
{
	t_transform	transform;

	transform = model_point(fdf, row, col, crow);
	rotate_x(&transform.point, fdf->view.rot_x);
	rotate_y(&transform.point, fdf->view.rot_y);
	rotate_z(&transform.point, fdf->view.rot_z);
	if (fdf->view.projection == FDF_PROJ_PARALLEL)
		return (project_parallel(fdf, transform));
	if (fdf->view.projection == FDF_PROJ_CABINET)
		return (project_cabinet(fdf, transform));
	return (project_iso(fdf, transform));
}
