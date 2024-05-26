/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line_d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 03:13:26 by abelov            #+#    #+#             */
/*   Updated: 2024/05/25 03:13:27 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf/fdf_lib.h>
#include <ft_fdf.h>

int	ft_fdf_intep_d(t_fdf *fdf, t_point p1, t_point p2, int orientation);

void	ft_swap_xy(t_point *p)
{
	int	tmp;

	tmp = p->x;
	p->x = p->y;
	p->y = tmp;
}

int	draw_line_d(t_fdf *fdf, t_point p1, t_point p2)
{
	int	res;
	int	orientation;

	orientation = (abs(p2.x - p1.x) < abs(p2.y - p1.y));
	if (orientation)
		(ft_swap_xy(&p1), ft_swap_xy(&p2));
	if (p2.x == p1.x && p2.y == p1.y)
		res = mlx_pixel_put(fdf->mlx, fdf->main_win, p1.x, p2.y, p2.col);
	else
		res = ft_fdf_intep_d(fdf, p1, p2, orientation);
	return (res);
}

int	ft_fdf_intep_d(t_fdf *fdf, t_point p1, t_point p2, int orientation)
{
	t_point	p3;
	int		curr;
	int		res;
	int		inc;

	inc = 1;
	if (p2.x < p1.x)
		inc = -1;
	curr = p1.x;
	while (curr * inc <= p2.x * inc)
	{
		p3.y = curr;
		p3.col = ft_fdf_get_color(p1, p2, curr);
		p3.x = p1.y + ((p2.y - p1.y) * (curr - p1.x)) / (p2.x - p1.x);
		if (orientation == 0)
			ft_swap_xy(&p3);
		res = mlx_pixel_put(fdf->mlx, fdf->main_win, p3.x, p3.y, p3.col);
		curr += inc;
	}
	return (res);
}
