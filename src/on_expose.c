/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   on_expose.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 03:11:20 by abelov            #+#    #+#             */
/*   Updated: 2024/05/25 03:11:21 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf/fdf_lib.h"
#include "ft_fdf.h"

void on_expose(t_fdf *fdf)

{
	t_map_row *row;
	t_point *const t1 = &(t_point){};
	int cr;
	int cc;
	struct s_fdf_win win;

	int z_scale = fdf->z_scale;
	int b_scale = fdf->b_scale;
	
	win = fdf->win;
	row = fdf->map;
	cr = fdf->rows;
	while (--cr > 0)
	{
		cc = fdf->cols;
		while (--cc > 0)
		{

			int ch_cc = (int) row->heights[cc] * z_scale;
			int ch_nc = (int) row->heights[(cc - 1)] * z_scale;
			int nh_cc = (int) row->next->heights[cc] * z_scale;
			int nh_nc = (int) row->next->heights[(cc - 1)] * z_scale;

			int cc7 = cc * b_scale * 7;
			int cr7 = cr * b_scale * 7;
			int pc7 = (cc - 1) * b_scale * 7;
			int pr7 = (cr - 1) * b_scale * 7;

			*t1 = (t_point){
				.x = (cc7 / 10 - cr7 / 10) + win.width / 2,
				.y = win.height - (ch_cc + cc7 / 20 + cr7 / 20),
				.col = row->colours[cc]
			};

			draw_line_d(fdf,  *t1, (t_point){
				.x = (cc7 / 10 - pr7 / 10) + win.width / 2,
				.y = win.height - (nh_cc + cc7 / 20 + pr7 / 20),
				.col = row->next->colours[cc]
			});

			draw_line_d(fdf, *t1, (t_point){
				.x = (pc7 / 10 - cr7 / 10) + win.width / 2,
				.y = win.height - (ch_nc + pc7 / 20 + cr7 / 20),
				.col = row->colours[(cc - 1)]
			});

			if (fdf->custom_colour_flag != 0)
				draw_line_d(fdf, *t1, (t_point) {
					.x = (pc7 / 10 - pr7 / 10) + win.width / 2,
					.y = win.height - (nh_nc + pc7 / 20 + pr7 / 20),
					.col = row->colours[(cc - 1)],
				});
		}
		if (cr % (fdf->rows / 10 + 1) == 0)
			mlx_do_sync(fdf->mlx);
		row = row->next;
	}
}
