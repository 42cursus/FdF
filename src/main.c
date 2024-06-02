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
#include <fdf/fdf_lib.h>
#include "ft_fdf.h"

void	mlx_keypress_hook(t_fdf *const fdf);

int	main(int argc, char **argv)
{
	t_fdf *const	fdf = &(t_fdf){.xy_scale = 20, .z_scale = 20,
		.zoom = 1.5, .map = NULL, .custom_colour_flag = 0};

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
	calculate_zoom(fdf);
	fdf->mlx = mlx_init();
	if (fdf->mlx == NULL)
		exit(1);
	fdf->root = mlx_new_window(fdf->mlx, fdf->win.width,
			fdf->win.height, "fdf");
	mlx_expose_hook(fdf->root, expose_win, fdf);
	mlx_mouse_hook(fdf->root, mouse_win, fdf);
	mlx_hook(fdf->root, DestroyNotify, 0, exit_win, fdf);
	mlx_keypress_hook(fdf);
	mlx_loop(fdf->mlx);
	return (EX_OK);
}

void	mlx_keypress_hook(t_fdf *const fdf)
{
	fdf->root->hooks[KeyRelease].hook = key_win;
	fdf->root->hooks[KeyRelease].param = fdf;
	fdf->root->hooks[KeyRelease].mask = KeyReleaseMask | KeyPressMask;
}

void	calculate_zoom(t_fdf *const fdf)
{
	int	shortest_side;
	int	longest_side;
	int	colls_rows;

	longest_side = fdf->cols;
	if (fdf->cols < fdf->rows)
		longest_side = fdf->rows;
	fdf->win.width = (longest_side * 280) * 2 / 10;
	if (fdf->win.width > 1024)
	{
		fdf->win.width = 1024;
		shortest_side = fdf->cols;
		if (fdf->cols < fdf->rows)
			shortest_side = fdf->rows;
		fdf->xy_scale = (int)(10000 / (long)(shortest_side * 7 * 2));
	}
	fdf->z_scale = fdf->xy_scale;
	colls_rows = (int)((fdf->cols + fdf->rows) * fdf->xy_scale / 20);
	fdf->win.height = fdf->max_height * 2 * fdf->xy_scale + (colls_rows * 7);
	if (fdf->win.height > 768)
	{
		fdf->win.height = 768;
		fdf->z_scale = ((768 - colls_rows) / fdf->max_height / 20);
	}
	fdf->zoom = fdf->xy_scale;
}
