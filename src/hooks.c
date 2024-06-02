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

#define NUM_5 0x35 /* (53) Number 5 on the main keyboard */
#define ESC 0xFF1B /* (53) Number 5 on the main keyboard */
#define UP 65362
#define DOWN 65364
#define RIGHT 65363
#define LEFT 65361

int	mouse_win(int button, int x, int y, void *p)
{
	t_img	*im3;
	double	step;

	if (button == 5 || button == 4)
	{
		if (button == 5)
		{
			step = ((t_fdf *) p)->zoom - (((t_fdf *) p)->zoom / 10);
			if (step < 0.1)
				return (EX_OK);
			((t_fdf *) p)->zoom = step;
		}
		if (button == 4)
		{
			step = ((t_fdf *) p)->zoom + (((t_fdf *) p)->zoom / 10);
			if (step > 70)
				return (EX_OK);
			((t_fdf *) p)->zoom += (((t_fdf *) p)->zoom / 10);
		}
		replace_image((t_fdf *) p);
		on_expose((t_fdf *) p);
	}
	return (EX_OK);
}

int	key_win(int key, t_fdf *fdf)
{
	int				step;
	static t_point	offset = {0};

	step = 25;
	if (key == NUM_5 || key == ESC)
		exit(0);
	if (key == RIGHT)
		fdf->draw_offset_x += step;
	if (key == LEFT)
		fdf->draw_offset_x -= step;
	if (key == UP)
		fdf->draw_offset_y -= step;
	if (key == DOWN)
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
	{
		ft_printf(" !! KO !!\n");
		exit(1);
	}
	mlx_destroy_image(fdf->mlx, fdf->canvas);
	fdf->canvas = im3;
	mlx_put_image_to_window(fdf->mlx, fdf->root,
		fdf->canvas, fdf->offset.x, fdf->offset.y);
}

int	exit_win(void *p)
{
	exit(0);
}

/**
 * https://tronche.com/gui/x/xlib/events/exposure/
 * https://tronche.com/gui/x/xlib/events/exposure/expose.html
 * https://tronche.com/gui/x/xlib/window/attributes/#XSetWindowAttributes
 */
int	expose_win(t_fdf *fdf)
{
	t_img	*im3;

	im3 = mlx_new_image(fdf->mlx, fdf->win.width, fdf->win.height);
	if (!im3)
	{
		ft_printf(" !! KO !!\n");
		exit(1);
	}
	fdf->canvas = im3;
	on_expose(fdf);
	return (EX_OK);
}
