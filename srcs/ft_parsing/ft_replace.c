/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 17:34:02 by alexafer          #+#    #+#             */
/*   Updated: 2024/04/05 18:44:27 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

static void	ft_rep_u(int *quote)
{
	if (!(*quote))
		*quote = 2;
	else
		*quote = 0;
}

void	ft_replace_quote(char *str)
{
	int	quote;
	int	i;

	quote = 0;
	i = 0;
	while (str[i])
	{
		if ((quote == 0 || quote == 1) && str[i] == '"')
			quote = !quote;
		else if ((quote == 0 || quote == 2) && str[i] == 39)
			ft_rep_u(&quote);
		else if (quote && str[i] == ' ')
			str[i] = 31;
		else if (quote && str[i] == '|')
			str[i] = 30;
		else if (quote == 2 && str[i] == '$')
			str[i] = 29;
		else if (quote && str[i] == '~')
			str[i] = 28;
		i++;
	}
}

void	ft_reverse_quote(char *str)
{
	int	quote;
	int	i;

	quote = 0;
	i = 0;
	while (str[i])
	{
		if ((quote == 0 || quote == 1) && str[i] == '"')
			quote = !quote;
		else if ((quote == 0 || quote == 2) && str[i] == 39)
			ft_rep_u(&quote);
		else if (quote && str[i] == 31)
			str[i] = ' ';
		else if (quote && str[i] == 30)
			str[i] = '|';
		else if (quote == 2 && str[i] == 29)
			str[i] = '$';
		else if (quote && str[i] == 28)
			str[i] = '~';
		i++;
	}
}
