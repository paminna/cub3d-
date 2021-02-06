/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paminna <paminna@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 16:48:04 by paminna           #+#    #+#             */
/*   Updated: 2021/02/06 20:58:29 by paminna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void					ft_initialize(t_data *img)
{
	img->bits_per_pixel = 0;
	img->endian = 0;
	img->line_length = 0;
	img->x = 0;
	img->y = 0;
	img->color = 0xFFC0CB;
	// player->color =0xFF5733; 
	img->i = 0;
	img->j = 0;
}

void					my_mlx_pixel_put(t_data *data, int x, int y, unsigned int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void draw_square(t_data *img, int i, int j, int scale)
{
	int i2 = i * scale;
	int j2 = j * scale;
	while (i2 < (i + 1) * scale)
	{
		j2 = j * scale;
		while (j2 < (j + 1) * scale)
		{
			my_mlx_pixel_put(img, i2, j2, img->color);
			j2++;
		}
		i2++;
	}
}


void	find_player(t_data *img)
{	
	while (img->i < 7)
	{
		while (img->j < 7)
		{
			if (img->map[img->i][img->j] == 'p')
			{
				img->x = img->i;
				img->y = img->j;
				img->map[img->i][img->j] = '0';
			}
			img->j++;
		}
		img->j = 0;
		img->i++;
	}
	img->i = 0;
	img->j = 0;
}

void draw_map(t_data *img)
{
	while (img->i < 7)
	{
		while (img->j < 7)
		{
			if (img->map[img->i][img->j] == '1')
				draw_square(img, img->i, img->j, 20);
			if (img->map[img->i][img->j] == 'p')
				draw_square(img, img->i, img->j, 20);
			img->j++;
		}
		img->j = 0;
		img->i++;
	}
	// mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
	img->i = 0;
	img->j = 0;
}

void redraw(t_data *img)
{
	img->img = mlx_new_image(img->mlx, 800, 580);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length,
                                 &img->endian);
 	draw_square(img, img->x, img->y, 20);
}

int	win_close(int keycode, t_data *img)
{
	if (keycode == 2)
	{
		if (img->map[img->x+1][img->y] != '1') {
			img->x += 1;
			img->map[img->x][img->y] = 'p';
			img->map[img->x - 1][img->y] = '0';
		}
	}
	if (keycode == 0)
	{
		if (img->map[img->x-1][img->y] != '1') {
			img->x -= 1;
			img->map[img->x][img->y] = 'p';
			img->map[img->x + 1][img->y] = '0';
		}
	}
	if (keycode == 13)
	{
		if (img->map[img->x][img->y-1] != '1') {
			img->y -= 1;
			img->map[img->x][img->y] = 'p';
			img->map[img->x][img->y + 1] = '0';
		}
	}
	if (keycode == 1)
	{
		if (img->map[img->x][img->y+1] != '1') {
			img->y += 1;
			img->map[img->x][img->y] = 'p';
			img->map[img->x][img->y - 1] = '0';
		}
	}
	mlx_destroy_image(img->mlx, img->img);
	redraw(img);
	draw_map(img);
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
	if (keycode == 53)
		exit(0);
	return (0);
}


int main(void)
{
	t_data img;
	int i;
	int j;

	i = 0;
	j = 0;
	int      fd = open("map.txt", O_RDONLY);
	char	  *line = NULL;
	t_list		*head = NULL;

	while (get_next_line(fd, &line))
		ft_lstadd_back(&head, ft_lstnew(line));
	ft_lstadd_back(&head, ft_lstnew(line));
	make_map(&head, ft_lstsize(head), &img);
	ft_initialize(&img);
	img.mlx = mlx_init();
	img.mlx_win = mlx_new_window(img.mlx, 800, 580, "Hey, cutie pie!");
	find_player(&img);
	redraw(&img);
	draw_map(&img);
	mlx_put_image_to_window(img.mlx, img.mlx_win, img.img, 0, 0);
	mlx_hook(img.mlx_win, 2, 1L<<0, win_close, &img);
	mlx_loop(img.mlx);
}