/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildscards.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 15:19:31 by alexafer          #+#    #+#             */
/*   Updated: 2024/03/18 03:18:40 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

int	ft_first_start(char *str)
{
	if (!str)
		return (0);
	return (str[0] == '*');
}

int	ft_last_star(char *str)
{
	int	i;
	int	l;

	if (!str)
		return (0);
	l = ft_strlen(str);
	i = 0;
	while (i < (l - 1))
		i++;
	return (str[i] == '*');
}

int	ft_lastsplit(char **split)
{
	int	i;

	i = 0;
	if (!split || !split[0])
		return (0);
	while (split[i])
		i++;
	return (i - 1);
}

int	ft_return_v(int last, char *str, char **split, int i, int j)
{
	char	*str_2;
	int		len;

	len = ft_strlen(split[ft_lastsplit(split)]);
	str_2 = &str[ft_strlen(str) - len];
	if (!last && !ft_strncmp(str_2, split[ft_lastsplit(split)], len))
		return (1);
	if (split[i] || ft_strlen(&str[j]) && !last)
		return(0);
	return (1);
}

int	ft_wildscards(char *str, char *str_wild)
{
	char **split;
	int	j;
	int	i;
	int	first;
	int	last;

	i = 0;
	j = 0;
	split = ft_split(str_wild, '*');
	first = ft_first_start(str_wild);
	last = ft_last_star(str_wild);
	while (split[i] && str[j])
	{
		while ((!(!first && i == 0)) && str[j] && (str[j] != split[i][0]))
			j++;
		if (ft_strncmp(&str[j], split[i], ft_strlen(split[i])))
			j++;
		else
		{
			j += ft_strlen(split[i]);
			i++;
		}
	}
	return (ft_return_v(last, str, split, i, j));
}
