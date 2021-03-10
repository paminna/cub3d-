/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paminna <paminna@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 19:11:09 by paminna           #+#    #+#             */
/*   Updated: 2021/02/18 14:41:12 by paminna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_data	*make_map(t_list **head, int size, t_data *img)
{
	int		  i = -1;
	t_list	*tmp = *head;

	img->map = ft_calloc(size + 1, sizeof(char *));
	while (tmp)
	{
		img->map[++i] = tmp->content;
		tmp= tmp->next;
	}
	img->map[++i] = NULL;
	return (img);
}
