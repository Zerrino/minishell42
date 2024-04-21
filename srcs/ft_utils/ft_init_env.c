/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpetit <lpetit@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 15:35:55 by lpetit            #+#    #+#             */
/*   Updated: 2024/04/20 16:22:39 by lpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

t_env	*ft_newnode(char *str)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->env_var = ft_strdup(str);
	node->exp = 1;
	node->next = NULL;
	return (node);
}

int	update_node(t_env *node, char *str)
{
	char	*tmp;

	tmp = node->env_var;
	node->env_var = ft_strdup(str);
	if (node->env_var == NULL)
	{
		node->env_var = tmp;
		return (1);
	}
	else
	{
		free(tmp);
		node->exp = 1;
		return (0);
	}
}

void	ft_clearlst(t_env *node)
{
	t_env	*tmp;

	if (!node)
		return ;
	while (node != NULL)
	{
		tmp = node->next;
		if (node->env_var != NULL)
			free(node->env_var);
		free(node);
		node = tmp;
	}
}

t_env	*init_env_var(char **env)
{
	t_env	*tmp;
	t_env	*node;
	int		i;

	i = 0;
	if (env == NULL)
		return (NULL);
	node = ft_newnode(env[i]);
	if (!node)
		return (NULL);
	tmp = node;
	i++;
	while (env[i])
	{
		node->next = ft_newnode(env[i]);
		if (!node->next || !node->next->env_var)
		{
			ft_clearlst(tmp);
			return (NULL);
		}
		node = node->next;
		i++;
	}
	return (tmp);
}
