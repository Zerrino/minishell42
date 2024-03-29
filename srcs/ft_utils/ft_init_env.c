/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpetit <lpetit@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 15:35:55 by lpetit            #+#    #+#             */
/*   Updated: 2024/03/29 13:45:24 by lpetit           ###   ########.fr       */
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
		free(node->env_var);
		free(node);
		node = tmp;
	}
}

t_env	*init_env_var(t_minishell *mini, char **env)
{
	t_env	*tmp;
	t_env	*node;
	int	env_len;
	int	i;

	i = 0;
	env_len = 0;
	while (env[env_len])
		env_len++;
	node = ft_newnode(env[i]);
	if (!node)
		exit(EXIT_FAILURE);
	tmp = node;
	i++;
	while (i < env_len)
	{
		node->next = ft_newnode(env[i]);
		if (!node)
		{
			ft_clearlst(tmp);
			exit(EXIT_FAILURE);
		}
		node = node->next;
		i++;
	}
	return (tmp);
}
