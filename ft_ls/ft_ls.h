/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohavryle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 17:49:40 by ohavryle          #+#    #+#             */
/*   Updated: 2019/03/09 17:49:44 by ohavryle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include <dirent.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft/libft.h"
# include <sys/ioctl.h>
# include <sys/stat.h>
#include <stdio.h>
typedef struct	s_flags
{
	int r;
	int R;
	int a;
	int l;
	int t;
}				t_flags;

void	define_flags(t_flags *flags, char **av, int ac);
int		error(int ac, char **av, char *path);
char	*str_move(char *str, size_t i);
void	str_swap(char **str1, char **str2);
char 	*strconcat(char *str, char *str1, char *str2);
void	sort_2d(char **arr, int len, t_flags flags);
char	*true_filename(char *str);

#endif
