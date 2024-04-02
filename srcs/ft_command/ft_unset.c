/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpetit <lpetit@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 12:33:11 by lpetit            #+#    #+#             */
/*   Updated: 2024/03/31 16:18:09 by lpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

int	ft_unset(t_command *com, t_minishell *mini)
{
	t_env	*tmp;
	t_env	*to_unset;

	printf("%s\n", com->data[0]);
	tmp = mini->env;
	to_unset = ft_getenv(mini->env, com->data[0], 1);
	if (to_unset != NULL)
	{
		while (tmp->next != to_unset)
			tmp = tmp->next;
		tmp->next = to_unset->next;
		free(to_unset->env_var);
		free(to_unset);
	}
	return (0);
}
