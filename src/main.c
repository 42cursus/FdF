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
#include "ft_fdf.h"

# define EXIT_KEY 0x35 /* (53) Number 5 on the main keyboard */

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

int	main(int argc, char **argv)
{
	int				i;
	int				shortest_side;
	int				longest_side;
	t_fdf *const	fdf = &(t_fdf){.map = NULL, .custom_colour_flag = 1};
	int				ret_code;
	
	ret_code = 0;
	ft_printf("FdF Test Program\n");
	fdf->endianness = check_endianness();
	if (argc != 2)
		exit(EX_USAGE);
	fdf->filename = argv[1];
	load_data(fdf);
	if (!fdf->cols || !fdf->rows) {
		printf("No data found.\n");
		exit(1);
	}
	fdf->b_scale = 20;
	if (fdf->cols < fdf->rows)
		longest_side = fdf->rows;
	else
		longest_side = fdf->cols;
	fdf->win.width = (longest_side * 280) / 10;
	if (1000 < fdf->win.width) {
		fdf->win.width = 1000;
		if (fdf->cols < fdf->rows)
			shortest_side = fdf->rows;
		else
			shortest_side = fdf->cols;
		fdf->b_scale = (int) (10000 / (long) (shortest_side * 14)) + 1;
	}
	fdf->z_scale = fdf->b_scale;

	i = fdf->b_scale * (fdf->cols + fdf->rows) * 7;

	fdf->win.height = fdf->max_height * fdf->b_scale + i / 20;

	if (800 < fdf->win.height) {
		fdf->win.height = 800;
		fdf->z_scale = (800 - i / 20) / fdf->max_height + 1;
	}
	fdf->mlx = mlx_init();
	if (fdf->mlx == NULL)
		exit(1);
	fdf->main_win = mlx_new_window(fdf->mlx, fdf->win.width,
								   fdf->win.height, "fdf");
	on_expose(fdf);
	mlx_hook(fdf->main_win,
			 DestroyNotify, 0, exit_win, fdf->mlx);
	mlx_key_hook(fdf->main_win, out, NULL);
	mlx_loop(fdf->mlx);
	return (ret_code);
}
