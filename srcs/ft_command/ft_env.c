/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpetit <lpetit@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:17:05 by lpetit            #+#    #+#             */
/*   Updated: 2024/03/26 18:21:22 by lpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

int	ft_env(t_minishell *mini)
{
	size_t	i;

	i = 0;
	while (mini->env_var[i])
	{
		printf("%s\n", mini->env_var[i]);
		i++;
	}
	return (0);
}
