/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohavryle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 18:21:25 by ohavryle          #+#    #+#             */
/*   Updated: 2019/04/11 18:21:27 by ohavryle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*str_move(char *str, size_t i)
{
	int		j;
	size_t	len;

	j = 0;
	len = ft_strlen(str);
	while (i < len)
		str[j++] = str[++i];
	if (j == 0)
		ft_bzero(str, ft_strlen(str));
	else
		ft_bzero(str + j + 1, len - j);
	i = 0;
	while (str[i])
	{
		if (str[i] == ':' && str[i + 3] == ' ')
		{
			str[i] = '\0';
			break ;
		}
		i++;
	}
	return (str);
}

void	str_swap(char **str1, char **str2)
{
	char *tmp;

	tmp = *str1;
	*str1 = *str2;
	*str2 = tmp;
}

char 	*strconcat(char *str, char *str1, char *str2)
{
	char *tmp;

	tmp = (char*)malloc(sizeof(char) * (ft_strlen(str) + ft_strlen(str1) + ft_strlen(str2) + 1));
	ft_strcpy(tmp, str);
	ft_strcat(tmp, str1);
	ft_strcat(tmp, str2);
	tmp[ft_strlen(str) + ft_strlen(str1)+ ft_strlen(str2)] = '\0';
	return (tmp);
}

void	sort_2d(char **arr, int len, t_flags flags)
{
	int c;
	int i;

	while (1)
	{
		i = -1;
		c = 0;
		while (++i + 1 < len)
		{
			if (ft_strcmp(arr[i], arr[i + 1]) > 0 && flags.r == 0)
			{
				c++;
				str_swap(&arr[i], &arr[i + 1]);
			}
			else if (ft_strcmp(arr[i], arr[i + 1]) < 0 && flags.r == 1)
			{
				c++;
				str_swap(&arr[i], &arr[i + 1]);
			}
		}
		if (c == 0)
			break ;
	}
}
