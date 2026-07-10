/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 03:21:28 by abelov            #+#    #+#             */
/*   Updated: 2024/05/28 03:21:29 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sysexits.h>
#include "ft_fdf.h"

int	cleanup(const t_fdf *fdf);

int	mouse_win(int button, int x, int y, void *p)
{
	double			step;
	t_fdf *const	app = p;

	((void)x, (void)y);
	if (button == FDF_SCROLL_DOWN || button == FDF_SCROLL_UP)
	{
		if (button == FDF_SCROLL_DOWN)
		{
			step = app->zoom - (app->zoom / FDF_PERCENT_DIVISOR);
			if (step < FDF_ZOOM_MIN)
				return (EX_OK);
			app->zoom = step;
		}
		if (button == FDF_SCROLL_UP)
		{
			step = app->zoom + (app->zoom / FDF_PERCENT_DIVISOR);
			if (step > FDF_ZOOM_MAX)
				return (EX_OK);
			app->zoom = step;
		}
		replace_image(app);
		on_expose(app);
	}
	return (EX_OK);
}

int	key_win(int key, t_fdf *fdf)
{
	int				step;

	step = FDF_PAN_STEP;
	if (key == XK_KP_5 || key == XK_Escape)
		exit_win(fdf);
	if (key == XK_Right)
		fdf->draw_offset_x += step;
	if (key == XK_Left)
		fdf->draw_offset_x -= step;
	if (key == XK_Up)
		fdf->draw_offset_y -= step;
	if (key == XK_Down)
		fdf->draw_offset_y += step;
	replace_image(fdf);
	on_expose(fdf);
	return (0);
}

void	replace_image(t_fdf *fdf)
{
	t_img	*im3;

	im3 = mlx_new_image(fdf->mlx, fdf->win.width, fdf->win.height);
	if (!im3)
		exit(cleanup(fdf) + 1);
	mlx_destroy_image(fdf->mlx, fdf->canvas);
	fdf->canvas = im3;
	mlx_put_image_to_window(fdf->mlx, fdf->root,
		fdf->canvas, fdf->offset.x, fdf->offset.y);
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
	t_img	*cnvs;

	cnvs = mlx_new_image(fdf->mlx, fdf->win.width, fdf->win.height);
	if (!cnvs)
		exit(cleanup(fdf) + 1);
	fdf->canvas = cnvs;
	on_expose(fdf);
	return (EX_OK);
}
