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

# include <ft/ft_list.h>
# include "util.h"

/**
 * What is the strict aliasing rule?
 * 	https://stackoverflow.com/questions/98650/
 *
 * How to use a union along with two structs + more:
 * 	https://stackoverflow.com/questions/28596446/
 *
 * See also:
 * 	Embedded C. Struct and Union, Bit Fields in A Nutshell
 * 		https://atadiat.com/en/e-embedded-c-struct-union-part-2/
 */
typedef struct s_content
{
	void	*data;
	int		size;
}		t_cont;

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
	int z;
	int col;
}	t_point;

typedef struct s_fdf_points
{
	t_point	*data;
	int 	size;
}	t_points;

typedef struct s_fdf_struct	t_fdf;
t_cont *draw_line_d(t_fdf *fdf, t_point p1, t_point p2);
int		ft_fdf_get_color(t_point p1, t_point p2, int curr_pos);
t_rgb	ft_fdf_int_to_color(int color);

#endif //FDF_LIB_H
