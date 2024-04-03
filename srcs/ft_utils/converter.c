/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 16:27:10 by lpetit            #+#    #+#             */
/*   Updated: 2024/04/03 03:18:39 by alexafer         ###   ########.fr       */
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
		return (NULL);
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
	if (!node)
		return (NULL);
	free(tmp);
	tmp = node->env_var;
	while (*tmp != '=')
		tmp++;
	tmp++;
	return (tmp);
}

char	*converter(t_minishell *mini, char *str)
{
	char	*new;
	char	*env_value;
	char	*tmp;

	tmp = str;
	new = ft_strdup("");
	while (*tmp)
	{
		if (*tmp && *tmp == '$')
		{
			tmp++;
			env_value = get_env_value(tmp, mini->env);
			if (env_value != NULL)
				new = ft_strjoin_f(new, env_value);
			while (*tmp && isalnum(*tmp))
				tmp++;
		}
		else if (*tmp)
		{
			new = ft_charjoin_f(new, *tmp);
			tmp++;
		}
	}
	free(str);
	return (new);
}

char	*converter_nfree(t_minishell *mini, char *str)
{
	char	*new;
	char	*env_value;
	char	*tmp;

	tmp = str;
	new = ft_strdup("");
	while (*tmp)
	{
		if (*tmp && *tmp == '$')
		{
			tmp++;
			env_value = get_env_value(tmp, mini->env);
			if (env_value != NULL)
				new = ft_strjoin_f(new, env_value);
			while (*tmp && isalnum(*tmp))
				tmp++;
		}
		else if (*tmp)
		{
			new = ft_charjoin_f(new, *tmp);
			tmp++;
		}
	}
	return (new);
}
