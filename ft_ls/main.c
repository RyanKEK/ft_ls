/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohavryle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 14:36:54 by ohavryle          #+#    #+#             */
/*   Updated: 2019/03/19 14:37:05 by ohavryle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_ls.h"
#include <time.h>
#include <pwd.h>
#include <grp.h>

char	*true_filename(char *str)
{
	size_t i;

	i = ft_strlen(str);
	while (--i > 0)
		if (str[i] == '/')
			break ;
	if (i == 0)
		return (str);
	else
		return (str + i + 1);
}

void	free_2d(char **arr, int len)
{
	int i;

	i = -1;
	while (++i < len)
		free(arr[i]);
	free(arr);
}

void	ft_putstrs(char *str1, char *str2)
{
	ft_putstr(str1);
	ft_putstr(str2);
}

int		max_len(char **arr, int arr_len)
{
	int	max;
	int	len;
	int	i;

	i = -1;
	max = 0;
	while (++i < arr_len)
	{
		len = (int)ft_strlen(arr[i]);
		if (max < len)
			max = len;
	}
	return (max);
}

char	**output_array(char *arg, t_flags flags)
{
	DIR				*dir;
	struct dirent	*dp;
	int 			arr_len;
	char			**arr;
	int 			i;

	arr_len = 0;
	i = 0;
	if (!(dir = opendir(arg)))
	{
		perror("Cannot open a dir");
		exit(42);
	}
	while ((dp = readdir(dir)))
	{
		if (flags.a == 0 && dp->d_name[0] == '.')
			continue ;
		else
			arr_len++;
	}
	closedir(dir);
	arr = (char**)malloc(sizeof(char*) * arr_len + 1);
	dir = opendir(arg);
	while ((dp = readdir(dir)))
	{
		if (flags.a == 0 && dp->d_name[0] == '.')
			continue ;
		else
		{
			arr[i] = (char*)malloc(sizeof(char) * ft_strlen(strconcat(arg, "/", dp->d_name) + 1));
			ft_strcpy(arr[i], strconcat(arg, "/", dp->d_name));
			arr[i][ft_strlen(strconcat(arg, "/", dp->d_name))] = '\0';
			i++;
		}
	}
	arr[i] = NULL;
	sort_2d(arr, arr_len, flags);
	return (arr);
}

void	print_permissions(struct stat st)
{
	ft_putstr((S_ISDIR(st.st_mode)) ? "d" : "-");
	ft_putstr((S_IRUSR & st.st_mode) ? "r" : "-");
	ft_putstr((S_IWUSR & st.st_mode) ? "w" : "-");
	ft_putstr((S_IXUSR & st.st_mode) ? "x" : "-");
	ft_putstr((S_IRGRP & st.st_mode) ? "r" : "-");
	ft_putstr((S_IWGRP & st.st_mode) ? "w" : "-");
	ft_putstr((S_IXGRP & st.st_mode) ? "x" : "-");
	ft_putstr((S_IROTH & st.st_mode) ? "r" : "-");
	ft_putstr((S_IWOTH & st.st_mode) ? "w" : "-");
	ft_putstr((S_IXOTH & st.st_mode) ? "x" : "-");
}

void 	ls_l(char **arr, int arr_len)
{
	int				i;
	int				j;
	struct stat		st;
	size_t 			max_links;
	size_t 			max_size;
	struct passwd	*pwd;
	struct group	*grp;
	long 			total;

	total = 0;
	max_links = 1;
	max_size = 1;
	i = -1;
	while (++i < arr_len)
	{
		stat(arr[i], &st);

		total += st.st_blocks;
		if (max_links < ft_strlen(dec_to_any(st.st_nlink, 10)))
			max_links = ft_strlen(dec_to_any(st.st_nlink, 10));
		if (max_size < ft_strlen(dec_to_any(st.st_size, 10)))
			max_size = ft_strlen(dec_to_any(st.st_size, 10));
	}
	i = -1;
	ft_putstr("total ");
	ft_putnbr(total);
	ft_putchar('\n');
	while (++i < arr_len)
	{
		j = -1;
		stat(arr[i], &st);
		if (!(pwd = getpwuid(st.st_uid)))
			ft_putstr("pwd error\n");
		if (!(grp = getgrgid(st.st_gid)))
			ft_putstr("grp error\n");
		print_permissions(st);
		while (++j < (int)(max_links + 2 - ft_strlen(dec_to_any(st.st_nlink, 10))))
			ft_putchar(' ');
		ft_putnbr(st.st_nlink);
		ft_putchar(' ');
		ft_putstr(pwd->pw_name);
		ft_putstr("  ");
		ft_putstr(grp->gr_name);
		j = -1;
		while (++j < (int)(max_size + 2 - ft_strlen(dec_to_any(st.st_size, 10))))
			ft_putchar(' ');
		ft_putnbr(st.st_size);
		ft_putchar(' ');
		ft_putstr(str_move(ctime(&st.st_mtimespec.tv_sec), 3));
		ft_putchar(' ');
		j = ft_strlen(arr[i]);
		while (arr[i][--j] != '/')
			;
		ft_putstr(arr[i] + j + 1);
		ft_putchar('\n');
	}

}

int		ls_output(char **arr, int arr_len)
{
	struct winsize	ws;
	int				max;
	int				len;
	int				space;
	int				i;
	size_t			j;

	i = -1;
	len = 0;
	max = max_len(arr, arr_len);
	ioctl(0, TIOCGWINSZ, &ws);
	while (++i < arr_len)
	{
		j = ft_strlen(arr[i]);
		while (arr[i][--j])
			if (arr[i][j] == '/')
				break ;
		space = max - (int)ft_strlen(arr[i]) + 4;
		if (space < 4)
		{
			printf("gg\n");
			exit(42);
		}
		if (ws.ws_col - len < max + 7)
		{
			len = 0;
			write(1, "\n", 1);
		}
		write(1, str_move(arr[i], j), ft_strlen(arr[i]));
		len += ft_strlen(arr[i]);
		while (space--)
		{
			len++;
			write(1, " ", 1);
		}
	}
	if (arr_len > 0)
		write(1, "\n", 1);
	if (max == 0)
		return (0);
	return (1);
}

int 	ls_R(char *arg, t_flags flags, char **arr, int arr_len)
{
	DIR				*dir;
	struct dirent	*dp;
	static int c = 0;

	if (!(dir = opendir(arg)))
	{
		perror("Cannot open a dir: ");
		ft_putstr(arg);
		exit(42);
	}
	if (c == 0 && flags.l == 0)
		ls_output(arr, arr_len);
	else if (c == 0 && flags.l == 1)
		ls_l(arr, arr_len);
	c++;
	while ((dp = readdir(dir)))
	{
		if (!ft_strcmp(dp->d_name, ".") || !ft_strcmp(dp->d_name, ".."))
			continue ;
		else if (flags.a == 0 && dp->d_name[0] == '.')
			continue ;
		else
		{
			if (opendir(strconcat(arg, "/", dp->d_name)))
			{
				arr_len = 0;
				ft_putstr("\n");
				ft_putstrs(arg, "/");
				ft_putstr(dp->d_name);
				ft_putstr(":\n");
				arr = output_array(strconcat(arg, "/", dp->d_name), flags);
				while (arr[arr_len])
					arr_len++;
				if (flags.l == 1 && arr_len > 0)
					ls_l(arr, arr_len);
				else if (ls_output(arr, arr_len) && arr_len > 0)
					ft_putchar('\n');
				ls_R(strconcat(arg, "/", dp->d_name), flags, arr, arr_len);
			}
		}
	}
	return (0);
}

int		main(int ac, char **av)
{
	int			i;
	t_flags		flags;
	struct stat	st;
	char		**arr;
	int			arr_len;
	int 		args;

	flags.r = 0;
	flags.R = 0;
	flags.t = 0;
	flags.a = 0;
	flags.l = 0;
	args = 0;
	i = 0;
	while (++i < ac)
		if (av[i][0] != '-'){
			args++;
		}
	define_flags(&flags, av, ac);
	error(ac, av, av[i]);
	arr_len = 0;
	if (!args)
	{
		arr = output_array(".", flags);
		while (arr[arr_len])
			arr_len++;
		if (flags.R == 1)
			ls_R(".", flags, arr, arr_len);
		else if (flags.l == 1)
			ls_l(arr, arr_len);
		else
			ls_output(arr, arr_len);
	}
	else
	{
		i = 0;
		while (++i < ac)
		{
			arr_len = 0;
			if (stat(av[i], &st) < 0 || av[i][0] == '-')
				continue ;
			arr = output_array(av[i], flags);
			while (arr[arr_len])
				arr_len++;
			if (flags.R == 1)
				ls_R(av[i], flags, arr, arr_len);
			else if (flags.l == 1)
				ls_l(arr, arr_len);
			else
				ls_output(arr, arr_len);
			free_2d(arr, arr_len);
		}
	}
	return (0);
}
