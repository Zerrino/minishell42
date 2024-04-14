/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_i.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 00:21:07 by alexafer          #+#    #+#             */
/*   Updated: 2024/04/14 18:25:17 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

void	parser_init(t_minishell *mini, char **input, t_command *c, int nom)
{
	char	*ou;

	mini->nom = nom;
	c->nom = nom;
	*input = converter(mini, *input);
	if (ft_empty_par(mini, *input))
	{
		c->op = -1;
		return ;
	}
	c->op = 1;
	c->op = ft_output_com(c, *input);
	ou = ft_input_dir(mini, c, *input);
	if (ou)
		c->in = ou;
}
