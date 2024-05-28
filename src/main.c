/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 07:18:11 by abelov            #+#    #+#             */
/*   Updated: 2024/05/18 07:18:12 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sysexits.h>
#include <X11/XF86keysym.h>
#include <fdf/fdf_lib.h>
#include "ft_fdf.h"



int out(int key)
{
	if (key == EXIT_KEY)
		exit(1);
	return 0;
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




int	main(int argc, char **argv)
{
	int				shortest_side;
	int				longest_side;
	t_fdf *const	fdf = &(t_fdf){.xy_scale = 20, .z_scale = 20,
								   .map = NULL, .custom_colour_flag = 0};
	int				ret_code;

	ret_code = 0;
	ft_printf("FdF Test Program\n");
	fdf->endianness = check_endianness();
	if (argc != 2)
		exit(EX_USAGE);
	fdf->filename = argv[1];
	load_data(fdf);
	if (!fdf->cols || !fdf->rows)
	{
		printf("No data found.\n");
		exit(1);
	}
	if (fdf->cols < fdf->rows)
		longest_side = fdf->rows;
	else
		longest_side = fdf->cols;
	fdf->win.width = (longest_side * 280) / MULT2;
	if (fdf->win.width > 1000)
	{
		fdf->win.width = 1000;
		if (fdf->cols < fdf->rows)
			shortest_side = fdf->rows;
		else
			shortest_side = fdf->cols;
		fdf->xy_scale = (int) (10000 / (long) (shortest_side * (MULT1 * 2))) + 1;
	}
	fdf->z_scale = fdf->xy_scale;

	int colls_rows = fdf->cols + fdf->rows;

//	fdf->win.height = fdf->xy_scale / (MULT2 * 2) *  ((MULT2 * 2) * fdf->max_height + ((fdf->cols + fdf->rows) * MULT1));
	fdf->win.height = fdf->max_height * fdf->xy_scale + (fdf->xy_scale * (fdf->cols + fdf->rows) * MULT1) / (MULT2 * 2);

	int delta = colls_rows * fdf->xy_scale / (MULT2 * 2);
//
//	fdf->win.height = fdf->max_height * fdf->xy_scale + delta;
	if (fdf->win.height > 800)
	{
		fdf->win.height = 800;
		fdf->z_scale = ((800 - delta) / fdf->max_height) + 1;
	}

//	fdf->xy_scale *= 2;
//	fdf->z_scale *= 2;

	fdf->mlx = mlx_init();
	if (fdf->mlx == NULL)
		exit(1);
	fdf->root = mlx_new_window(fdf->mlx, fdf->win.width,
							   fdf->win.height, "fdf");

	fdf->xy_scale *= 1;
	fdf->z_scale *= 1;

	int img_width = fdf->win.width * 2;
	int img_height = fdf->win.height * 2;

	fdf->offset.x = -(fdf->win.width / 2);
	fdf->offset.y = -(fdf->win.height / 2);

	fdf->draw_offset_x = fdf->win.width;
	fdf->draw_offset_y = fdf->win.height - fdf->offset.y;

	t_img *im3 = mlx_new_image(fdf->mlx, img_width, img_height);
	if (!im3)
	{
		ft_printf(" !! KO !!\n");
		exit(1);
	}
	ft_printf("OK (bpp3 %d, sizeline3 %d endianness3 %d type %d)\n",
			  im3->bpp, im3->size_line, im3->image->byte_order, im3->type);
	fdf->canvas = im3;

	mlx_expose_hook(fdf->root, expose_win, fdf);
	t_img *im2 = mlx_xpm_file_to_image(fdf->mlx, "open24.xpm", (int [1]){}, (int[1]){});
	mlx_put_image_to_window(fdf->mlx, fdf->root, im2,  0, 0);

	mlx_hook(fdf->root, DestroyNotify, 0, exit_win,
			 fdf->mlx);
	fdf->root->hooks[KeyRelease].hook = key_win;
	fdf->root->hooks[KeyRelease].param = fdf;
	fdf->root->hooks[KeyRelease].mask = KeyReleaseMask | KeyPressMask;

	mlx_loop(fdf->mlx);

	return (ret_code);
}
