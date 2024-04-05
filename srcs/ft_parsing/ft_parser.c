/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:47:31 by alexafer          #+#    #+#             */
/*   Updated: 2024/04/05 17:53:52 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

// 31 30 29 28
void	ft_all_parser(t_minishell *mini, char *input)
{
	t_command	*command;
	char	**splited;
	int		i;
	int		max;

	if (ft_empty_par(mini, input))
		return ;
	i  = 0;
	ft_replace_quote(input);
	splited = ft_split(input, '|');
	while (splited[i])
		i++;
	max = i;
	command = (t_command *)malloc(sizeof(t_command) * (i));
	if (!command)
		return ;
	i = 0;
	while (i < max)
	{
		command[i].in = 0;
		command[i].next = 1;
		if (i + 1 == max)
			command[i].next = 0;
		if (i > 0)
		{
			if (command[i - 1].next == 1)
				command[i].in = command[i - 1].output_str;
		}
		ft_parser(mini, splited[i], &command[i]);
		mini->status_com = command[i].status;
		if (mini->stop)
			return ;
		i++;
	}
	//ft_parser(mini, input, &command);
}
