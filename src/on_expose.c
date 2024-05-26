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
	t_map_row *node;
	int cr;
	int cc;
	struct s_fdf_win win;
	
	win = fdf->win;
	node = fdf->map;
	cr = fdf->rows;
	while (--cr > 0)
	{
		cc = fdf->cols;
		while (--cc > 0)
		{

			int half_width = win.width / 2;

			int ch_cc = (int) node->heights[cc] * fdf->z_scale;
			int ch_nc = (int) node->heights[(cc - 1)] * fdf->z_scale;
			int nh_cc = (int) node->next->heights[cc] * fdf->z_scale;
			int nh_nc = (int) node->next->heights[(cc - 1)] * fdf->z_scale;

			int cc7 = cc * fdf->b_scale * 7;
			int cr7 = cr * fdf->b_scale * 7;
			int nc7 = (cc - 1) * fdf->b_scale * 7;
			int nr7 = (cr - 1) * fdf->b_scale * 7;

			int x1 = (cc7 / 10 - cr7 / 10) + half_width;
			int y1 = win.height - (ch_cc + cc7 / 20 + cr7 / 20);

			int y21 = win.height - (ch_nc + nc7 / 20 + cr7 / 20);
			int y22 = win.height - (nh_cc + cc7 / 20 + nr7 / 20);
			int y23 = win.height - (nh_nc + nc7 / 20 + nr7 / 20);
			
			int x21 = (nc7 / 10 - cr7 / 10) + half_width;
			int x22 = (cc7 / 10 - nr7 / 10) + half_width;
			int x23 = (nc7 / 10 - nr7 / 10) + half_width;

			draw_line_d(fdf, x1, y1, x22, y22,
						node->colours[cc],
						node->next->colours[cc]);

			draw_line_d(fdf, x1, y1, x21, y21,
						node->colours[cc],
						node->colours[(cc - 1)]);

			if (fdf->custom_colour_flag != 0)
			{
				draw_line_d(fdf, x1, y1, x23, y23,
							node->colours[cc],
							node->next->colours[(cc - 1)]);

			}
		}
		if (cr % (fdf->rows / 10 + 1) == 0)
			mlx_do_sync(fdf->mlx);
		node = node->next;
	}
}
