/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 17:48:44 by alexafer          #+#    #+#             */
/*   Updated: 2024/04/05 18:37:33 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

static void	ft_util_com(int *i, int *doub)
{
	*doub = 1;
	*i += 1;
}

int	ft_output_com(t_minishell *mini, char *input)
{
	char	**splited;
	int		i;
	int		doub;
	int		output;

	i = 0;
	output = 1;
	while (input[i])
	{
		if (input[i] == '>')
		{
			doub = 0;
			if (output != 1)
				close(output);
			if (input[i + 1] == '>')
				ft_util_com(&i, &doub);
			splited = ft_split(&input[i + 1], ' ');
			output = ft_redir_right(splited[0], doub);
			ft_free_split(splited);
			if (output == -1)
				return (-1);
		}
		i++;
	}
	return (output);
}

char	*ft_input_dir(t_minishell *mini, char *input)
{
	char	**splited;
	int		i;
	int		doub;
	char	*output;

	i = 0;
	output = 0;
	while (input[i])
	{
		if (input[i] == '<')
		{
			doub = 0;
			if (input[i + 1] == '<')
				ft_util_com(&i, &doub);
			splited = ft_split(&input[i + 1], ' ');
			if (output)
				free(output);
			output = ft_redir_left(splited[0], doub);
			ft_free_split(splited);
			if (output == 0)
				return (0);
		}
		i++;
	}
	return (output);
}
