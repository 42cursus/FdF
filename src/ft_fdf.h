/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 07:37:23 by abelov            #+#    #+#             */
/*   Updated: 2024/05/18 07:37:24 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FDF_H
# define FT_FDF_H
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include <mlx_int.h>
# include "ft/gnl.h"
# include "ft/libft.h"
# include "mlx/mlx.h"

# define WHITE_COLOR 0xffffff
# define FDF_INIT_SCALE 20
# define FDF_INIT_ZOOM 1.5
# define FDF_WIN_MAX_WIDTH 1024
# define FDF_WIN_MAX_HEIGHT 768
# define FDF_WIN_WIDTH_FACTOR 280
# define FDF_PERCENT_DIVISOR 10
# define FDF_FIT_SCALE_NUMERATOR 10000
# define FDF_GRID_SCALE_FACTOR 7
# define FDF_HEIGHT_MARGIN_DIVISOR 20
# define FDF_ISO_X_DIVISOR 10
# define FDF_ISO_Y_DIVISOR 15
# define FDF_PAN_STEP 25
# define FDF_ZOOM_MIN 0.1
# define FDF_ZOOM_MAX 70
# define FDF_SCROLL_UP 4
# define FDF_SCROLL_DOWN 5
# define FDF_RGB_RED_SHIFT 16
# define FDF_RGB_GREEN_SHIFT 8
# define FDF_RGB_MODULO 256

typedef struct s_fdf_colour
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_fdf_point
{
	int	x;
	int	y;
	int	z;
	int	col;
}	t_point;

typedef struct s_rect
{
	t_point	t1;
	t_point	t2;
	t_point	t3;
	t_point	t4;
}	t_rect;

typedef struct s_bres
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	steps;
}	t_bres;

typedef struct s_map_row	t_map_row;
struct s_map_row
{
	char		*line;
	char		**word_tab;
	double		*heights;
	int			*colours;
	t_map_row	*next;
};

typedef struct s_fdf_struct
{
	struct s_fdf_win
	{
		int	width;
		int	height;
	}			win;
	t_point		offset;
	t_xvar		*mlx;
	t_win_list	*root;
	t_map_row	*map;
	int			cols;
	int			rows;
	double		xy_scale;
	double		z_scale;
	double		max_height;
	char		*filename;
	int			custom_colour_flag;
	int			endianness;
	double		draw_offset_y;
	double		draw_offset_x;
	double		zoom;
	t_img		*canvas;
}	t_fdf;

void	load_data(t_fdf *fdf);
void	data_convert(t_fdf *fdf, t_map_row *row);
void	on_expose(t_fdf *fdf);
void	mlx_keypress_hook(t_fdf *const fdf);
int		key_win(int key, t_fdf *fdf);
int		mouse_win(int button, int x, int y, void *p);
int		cleanup(const t_fdf *fdf);
int		exit_win(const t_fdf *fdf);
int		expose_win(t_fdf *fdf);
int		check_endianness(void);
void	calculate_zoom(t_fdf *const fdf);
t_point	get_point(t_fdf *fdf, t_map_row *row, int col, int crow);
void	replace_image(t_fdf *fdf);
void	draw_line_d(t_fdf *fdf, t_point p1, t_point p2);
#endif //FT_FDF_H
