/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 04:16:31 by alexafer          #+#    #+#             */
/*   Updated: 2024/03/20 05:29:40 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

int	ft_cd(char **split, t_minishell *mini)
{
	if (!split || !split[1])
		return (1);
	if (chdir(split[1]) == -1)
		return (ft_printf_error());
	mini->error = ft_get_path(mini);
	return (mini->error);
}

int	ft_execute(char **split, t_minishell *mini)
{
	char	**test;
	char	*path;
	char	*path2;
	int		a;
	int		b;

	//path = ft_strjoin(mini->start_path, "/");
	//path2 = ft_strjoin(path, &mini->program_name[2]);
	//printf("path2 : %s\n", path2);
	//free(path);
	a = 0;
	int	m = fork();
	//printf("%d\n", m);
	//b = execve("/Users/Alexandre/Desktop/minishell/minishell42/minishell", NULL, NULL);
	//a = execve(split[0], NULL, NULL);
	//b = execve(path2, &mini->program_name, NULL);
	//free(path2);
	if (a == -1 || b == -1)
		return (ft_printf_error());
	return (0);
}
