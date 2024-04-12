/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 05:47:51 by alexafer          #+#    #+#             */
/*   Updated: 2024/04/12 06:35:24 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

static int	ft_change_len(char *str, char c)
{
	int	i;
	int	max;

	i = 0;
	max = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != c && str[i + 1] == c)
			max++;
		i++;
	}
	max += i;
	return (max);
}

char	*ft_change_input(char *str, char c)
{
	char	*result;
	int		i;
	int		j;
	int		max;

	max = ft_change_len(str, c);
	result = (char *)malloc(sizeof(char) * (max + 1));
	if (!result)
		return (0);
	j = 0;
	i = 0;
	while (str[i])
	{
		result[j] = str[i];
		j++;
		if (str[i] != ' ' && str[i] != c && str[i + 1] == c)
		{
			result[j] = ' ';
			j++;
		}
		i++;
	}
	free(str);
	result[j] = '\0';
	return (result);
}
