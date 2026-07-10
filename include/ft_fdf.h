/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 07:37:23 by abelov            #+#    #+#             */
/*   Updated: 2026/07/10 18:34:56 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FDF_H
# define FT_FDF_H
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include <X11/Xlib.h>
# include <X11/Xutil.h>
# include <X11/extensions/XShm.h>
# include "libft.h"
# include <mlx.h>

typedef struct s_xvar		t_xvar;
typedef struct s_win_list	t_win_list;

# define WHITE_COLOR 0xffffff
# define FDF_INIT_SCALE 20
# define FDF_WIN_MAX_WIDTH 1024
# define FDF_WIN_MAX_HEIGHT 768
# define FDF_WIN_WIDTH_FACTOR 280
# define FDF_PERCENT_DIVISOR 10
# define FDF_FIT_SCALE_NUMERATOR 10000
# define FDF_GRID_SCALE_FACTOR 7
# define FDF_HEIGHT_MARGIN_DIVISOR 20
# define FDF_ISO_X_DIVISOR 10
# define FDF_ISO_Y_DIVISOR 20
# define FDF_PARALLEL_DIVISOR 8
# define FDF_CABINET_X_DIVISOR 8
# define FDF_PARALLEL_DEPTH_DIVISOR 2
# define FDF_CABINET_DEPTH_DIVISOR 4
# define FDF_PAN_STEP 25
# define FDF_ROT_STEP 0.035
# define FDF_Z_FACTOR_MIN 0.1
# define FDF_Z_FACTOR_MAX 10.0
# define FDF_Z_FACTOR_STEP 0.1
# define FDF_ZOOM_MIN 0.1
# define FDF_ZOOM_MAX 70
# define FDF_SCROLL_UP 4
# define FDF_SCROLL_DOWN 5
# define FDF_MOUSE_MIDDLE 2
# define FDF_PROJ_ISO 1
# define FDF_PROJ_PARALLEL 2
# define FDF_PROJ_CABINET 3
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

typedef struct s_fdf_dpoint
{
	double	x;
	double	y;
	double	z;
	int		col;
}	t_dpoint;

typedef struct s_transform
{
	t_dpoint	point;
	double		scale;
}	t_transform;

typedef struct s_xshm
{
	ShmSeg	shmseg;
	int		shmid;
	char	*shmaddr;
	Bool	read_only;
}	t_xshm;

typedef struct s_img
{
	XImage	*image;
	Pixmap	pix;
	GC		gc;
	int		size_line;
	int		bpp;
	int		width;
	int		height;
	int		type;
	int		format;
	char	*data;
	t_xshm	shm;
}	t_img;

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

typedef struct s_fdf_view
{
	int		projection;
	double	zoom;
	double	pan_x;
	double	pan_y;
	double	rot_x;
	double	rot_y;
	double	rot_z;
	double	z_factor;
	int		dirty;
	int		mouse_active;
	int		drag;
	int		mouse_x;
	int		mouse_y;
}	t_view;

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
	t_view		view;
	t_img		*canvas;
}	t_fdf;

void	load_data(t_fdf *fdf);
void	data_convert(t_fdf *fdf, t_map_row *row);
void	on_expose(t_fdf *fdf);

int		key_win(int key, t_fdf *fdf);
int		mouse_win(int button, int x, int y, void *p);
int		mouse_release_win(int button, int x, int y, void *p);
int		mouse_move_win(int x, int y, void *p);
int		cleanup(const t_fdf *fdf);
int		exit_win(const t_fdf *fdf);
int		expose_win(t_fdf *fdf);
int		check_endianness(void);
void	calculate_zoom(t_fdf *const fdf);
void	init_view(t_fdf *fdf);
void	refresh_image(t_fdf *fdf);
void	fdf_pan(t_fdf *fdf, double dx, double dy);
void	fdf_zoom_at(t_fdf *fdf, double next_zoom, int x, int y);
void	fdf_reset_view(t_fdf *fdf);
void	fdf_adjust_z_factor(t_fdf *fdf, double delta);
t_point	get_point(t_fdf *fdf, t_map_row *row, int col, int crow);
void	rotate_x(t_dpoint *point, double angle);
void	rotate_y(t_dpoint *point, double angle);
void	rotate_z(t_dpoint *point, double angle);
void	replace_image(t_fdf *fdf);
void	draw_line_d(t_fdf *fdf, t_point p1, t_point p2);
#endif //FT_FDF_H
