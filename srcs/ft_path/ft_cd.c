/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 04:16:31 by alexafer          #+#    #+#             */
/*   Updated: 2024/04/02 18:56:56 by alexafer         ###   ########.fr       */
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


//typedef	struct s_env
//{
//	char	*env_var;
//	struct s_env	*next;
//}	t_env;

char	**ft_converter_env(t_env *env)
{
	t_env	*start;
	char	**result;
	int	i;

	start = env;
	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	result = (char **)malloc(sizeof(char) * (i + 1));
	if (!result)
		return (0);
	i = 0;
	env = start;
	while (env)
	{
		result[i] = env->env_var;
		i++;
		env = env->next;
	}
	result[i] = 0;
	return (result);
}

int	ft_execute(t_command *command, t_minishell *mini)
{
    pid_t	pid;
	int		status;
	char	**test;
	char	*path;
	char	*path2;
	char	**aargv;
	char	**eenvp;
	int		a;
	int		b;
	int		i;

	pid = fork();
	command->status = 0;
	if (pid == -1)
	{
		printf("Pid fail\n");
		return (0);
	}
	else if (pid == 0)
	{
		if (!ft_strchr(command->command, '/'))
		{
			printf("Enter here.\n");
			path = ft_strjoin("$PATH", "");
			path = converter(mini, path);
			eenvp = ft_converter_env(mini->env);
			test = ft_split(path, ':');
			i = 0;
			while (test[i])
			{
				test[i] = ft_strjoin(test[i], "/");
				test[i] = ft_strjoin(test[i], command->command);
				aargv = ft_strstrjoin(test[i], command->data);
				a = 0;
				execve(test[i], aargv, eenvp);
				i++;
			}
		}
		else
		{
			printf("Enter here now.\n");
			path = command->command;
			eenvp = ft_converter_env(mini->env);
			aargv = ft_strstrjoin(path, command->data);
			execve(path, aargv, eenvp);
		}
		return (0);
	}
	else
	{
		waitpid(pid, &status, 0);
		printf("celui du dessus a fini.\n");
	}
	return (0);
}
