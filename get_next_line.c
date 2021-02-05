/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paminna <paminna@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 18:47:16 by paminna           #+#    #+#             */
/*   Updated: 2021/02/05 20:35:16 by paminna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	n_in_rem(char *str_n, char **remainder, char **line)
{
	char *tmp;
	char *tmp_2;

	*str_n++ = '\0';
	tmp = *remainder;
	tmp_2 = *line;
	*line = ft_strdup(*remainder);
	if (*line == NULL)
		return (-1);
	*remainder = ft_strdup(str_n);
	if (*remainder == NULL)
		return (-1);
	free(tmp);
	return (1);
}

int	r_less_null(char **remainder)
{
	free(*remainder);
	return (-1);
}

int	r_null(char **line, char **remainder)
{
	*line = ft_strdup(*remainder);
	if (*line == NULL)
		return (-1);
	free(*remainder);
	*remainder = NULL;
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static char *remainder;
	int			r;
	char		*str_n;
	char		buf[BUFFER_SIZE + 1];
	char		*tmp;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	if (remainder == NULL && !(remainder = ft_strdup("")))
		return (-1);
	if ((str_n = ft_strchr(remainder, '\n')))
		return (n_in_rem(str_n, &remainder, line));
	while ((r = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[r] = '\0';
		tmp = remainder;
		remainder = ft_strjoin(remainder, buf);
		if (remainder == NULL)
			return (-1);
		free(tmp);
		if ((str_n = ft_strchr(remainder, '\n')))
			return (n_in_rem(str_n, &remainder, line));
	}
	return ((r < 0) ? r_less_null(&remainder) : r_null(line, &remainder));
}
