/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 03:21:28 by abelov            #+#    #+#             */
/*   Updated: 2024/05/28 03:21:29 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

int key_win(int key, t_fdf *fdf)
{
	t_img *im = fdf->canvas;
	int step = 25;


	printf("Key in Win1 : %d\n", key);
	if (key == EXIT_KEY)
		exit(0);
	if (key == RIGHT) {
		fdf->offset.x += step;
//		mlx_clear_window(fdf->mlx, fdf->root);
		mlx_put_image_to_window(fdf->mlx, fdf->root, im, fdf->offset.x, fdf->offset.y);
	}
	if (key == LEFT) {
		fdf->offset.x -= step;
//		mlx_clear_window(fdf->mlx, fdf->root);
		mlx_put_image_to_window(fdf->mlx, fdf->root, im, fdf->offset.x, fdf->offset.y);
	}
	if (key == UP) {
		fdf->offset.y -= step;
//		mlx_clear_window(fdf->mlx, fdf->root);
		mlx_put_image_to_window(fdf->mlx, fdf->root, im, fdf->offset.x, fdf->offset.y);
	}
	if (key == DOWN) {
		fdf->offset.y += step;
//		mlx_clear_window(fdf->mlx, fdf->root);
		mlx_put_image_to_window(fdf->mlx, fdf->root, im, fdf->offset.x, fdf->offset.y);
	}
	return (0);
}

