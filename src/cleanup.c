/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 10:20:06 by abelov            #+#    #+#             */
/*   Updated: 2024/06/02 10:20:06 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

int	cleanup(const t_fdf *fdf)
{
	int			errcode;
	t_map_row	*row;
	t_map_row	*curr;

	row = fdf->map;
	while (row != NULL)
	{
		curr = row;
		free(curr->colours);
		free(curr->heights);
		free(curr->word_tab);
		row = row->next;
		free(curr);
	}
	errcode = mlx_destroy_image(fdf->mlx, fdf->canvas);
	if (errcode)
		return (errcode);
	errcode = mlx_destroy_window(fdf->mlx, fdf->root);
	if (errcode)
		return (errcode);
	errcode = mlx_destroy_display(fdf->mlx);
	free(fdf->mlx);
	return (errcode);
}
