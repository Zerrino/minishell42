/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 20:21:18 by alexafer          #+#    #+#             */
/*   Updated: 2024/03/16 23:44:04 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

int	ft_get_path(volatile t_minishell *shell)
{
	char	cwd[PATH_MAX];
	char	*str;

	str = "";
	if (shell->path)
		free(shell->path);
	if (getcwd(cwd, sizeof(cwd)))
	{
		if (shell->path == 0)
			shell->start_path = ft_strjoin(cwd, str);
		shell->path = ft_strjoin(cwd, str);
		//free(str);
	}
	else
		return (ft_printf_error());
	shell->folder = ft_get_folder(*shell);
	return (0);
}

char	*ft_get_folder(volatile t_minishell shell)
{
	char	*folder;
	int		i;
	int		j;

	i = 0;
	j = 0;
	folder = shell.path;
	while (*folder)
		if (*folder++ == 47)
			i++;
	folder = shell.path;
	while (*folder && i)
		if (*folder++ == 47)
			i--;
	return (folder);
}

void	ft_printf_path(volatile t_minishell *shell)
{
	ft_printf("Started at directory: %s\n", shell->start_path);
	ft_printf("Current directory: %s\n", shell->path);
}
