/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohavryle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 13:52:52 by ohavryle          #+#    #+#             */
/*   Updated: 2019/04/08 13:52:54 by ohavryle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	error_message(const char *str)
{
	ft_putstr(str);
	exit(42);
}

void	is_error(int ac, char **av)
{
	int fd;
	char *line;
	int i;
	int empty_cell;

	empty_cell = 0;
	if (ac < 2)
		error_message("Usage: ./wolf3d map [texture1 texture 2 ...]\n");
	if (ac > 11)
		error_message("Sorry, but no more than 9 textures is supported :(\n");
	if ((fd = open(av[1], O_RDONLY)) < 0)
	{
		ft_putstr("No such file: ");
		ft_putstr(av[1]);
		ft_putchar('\n');
		exit(42);
	}
	while (get_next_line(fd, &line) > 0)
	{
		i = -1;
		while (line[++i])
			if (line[i] == '0')
				empty_cell++;
		free(line);
	}
	if (!empty_cell)
		error_message("Unfortunately, this map has no empty cells!\n");
}
