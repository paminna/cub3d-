/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_screenshoot.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paminna <paminna@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 19:52:30 by paminna           #+#    #+#             */
/*   Updated: 2021/04/03 18:39:03 by paminna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_close(void)
{
	exit(0);
	return (0);
}

void	ft_errors(char *ans)
{
	int i;

	i = 0;
	write(1, "Error\n", 6);
	while (*ans != '\0')
		write(1, &(*ans++), 1);
	exit(0);
}

void	ft_header(t_img *win, int fd)
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
	size = 0;
	write(fd, &size, 24);
}

void	make_screenshoot(t_data *img)
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
		write(fd, (img->win.addr + i * img->win.line_length),
		(img->win.width * img->win.bits_per_pixel / 8));
		i--;
	}
	close(fd);
	exit(0);
}
