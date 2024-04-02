/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_converter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpetit <lpetit@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:15:30 by lpetit            #+#    #+#             */
/*   Updated: 2024/04/02 14:38:33 by lpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

void	test_converter(t_minishell *mini, t_command *com)
{
	char	*str;
	char	*to_test;
	size_t	i;

	i = 0;
	str = ft_strdup("");
	while (com->data[i])
	{
		str = ft_strjoin_f(str, com->data[i]);
		i++;
	}
	to_test = converter(mini, str);
	printf("%s\n", to_test);
	free(to_test);
	return ;
}
