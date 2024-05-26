/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_lib.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 04:11:45 by abelov            #+#    #+#             */
/*   Updated: 2024/05/25 04:11:45 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_LIB_H
#define FDF_LIB_H

# include "util.h"

typedef struct s_fdf_colour
{
	int r;
	int g;
	int b;
}	t_rgb;

typedef struct s_fdf_point
{
	int x;
	int y;
	int col;
}	t_point;

typedef struct s_fdf_struct	t_fdf;
int		draw_line_d(t_fdf *fdf, t_point p1, t_point p2);
int		ft_fdf_get_color(t_point p1, t_point p2, int curr_pos);
t_rgb	ft_fdf_int_to_color(int color);

#endif //FDF_LIB_H
