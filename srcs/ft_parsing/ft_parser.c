/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:47:31 by alexafer          #+#    #+#             */
/*   Updated: 2024/03/24 23:13:27 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

void	ft_parser(t_minishell *mini, char *input)
{
	t_command	command;
	char		**split;
	int			i;
	int			j;
	int			option;

	printf("Parsing : %s\n", input);
	if (!input)
	{
		mini->stop = 1;
		return ;
	}
	if (input[0] == 0)
		return ;
	i = 0;
	while (input[i] != ' ' && input[i] != '\0')
	{
		command.command[i] = input[i];
		i++;
	}
	command.command[i] = '\0';
	if (command.command[i] == input[i])
		command.option = 0;
	split = ft_split(input, ' ');
	i = 1;
	while (split[i])
	{
		option = 1;
		j = 0;
		while (split[i][j] && option)
		{
			if ((j == 0 && split[i][j] == '-'))
				;
			else if (split[i][j] == 'n')
				option = 1;
			else
				option = 0;
			j++;
		}
		if (option == 0)
			break ;
		i++;
	}
	if (i > 1)
		command.option = "n";
	else
		command.option = 0;
	command.data = &split[i];
	//printf("command : %s\n", command.command);
	//printf("option : %s\n", command.option);
	//printf("data : %s\n", command.data[0]);
	ft_take_action(&command, mini);
	return ;
}
