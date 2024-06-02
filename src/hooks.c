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

# define NUM_5	 0x35 /* (53) Number 5 on the main keyboard */
# define ESC	 0xFF1B /* (53) Number 5 on the main keyboard */
# define UP 65362
# define DOWN 65364
# define RIGHT 65363
# define LEFT 65361

# define EXIT_KEY ESC

int mouse_win(int button, int x, int y, void *p)
{
	ft_printf("Mouse in Win1, button %d at %dx%d.\n", button, x, y);
	t_fdf *fdf = (t_fdf *)p;

	int img_width;
	int img_height;
	double step;

	step = 0.5;
	if (button == 5 || button == 4)
	{
		if (button == 5)
			if (fdf->zoom > step * 2)
				fdf->zoom -= step;
		if (button == 4)
			fdf->zoom += step;

		img_width = (int) (fdf->win.width * fdf->zoom * 2);
		img_height = (int) (fdf->win.height * fdf->zoom * 2);

		fdf->offset.x = -((img_width / 2) - (fdf->win.width / 2));
		fdf->offset.y = -((img_height / 2) - (fdf->win.height / 2));

		fdf->draw_offset_x = img_width / 2.2;
		fdf->draw_offset_y = img_height / 1.5;

		t_img *im3 = mlx_new_image(fdf->mlx, img_width, img_height);
		if (!im3) {
			ft_printf(" !! KO !!\n");
			exit(1);
		}
		ft_printf("OK (bpp3 %d, sizeline3 %d endianness3 %d type %d)\n",
				  im3->bpp, im3->size_line, im3->image->byte_order, im3->type);
		mlx_destroy_image(fdf->mlx, fdf->canvas);
		fdf->canvas = im3;
		on_expose(fdf);
	}
	return (EX_OK);
}

int key_win(int key, t_fdf *fdf)
{
	int		step = 25;
	static	t_point offset = {0};

//	printf("Key in Win1 : %d\n", key);
	if (key == NUM_5 || key == ESC)
		exit(0);
	if (key == RIGHT)
		fdf->offset.x += step;
	if (key == LEFT)
		fdf->offset.x -= step;
	if (key == UP)
		fdf->offset.y -= step;
	if (key == DOWN)
		fdf->offset.y += step;
	mlx_clear_window(fdf->mlx, fdf->root);
	mlx_put_image_to_window(fdf->mlx, fdf->root, fdf->canvas, fdf->offset.x, fdf->offset.y);
	return (0);
}

int exit_win(void *p)
{
	exit(0);
}

/**
 * https://tronche.com/gui/x/xlib/events/exposure/
 * https://tronche.com/gui/x/xlib/events/exposure/expose.html
 * https://tronche.com/gui/x/xlib/window/attributes/#XSetWindowAttributes
 */
int expose_win(void *fdf) {
	ft_printf("Expose window hook. Param: %d\n", *(int *)fdf);
	on_expose(fdf);
	return (EX_OK);
}