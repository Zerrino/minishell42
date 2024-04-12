/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpetit <lpetit@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 18:21:47 by lpetit            #+#    #+#             */
/*   Updated: 2024/04/11 14:17:06 by lpetit           ###   ########.fr       */
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
	char	*err_msg;

	i = 0;
	err_msg = "': not a valid identifier\n";
	while (str[i])
	{
		if ((!(ft_isalnum(str[i])) && str[i] != '_' && str[i] != '=')
			|| !(ft_isalpha(str[0])))
		{
			write(2, "export: `", 9);
			write(2, str, ft_strlen(str));
			write(2, err_msg, ft_strlen(err_msg));
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_export_env(char *str, t_minishell *mini)
{
	t_env	*tmp;

	tmp = ft_getenv(mini->env, str, 0);
	if (tmp != NULL)
	{
		if (update_node(tmp, str) != 0)
			return (1);
	}
	else if (tmp == NULL && has_equal_sign(str))
	{
		tmp = mini->env;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = ft_newnode(str);
		if (tmp->next == NULL)
			return (1);
		else if (tmp->next->env_var == NULL)
		{
			free(tmp->next);
			tmp->next = NULL;
			return (1);
		}
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
	while (com->data[i])
	{
		if (!(check(com->data[i])))
		{
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
