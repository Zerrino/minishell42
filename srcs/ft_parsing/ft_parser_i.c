/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_i.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 00:21:07 by alexafer          #+#    #+#             */
/*   Updated: 2024/04/11 00:23:12 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

void	parser_init(t_minishell *mini, char **input, t_command *command)
{
	char	*ou;

	*input = converter(mini, *input);
	if (ft_empty_par(mini, *input))
	{
		command->op = -1;
		return ;
	}
	command->op = 1;
	command->op = ft_output_com(mini, command, *input);
	ou = ft_input_dir(mini, command, *input);
	if (ou)
		command->in = ou;
}
