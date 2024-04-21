/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpetit <lpetit@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 18:21:47 by lpetit            #+#    #+#             */
/*   Updated: 2024/04/21 15:52:36 by lpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

t_env	*ft_getenv(t_env *env, char *str, int c)
{
	t_env	*tmp;
	size_t	i;

	if (!env)
		return (NULL);
	tmp = env;
	c = 0;
	c++;
	while (tmp != NULL)
	{
		i = 0;
		while (tmp->env_var[i] == str[i])
		{
			if ((tmp->env_var[i] == '\0' || tmp->env_var[i] == '=') 
				&& (str[i] == '\0' || str[i] == '='))
				return (tmp);
			i++;
			if ((tmp->env_var[i] == '\0' || tmp->env_var[i] == '=') 
				&& (str[i] == '\0' || str[i] == '='))
				return (tmp);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

int	has_equal_sign(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	check(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if ((!(ft_isalnum(str[i])) && str[i] != '_')
			|| !(ft_isalpha(str[0])))
		{
			if (str[i] == '+' && str[i + 1] == '=' && str[0] != '+')
				break ;
			if (str[i] == '=' && str[0] != '+' && str[0] != '=')
				break ;
			ft_error_export(str);
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_export_env(char *str, t_minishell *mini)
{
	t_env	*tmp;

	tmp = ft_getenv(mini->env, str, 1);
	if (tmp != NULL)
	{
		if (update_node(tmp, str) != 0)
			return (1);
	}
	else if (tmp == NULL && has_equal_sign(str))
	{
		tmp = export_new(str, mini);
		if (tmp == NULL)
			return (1);
	}
	else if (tmp == NULL && !(has_equal_sign(str)))
	{
		tmp = export_new(str, mini);
		if (tmp == NULL)
			return (1);
		tmp->exp = 0;
	}
	return (0);
}

int	ft_export(t_command *com, t_minishell *mini)
{
	int		ret;
	int		tmp;
	size_t	i;

	i = 0;
	ret = 0;
	if (com->data[0] == NULL)
		ret = export_no_arg(com, mini);
	while (com->data[i])
	{
		if (!(check(com->data[i])) && !(check_value(com->data[i])))
		{
			if (has_plus_sign(com->data[i]))
				tmp = export_append(com->data[i], mini);
			else
				tmp = ft_export_env(com->data[i], mini);
			if (tmp == 1)
				ret = 1;
		}
		else
			ret = 1;
		i++;
	}
	return (ret);
}
