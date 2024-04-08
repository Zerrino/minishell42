/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpetit <lpetit@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:17:05 by lpetit            #+#    #+#             */
/*   Updated: 2024/04/08 12:56:58 by lpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

int	ft_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	if (!tmp)
		return (1);
	while (tmp != NULL)
	{
		printf("%s\n", tmp->env_var);
		tmp = tmp->next;
	}
	return (0);
}
