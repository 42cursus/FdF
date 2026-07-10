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

static void	free_word_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

static int	cleanup_mlx(const t_fdf *fdf)
{
	int	errcode;

	if (!fdf->mlx)
		return (0);
	errcode = 0;
	if (fdf->canvas)
		errcode = mlx_destroy_image(fdf->mlx, fdf->canvas);
	if (errcode)
		return (errcode);
	if (fdf->root)
		errcode = mlx_destroy_window(fdf->mlx, fdf->root);
	if (errcode)
		return (errcode);
	errcode = mlx_destroy_display(fdf->mlx);
	free(fdf->mlx);
	return (errcode);
}

int	cleanup(const t_fdf *fdf)
{
	t_map_row	*row;
	t_map_row	*curr;

	row = fdf->map;
	while (row != NULL)
	{
		curr = row;
		free(curr->colours);
		free(curr->heights);
		free_word_tab(curr->word_tab);
		row = row->next;
		free(curr);
	}
	return (cleanup_mlx(fdf));
}
