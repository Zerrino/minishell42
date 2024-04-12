/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildscards.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 15:19:31 by alexafer          #+#    #+#             */
/*   Updated: 2024/03/20 04:06:52 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

/*
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
	if (first == 0)
	{
		if (ft_strncmp(&str[j], split[i], ft_strlen(split[i])))
		{
			ft_free_split(split);
			return (0);
		}
	}
	while (split[i] && str[j])
	{
		while (str[j] && (str[j] != split[i][0]) && (i > 0 || first))
			j++;
		if (!str[j])
			break ;
		if (ft_strncmp(&str[j], split[i], ft_strlen(split[i])))
			j++;
		else
		{
			j += ft_strlen(split[i]);
			i++;
			if (split[i] == 0 && last == 0 && str[j])
			{
				if ((first || i > 1) && !(ft_strncmp(&str[ft_strlen(str)
				 - ft_strlen(split[i - 1])], split[i - 1], ft_strlen(split[i - 1]))))
					return (1);
				if (ft_strncmp(&str[j], split[i - 1], ft_strlen(split[i - 1])))
					return (0);
				return (0);
			}
		}
	}
	if (split[i] && ft_strncmp(&str[ft_strlen(str) - ft_strlen(split[i])]
	, split[i], ft_strlen(split[i])))
		return (0);
	if (split[i] && !last)
		return (0);
	return (1);
}
*/
