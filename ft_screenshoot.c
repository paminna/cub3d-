/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_screenshoot.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paminna <paminna@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 19:52:30 by paminna           #+#    #+#             */
/*   Updated: 2021/03/28 18:03:31 by paminna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void ft_header(t_img *win, int fd)
{
	int size;

	write(fd, "BM", 2);
	size = 14 + 40 + win->height * win->width * win->bits_per_pixel / 8;
	write(fd, &size, 4);
	size = 0;
	write(fd, &size, 4);
	size = 54;
	write(fd, &size, 4);
	size = 40;
	write(fd, &size, 4);
	write(fd, &win->width, 4);
	write(fd, &win->height, 4);
	size = 1;
	write(fd, &size, 2);
	write(fd, &win->bits_per_pixel, 2);
	// write(fd, &size, 12);
	size = 0;
	write(fd, &size, 24);
}

void make_screenshoot(t_data *img)
{
	int		i;
	char	*file;
	int		fd;
	
	file = (char*)"screen.bmp";
	if ((fd = open(file, O_RDWR | O_TRUNC | O_CREAT, 0777)) < 0)
		ft_errors("can't open file");
	ft_header(&img->win, fd);
	i = img->win.height;
	while (i > 0)
	{
		write(fd, (img->win.addr + i * img->win.line_length), (img->win.width * img->win.bits_per_pixel / 8));
		i--;
	}
	close (fd);
	// mlx_destroy_image(img->mlx, img->win.img);
	exit(0);
}