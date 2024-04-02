/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpetit <lpetit@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 18:21:47 by lpetit            #+#    #+#             */
/*   Updated: 2024/04/02 14:12:57 by lpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

t_env	*ft_getenv(t_env *env, char *str, int c)
{
	t_env	*tmp;
	size_t	i;

	tmp = env;
	while (tmp != NULL)
	{
		i = 0;
		while (tmp->env_var[i] == str[i])
		{
			if (c == 0 && tmp->env_var[i] == '=')
				return (tmp);
			i++;
			if (c == 1 && tmp->env_var[i] == '=' && str[i] == '\0')
				return (tmp);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

int	ft_export(t_command *com, t_minishell *mini)
{
	t_env	*tmp;

	tmp = ft_getenv(mini->env, com->data[0], 0);
	if (tmp != NULL)
	{
		if (update_node(tmp, com->data[0]) != 0)
		{
			ft_clearlst(mini->env);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		tmp = mini->env;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = ft_newnode(com->data[0]);
	}
	return (0);
}
