/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 20:31:29 by alexafer          #+#    #+#             */
/*   Updated: 2024/03/30 02:46:56 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

void	ft_echo(t_command *command)
{
	char	*str;
	int		i;

	i = 0;
	str = ft_calloc(1, sizeof(char));
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
	//ft_printf("%s", command->output_str);
}
