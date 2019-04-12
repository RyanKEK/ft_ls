/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohavryle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 18:33:41 by ohavryle          #+#    #+#             */
/*   Updated: 2019/03/12 18:33:42 by ohavryle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	usage(char c)
{
	ft_putstr("ft_ls: illegal option -- ");
	ft_putchar(c);
	ft_putchar('\n');
	ft_putstr("usage: ./ft_ls [-Ralrt] [file ...]\n");
	exit(42);
}

void	no_file_error(char *file)
{
	ft_putstr("ft_ls: ");
	ft_putstr(file);
	ft_putstr(": No such file or directory\n");
}

int		error(int ac, char **av, char *path)
{
	int				i;
	int				arg;
	DIR				*dir;
	//struct dirent	*dp;
	struct stat		st;

	arg = 0;
	i = 0;
	if (!(dir = opendir(path)))
	{
//		perror("Cannot open a dir");
//		ft_putstr(path);
//		exit(42);
	}
	while (++i < ac)
		if (stat(av[i], &st) < 0 && av[i][0] != '-') {
			no_file_error(av[i]);
		}
	return (0);
}

void	exact_flag(char **av, int i, int j, t_flags *flags)
{
	if (av[i][j] == 'r')
		flags->r = 1;
	else if (av[i][j] == 'R')
		flags->R = 1;
	else if (av[i][j] == 'l')
		flags->l = 1;
	else if (av[i][j] == 't')
		flags->t = 1;
	else if (av[i][j] == 'a')
		flags->a = 1;
	else
		usage(av[i][j]);
}

void	define_flags(t_flags *flags, char **av, int ac)
{
	int i;
	int arg;
	int j;

	j = 0;
	i = 0;
	arg = 0;
	while (++i < ac)
	{
		j = 0;
		if (av[i][0] != '-')
			arg++;
		if (av[i][0] == '-' && arg == 0)
		{
			while (av[i][++j])
				exact_flag(av, i, j, flags);
		}
		else if (av[i][0] == '-' && arg != 0)
			no_file_error(av[i]);
	}
}
