/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpetit <lpetit@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 13:23:26 by lpetit            #+#    #+#             */
/*   Updated: 2024/04/21 16:14:44 by lpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/ft_minishell.h"

char	*ft_strjoin_free(char *s1, char const *s2)
{
	size_t	s1_size;
	size_t	s2_size;
	char	*join;

	if (!s1 || !s2)
	{
		if (s1 != NULL && s2 == NULL)
			free(s1);
		return (NULL);
	}
	s1_size = ft_strlen(s1);
	s2_size = ft_strlen(s2);
	join = malloc((s1_size + s2_size + 1) * sizeof(char));
	if (!join)
	{
		free(s1);
		return (NULL);
	}
	ft_strlcpy(join, s1, s1_size + 1);
	ft_strlcpy((join + s1_size), s2, s2_size + 1);
	free(s1);
	return (join);
}

t_env	*export_new(char *str, t_minishell *mini)
{
	t_env	*tmp;

	if (!str)
		return (NULL);
	tmp = mini->env;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = ft_newnode(str);
	if (tmp->next == NULL)
		return (NULL);
	else if (tmp->next->env_var == NULL)
	{
		free(tmp->next);
		tmp->next = NULL;
		return (NULL);
	}
	return (tmp->next);
}

char	*add_quotes(char *str)
{
	char	**split;
	char	*tmp;
	size_t	i;

	i = 0;
	tmp = ft_strdup(str);
	if (!tmp)
		return (NULL);
	while (tmp[i] != '=')
		i++;
	tmp[i] = '(';
	split = ft_split(tmp, '(');
	free(tmp);
	tmp = ft_strjoin("declare -x ", split[0]);
	tmp = ft_strjoin_free(tmp, "=\"");
	tmp = ft_strjoin_free(tmp, split[1]);
	tmp = ft_strjoin_free(tmp, "\"\n");
	if (split != NULL)
		ft_free_split(split);
	return (tmp);
}

char	*no_quotes(char *str)
{
	char	*tmp;

	tmp = ft_strjoin("declare -x ", str);
	tmp = ft_strjoin_free(tmp, "\n");
	return (tmp);
}

int	export_no_arg(t_command *com, t_minishell *mini)
{
	t_env	*lst;
	char	*tmp;
	char	*str;

	lst = mini->env;
	str = ft_strdup("");
	if (!str)
		return (1);
	while (lst != NULL)
	{
		if (has_equal_sign(lst->env_var))
			tmp = add_quotes(lst->env_var); 
		else
			tmp = no_quotes(lst->env_var);
		str = ft_strjoin_free(str, tmp);
		if (tmp != NULL)
			free(tmp);
		lst = lst->next;
	}
	if (!str)
		return (1);
	com->output_str = str;
	return (0);
}
