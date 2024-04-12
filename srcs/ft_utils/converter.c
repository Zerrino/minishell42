/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 16:27:10 by lpetit            #+#    #+#             */
/*   Updated: 2024/04/11 12:58:38 by lpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

char	*ft_charjoin_f(char *s1, char c)
{
	size_t	s1_size;
	char	*join;

	if (!s1)
		return (NULL);
	s1_size = ft_strlen(s1);
	join = (char *)malloc(((s1_size + 1) + 1) * sizeof(char));
	if (!join)
	{
		free(s1);
		return (NULL);
	}
	ft_strlcpy(join, s1, s1_size + 1);
	join[s1_size] = c;
	join[s1_size + 1] = '\0';
	free(s1);
	return (join);
}

char	*get_env_value(char *str, t_env *env)
{
	t_env	*node;
	char	*tmp;
	size_t	i;

	i = 0;
	tmp = ft_strdup(str);
	if (!tmp)
		return (NULL);
	while (tmp[i] && isalnum(tmp[i]))
		i++;
	tmp[i] = '\0';
	node = ft_getenv(env, tmp, 1);
	free(tmp);
	if (!node)
		return (NULL);
	tmp = node->env_var;
	while (*tmp != '=')
		tmp++;
	tmp++;
	return (tmp);
}

char	*join_value(char *new, char *str, t_minishell *mini)
{
	char	*env_value;
	char	*tmp;

	if (!new)
		return (NULL);
	tmp = new;
	if (*str == '$')
		env_value = ft_itoa(mini->pid);
	else if (*str == '?')
		env_value = ft_itoa(mini->status_com);
	else if (isalnum(*str))
		env_value = ft_strdup(get_env_value(str, mini->env));
	else if (*str == '\0' || !(isalnum(*str)))
		env_value = ft_strdup("$");
	if (env_value != NULL)
	{
		new = ft_strjoin_f(new, env_value);
		free(env_value);
	}
	if (!new)
		free(tmp);
	return (new);
}

char	*converter(t_minishell *mini, char *str)
{
	char	*new;
	char	*tmp;

	tmp = str;
	new = ft_strdup("");
	while (*tmp)
	{
		if (*tmp && *tmp == '$')
		{
			tmp++;
			new = join_value(new, tmp, mini);
			if (*tmp != '$' && *tmp != '?')
				while (*tmp && isalnum(*tmp))
					tmp++;
			else
				tmp++;
		}
		else if (*tmp)
		{
			new = ft_charjoin_f(new, *tmp);
			tmp++;
		}
	}
	free(str);
	return (converter_tilde(mini, new));
}

char	*converter_nfree(t_minishell *mini, char *str)
{
	char	*new;
	char	*tmp;

	tmp = str;
	new = ft_strdup("");
	while (*tmp)
	{
		if (*tmp && *tmp == '$')
		{
			tmp++;
			new = join_value(new, tmp, mini);
			if (*tmp != '$' && *tmp != '?')
				while (*tmp && isalnum(*tmp))
					tmp++;
			else
				tmp++;
		}
		else if (*tmp)
		{
			new = ft_charjoin_f(new, *tmp);
			tmp++;
		}
	}
	return (converter_tilde(mini, new));
}
