/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpetit <lpetit@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 12:33:11 by lpetit            #+#    #+#             */
/*   Updated: 2024/04/08 19:34:56 by lpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

void	ft_unset_env(char *str, t_minishell *mini)
{
	t_env	*tmp;
	t_env	*to_unset;

	tmp = mini->env;
	to_unset = ft_getenv(mini->env, str, 1);
	if (to_unset != NULL)
	{
		if (mini->env != to_unset)
		{
			while (tmp->next != to_unset)
				tmp = tmp->next;
			tmp->next = to_unset->next;
		}
		else
		{
			mini->env = to_unset->next;
		}
		free(to_unset->env_var);
		free(to_unset);
	}
	return ;
}

int	ft_unset(t_command *com, t_minishell *mini)
{
	size_t	i;

	i = 0;
	while (com->data[i])
	{
		ft_unset_env(com->data[i], mini);
		i++;
	}
	return (0);
}
