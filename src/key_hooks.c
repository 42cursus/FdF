/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 18:35:09 by abelov            #+#    #+#             */
/*   Updated: 2026/07/10 18:35:09 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sysexits.h>
#include "ft_fdf.h"

int	fdf_key_pan(int key, t_fdf *fdf)
{
	if (key == XK_Right)
		fdf_pan(fdf, FDF_PAN_STEP, 0);
	else if (key == XK_Left)
		fdf_pan(fdf, -FDF_PAN_STEP, 0);
	else if (key == XK_Up)
		fdf_pan(fdf, 0, -FDF_PAN_STEP);
	else if (key == XK_Down)
		fdf_pan(fdf, 0, FDF_PAN_STEP);
	else
		return (0);
	return (1);
}

int	fdf_key_rotate(int key, t_fdf *fdf)
{
	if (key == XK_w)
		fdf->view.rot_x += FDF_ROT_STEP;
	else if (key == XK_s)
		fdf->view.rot_x -= FDF_ROT_STEP;
	else if (key == XK_a)
		fdf->view.rot_y += FDF_ROT_STEP;
	else if (key == XK_d)
		fdf->view.rot_y -= FDF_ROT_STEP;
	else if (key == XK_q)
		fdf->view.rot_z += FDF_ROT_STEP;
	else if (key == XK_e)
		fdf->view.rot_z -= FDF_ROT_STEP;
	else
		return (0);
	return (1);
}

int	fdf_key_projection(int key, t_fdf *fdf)
{
	if (key == XK_1)
		fdf->view.projection = FDF_PROJ_ISO;
	else if (key == XK_2)
		fdf->view.projection = FDF_PROJ_PARALLEL;
	else if (key == XK_3)
		fdf->view.projection = FDF_PROJ_CABINET;
	else
		return (0);
	fdf->view.dirty = 1;
	return (1);
}

int	fdf_key_view(int key, t_fdf *fdf)
{
	if (key == XK_space)
		fdf_reset_view(fdf);
	else if (key == XK_KP_Add)
		fdf_adjust_z_factor(fdf, FDF_Z_FACTOR_STEP);
	else if (key == XK_KP_Subtract)
		fdf_adjust_z_factor(fdf, -FDF_Z_FACTOR_STEP);
	else
		return (0);
	return (1);
}

int	key_win(int key, t_fdf *fdf)
{
	if (key == XK_KP_5 || key == XK_Escape)
		exit_win(fdf);
	if (fdf_key_pan(key, fdf) || fdf_key_rotate(key, fdf)
		|| fdf_key_projection(key, fdf) || fdf_key_view(key, fdf))
		refresh_image(fdf);
	return (EX_OK);
}
