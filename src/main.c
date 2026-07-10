/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 07:18:11 by abelov            #+#    #+#             */
/*   Updated: 2026/07/10 18:35:23 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sysexits.h>
#include "ft_fdf.h"

void	setup_mlx(t_fdf *fdf);
void	clamp_window_height(t_fdf *fdf, int colls_rows);

int	main(int argc, char **argv)
{
	t_fdf *const	fdf = &(t_fdf){.xy_scale = FDF_INIT_SCALE,
		.z_scale = FDF_INIT_SCALE};

	fdf->endianness = check_endianness();
	if (argc != 2)
	{
		ft_printf("Usage: %s <map.fdf>\n", argv[0]);
		exit(EX_USAGE);
	}
	fdf->filename = argv[1];
	load_data(fdf);
	if (!fdf->cols || !fdf->rows)
	{
		printf("No data found.\n");
		exit(cleanup(fdf) + 1);
	}
	calculate_zoom(fdf);
	init_view(fdf);
	setup_mlx(fdf);
	mlx_loop(fdf->mlx);
	return (EX_OK);
}

void	setup_mlx(t_fdf *fdf)
{
	fdf->mlx = mlx_init();
	if (fdf->mlx == NULL)
		exit(cleanup(fdf) + 1);
	fdf->root = mlx_new_window(fdf->mlx, fdf->win.width,
			fdf->win.height, "fdf");
	if (fdf->root == NULL)
		exit(cleanup(fdf) + 1);
	mlx_expose_hook(fdf->root, (void *)expose_win, fdf);
	mlx_mouse_hook(fdf->root, (void *)mouse_win, fdf);
	mlx_hook(fdf->root, ButtonRelease, ButtonReleaseMask,
		(void *)mouse_release_win, fdf);
	mlx_hook(fdf->root, MotionNotify, PointerMotionMask,
		(void *)mouse_move_win, fdf);
	mlx_hook(fdf->root, DestroyNotify, 0, (void *)exit_win, fdf);
	mlx_hook(fdf->root, KeyPress, KeyPressMask, (void *) &key_win, fdf);
}

void	calculate_zoom(t_fdf *const fdf)
{
	int	colls_rows;
	int	longest_side;
	int	shortest_side;

	longest_side = fdf->cols;
	if (fdf->cols < fdf->rows)
		longest_side = fdf->rows;
	shortest_side = fdf->rows;
	if (fdf->cols < fdf->rows)
		shortest_side = fdf->cols;
	fdf->win.width = (longest_side * FDF_WIN_WIDTH_FACTOR)
		* 2 / FDF_PERCENT_DIVISOR;
	if (fdf->win.width > FDF_WIN_MAX_WIDTH)
	{
		fdf->win.width = FDF_WIN_MAX_WIDTH;
		fdf->xy_scale = (int)(FDF_FIT_SCALE_NUMERATOR
				/ (long)(shortest_side * FDF_GRID_SCALE_FACTOR * 2));
	}
	fdf->z_scale = fdf->xy_scale;
	colls_rows = (int)((fdf->cols + fdf->rows) * fdf->xy_scale
			/ FDF_HEIGHT_MARGIN_DIVISOR);
	fdf->win.height = fdf->max_height * 2 * fdf->xy_scale
		+ (colls_rows * FDF_GRID_SCALE_FACTOR);
	clamp_window_height(fdf, colls_rows);
}

void	clamp_window_height(t_fdf *fdf, int colls_rows)
{
	if (fdf->win.height <= FDF_WIN_MAX_HEIGHT)
		return ;
	fdf->win.height = FDF_WIN_MAX_HEIGHT;
	if (fdf->max_height > 0)
		fdf->z_scale = ((FDF_WIN_MAX_HEIGHT - colls_rows)
				/ fdf->max_height / FDF_HEIGHT_MARGIN_DIVISOR);
}
