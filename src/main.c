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

int	main(int argc, char **argv)
{
	int				shortest_side;
	int				longest_side;
	t_fdf *const	fdf = &(t_fdf){.xy_scale = 20, .z_scale = 20, .zoom = 1.5,
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
	fdf->win.width = (longest_side * 280) * 2 / 10;
	if (fdf->win.width > 1024)
	{
		fdf->win.width = 1024;
		if (fdf->cols < fdf->rows)
			shortest_side = fdf->rows;
		else
			shortest_side = fdf->cols;
		fdf->xy_scale = (int) (10000 / (long) (shortest_side * (7 * 2)));
	}
	fdf->z_scale = fdf->xy_scale;

	int colls_rows = fdf->cols + fdf->rows;

	fdf->win.height = fdf->max_height * 2 * fdf->xy_scale + (fdf->xy_scale * (fdf->cols + fdf->rows) *
		7) / (10 * 2);

	int delta = colls_rows * fdf->xy_scale / (10 * 2);

	if (fdf->win.height > 768)
	{
		fdf->win.height = 768;
		fdf->z_scale = ((768 - delta) / fdf->max_height);
	}

	fdf->xy_scale *= 1 * fdf->zoom;
	fdf->z_scale *= 0.5 * fdf->zoom;

	int img_width = (int)(fdf->win.width * fdf->zoom * 2);
	int img_height = (int)(fdf->win.height * fdf->zoom * 2);

	fdf->offset.x = -((img_width / 2) - (fdf->win.width / 2));
	fdf->offset.y = -((img_height / 2) - (fdf->win.height / 2));

	fdf->draw_offset_x = img_width / 2.2;
	fdf->draw_offset_y = img_height / 1.5;

	fdf->mlx = mlx_init();
	if (fdf->mlx == NULL)
		exit(1);
	fdf->root = mlx_new_window(fdf->mlx, fdf->win.width,
							   fdf->win.height, "fdf");
	t_img *im3 = mlx_new_image(fdf->mlx, img_width, img_height);
	if (!im3)
	{
		ft_printf(" !! KO !!\n");
		exit(1);
	}
	ft_printf("OK (bpp3 %d, sizeline3 %d endianness3 %d type %d)\n",
			  im3->bpp, im3->size_line, im3->image->byte_order, im3->type);
	fdf->canvas = im3;
	mlx_mouse_hook( fdf->root, mouse_win, fdf);
	mlx_expose_hook(fdf->root, expose_win, fdf);
	mlx_hook(fdf->root, DestroyNotify, 0, exit_win,
			 fdf->mlx);
	fdf->root->hooks[KeyRelease].hook = key_win;
	fdf->root->hooks[KeyRelease].param = fdf;
	fdf->root->hooks[KeyRelease].mask = KeyReleaseMask | KeyPressMask;



	mlx_loop(fdf->mlx);

	return (ret_code);
}
