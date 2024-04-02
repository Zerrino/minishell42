/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 20:31:29 by alexafer          #+#    #+#             */
/*   Updated: 2024/04/02 17:20:40 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

void	ft_echo(t_command *command)
{
	char	*str;
	int		i;

	i = 0;
	str = ft_calloc(1, sizeof(char));
	if (str)
	{
		while (command->data[i])
		{
			str = ft_strjoin_f(str, command->data[i]);
			if (command->data[i + 1])
				str = ft_strjoin_f(str, " ");
			i++;
		}
		if (!command->option)
			str = ft_strjoin_f(str, "\n");
		command->output_str = str;
		command->status = 0;
	}
	else
	{
		command->output_str = 0;
		command->status = 1;
	}
}
