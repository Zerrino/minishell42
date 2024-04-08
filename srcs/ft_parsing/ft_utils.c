/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 17:51:40 by alexafer          #+#    #+#             */
/*   Updated: 2024/04/05 19:19:56 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

int	ft_in_arr(int nb, int *array)
{
	int	i;

	i = 0;
	while (array[i] != -1)
	{
		if (nb == array[i])
			return (1);
		i++;
	}
	return (0);
}

static int	ft_get_u(char **split, int i, int *array_max[2])
{
	int	j;

	j = 0;
	while (split[i])
	{
		if (!ft_in_arr(i, array_max[0]) && !ft_in_arr(i, array_max[1]))
			j++;
		i++;
	}
	return (j);
}

char	**ft_get_data(char **split, t_command *command, int l, int *a[2])
{
	char	**result;
	int		i;
	int		j;

	i = l;
	j = ft_get_u(split, i, a);
	result = (char **)malloc(sizeof(char *) * (j + 1));
	if (!result)
		return (0);
	i = l;
	j = 0;
	while (split[i])
	{
		if (!ft_in_arr(i, a[0]) && !ft_in_arr(i, a[1]))
		{
			result[j] = split[i];
			j++;
		}
		i++;
	}
	result[j] = 0;
	return (result);
}
