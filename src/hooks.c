/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 03:21:28 by abelov            #+#    #+#             */
/*   Updated: 2026/07/10 18:35:00 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sysexits.h>
#include "ft_fdf.h"

void	replace_image(t_fdf *fdf)
{
	t_img	*im3;

	im3 = mlx_new_image(fdf->mlx, fdf->win.width, fdf->win.height);
	if (!im3)
		exit(cleanup(fdf) + 1);
	if (fdf->canvas)
		mlx_destroy_image(fdf->mlx, fdf->canvas);
	fdf->canvas = im3;
	mlx_put_image_to_window(fdf->mlx, fdf->root,
		fdf->canvas, fdf->offset.x, fdf->offset.y);
}

void	refresh_image(t_fdf *fdf)
{
	replace_image(fdf);
	on_expose(fdf);
	fdf->view.dirty = 0;
}

int	exit_win(const t_fdf *fdf)
{
	exit(cleanup(fdf));
}

/**
 * https://tronche.com/gui/x/xlib/events/exposure/
 * https://tronche.com/gui/x/xlib/events/exposure/expose.html
 * https://tronche.com/gui/x/xlib/window/attributes/#XSetWindowAttributes
 */
int	expose_win(t_fdf *fdf)
{
	if (!fdf->canvas)
	{
		fdf->canvas = mlx_new_image(fdf->mlx, fdf->win.width,
				fdf->win.height);
		if (!fdf->canvas)
			exit(cleanup(fdf) + 1);
	}
	on_expose(fdf);
	return (EX_OK);
}
