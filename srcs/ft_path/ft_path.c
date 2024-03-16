/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 20:21:18 by alexafer          #+#    #+#             */
/*   Updated: 2024/03/16 21:29:10 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

int	ft_get_path(t_minishell *mini)
{
	char	cwd[PATH_MAX];
	char	*str;

	str = "";
	if (mini->path)
		free(mini->path);
	if (getcwd(cwd, sizeof(cwd)))
	{
		if (mini->path == 0)
			mini->start_path = ft_strjoin(cwd, str);
		mini->path = ft_strjoin(cwd, str);
		//free(str);
	}
	else
		return (ft_printf_error());
	mini->folder = ft_get_folder(*mini);
	return (0);
}

char	*ft_get_folder(t_minishell mini)
{
	char	*folder;
	int		i;
	int		j;

	i = 0;
	j = 0;
	folder = mini.path;
	while (*folder)
		if (*folder++ == 47)
			i++;
	folder = mini.path;
	while (*folder && i)
		if (*folder++ == 47)
			i--;
	return (folder);
}

void	ft_printf_path(t_minishell *mini)
{
	ft_printf("Started at directory: %s\n", mini->start_path);
	ft_printf("Current directory: %s\n", mini->path);
}
