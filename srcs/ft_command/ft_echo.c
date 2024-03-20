/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 20:31:29 by alexafer          #+#    #+#             */
/*   Updated: 2024/03/20 20:56:05 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

void	ft_echo(t_command *command)
{
	char	*str;
	char	*str2;
	int	i;
	i = 0;
	str = 0;
	str2 = 0;
	while (command->data[i])
	{
		ft_printf("%s", command->data[i]);
		str = str2;
		str = ft_strjoin(str, command->data[i]);
		free(str2);
		if (command->data[i + 1])
		{
			ft_printf(" ");
			str = str2;
			str = ft_strjoin(str, " ");
			free(str2);
		}
		i++;
	}
	if (!command->option)
	{
		str = str2;
		str2 = ft_strjoin(str2, "\n");
		free(str);
	}
	command->output_str = str2;
	printf("\nDEUXIEME : %s", command->output_str);
}
