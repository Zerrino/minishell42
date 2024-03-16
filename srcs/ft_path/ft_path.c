/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 20:21:18 by alexafer          #+#    #+#             */
/*   Updated: 2024/03/16 21:06:36 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

int	ft_get_path(t_minishell *mini)
{
	char	cwd[PATH_MAX];

	if (mini->path)
		free(mini->path);
	if (getcwd(cwd, sizeof(cwd)))
	{
		if (mini->path == 0)
			mini->start_path = ft_strjoin(cwd, "");
		mini->path = ft_strjoin(cwd, "");
	}
	else
		return (ft_printf_error());
	return (0);
}

void	ft_printf_path(t_minishell *mini)
{
	ft_printf("Started at directory: %s\n", mini->start_path);
	ft_printf("Current directory: %s\n", mini->path);
}
