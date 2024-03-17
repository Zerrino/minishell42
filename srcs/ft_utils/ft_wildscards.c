/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildscards.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 15:19:31 by alexafer          #+#    #+#             */
/*   Updated: 2024/03/17 15:33:16 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

int	ft_wildscards(char *str, char *str_wild)
{
	char **split;
	int	j;
	int	n;
	int	i;

	n = 0;
	i = 0;
	j = 0;
	split = ft_split(str_wild, '*');

	while (split[i] && str[j])
	{
		while (str[])
		ft_printf("%s\n", split[i]);
		i++;
	}
	//printf("nb : %d\n", n);

	return (0);
}
