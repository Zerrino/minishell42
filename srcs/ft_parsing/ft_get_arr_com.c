/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_arr_com.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 17:50:15 by alexafer          #+#    #+#             */
/*   Updated: 2024/04/05 18:10:45 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

static void	ft_static_com(char **splited, int *nb)
{
	int	i;
	int	x;

	i = 0;
	while (splited[i])
	{
		if (ft_strchr(splited[i], '>'))
		{
			x = 0;
			if (splited[i][1] == '>')
				x = 1;
			if (!splited[i][1 + x])
				(*nb)++;
			(*nb)++;
		}
		i++;
	}
}

static int	*ft_static_com_2(char **splited, int *array, int i)
{
	int	x;
	int	j;

	x = 0;
	j = 0;
	while (splited[i])
	{
		if (ft_strchr(splited[i], '>'))
		{
			x = 0;
			if (splited[i][1] == '>')
				x = 1;
			if (!splited[i][1 + x])
				array[j++] = i + 1;
			array[j] = i;
			j++;
		}
		i++;
	}
	array[j] = -1;
	return (array);
}

int	*ft_get_arr_com(t_minishell *mini, t_command *command, char *input)
{
	char	**splited;
	int		*array;
	int		nb;
	int		i;

	(void)mini;
	(void)command;
	nb = 0;
	splited = ft_split(input, ' ');
	ft_static_com(splited, &nb);
	array = (int *)malloc(sizeof(int) * (nb + 1));
	if (!array)
		return (0);
	i = 0;
	array = ft_static_com_2(splited, array, i);
	ft_free_split(splited);
	return (array);
}
