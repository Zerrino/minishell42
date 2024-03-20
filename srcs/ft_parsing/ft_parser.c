/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:47:31 by alexafer          #+#    #+#             */
/*   Updated: 2024/03/20 16:22:30 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

void	ft_parser(t_minishell *mini, char *input)
{
	t_command	command;
	int	i;

	printf("Parsing : %s\n", input);
	if (!input)
	{
		mini->stop = 1;
		return ;
	}
	i = 0;
	while (input[i] != ' ' && input[i] != '\0')
	{
		command.command[i] = input[i];
		i++;
	}
	command.command[i] = '\0';
	if (command.command[i] == input[i])
	{
		command.option = 0;
	}
	command.data = split(input);
	printf("command : %s\n", command.command);
	return ;
}
