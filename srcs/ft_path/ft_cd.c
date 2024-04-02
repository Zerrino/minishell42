/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 04:16:31 by alexafer          #+#    #+#             */
/*   Updated: 2024/04/02 18:11:54 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

int	ft_cd(t_command *command, t_minishell *mini)
{
	if (!command->data || !command->data[0])
	{
		//cd home;
		command->status = 0;
		return (0);
	}
	if (chdir(command->data[0]) == -1)
	{
		command->status = 1;
		return (ft_printf_error());
	}
	mini->error = ft_get_path(mini);
	command->status = 0;
	return (mini->error);
}

char	**ft_strstrjoin(char *s1, char **s2)
{
	char	**result;
	int	i;
	int	j;
	int	m;

	while (s2[i])
		i++;
	result = (char **)malloc(sizeof(char) * (i + 2));
	if (!result)
		return (0);
	result[0] = s1;
	j = 1;
	m = 0;
	while (m < i)
	{
		result[j] = s2[m];
		m++;
		j++;
	}
	result[j] = 0;
	return (result);
}

int	ft_execute(t_command *command, t_minishell *mini)
{
	char	**test;
	char	*path;
	char	*path2;
	char	**argv;
	int		a;
	int		b;
	int		i;

	path = ft_strjoin("$PATH", "");
	path = converter(mini, path);
	//path = ft_strjoin_f(path, "/ls");
	//path = ft_strjoin_f(path, command->command);
	test = ft_split(path, ':');
	i = 0;
	while (test[i])
	{
		test[i] = ft_strjoin_f(test[i], "/");
		test[i] = ft_strjoin_f(test[i], command->command);
		argv = ft_strstrjoin(test[i], command->data);
		char *envp[] = {NULL};
		execve(test[i], argv, envp);
		i++;
	}
	printf("path : %s\n", path);
	//path = ft_strjoin(mini->start_path, "/");
	//path2 = ft_strjoin(path, &mini->program_name[2]);
	//printf("path2 : %s\n", path2);
	//free(path);
	a = 0;
	//int	m = fork();
	//printf("%d\n", m);
	//b = execve("/Users/Alexandre/Desktop/minishell/minishell42/minishell", NULL, NULL);
	//a = execve(split[0], NULL, NULL);
	//b = execve(path2, &mini->program_name, NULL);
	//free(path2);
	if (a == -1 || b == -1)
		return (ft_printf_error());
	return (0);
}
