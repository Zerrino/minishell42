/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 04:16:31 by alexafer          #+#    #+#             */
/*   Updated: 2024/04/04 02:55:37 by alexafer         ###   ########.fr       */
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
	int		len;
	int		i;

	len = 0;
	while (s2[len])
		len++;
	result = (char **)malloc(sizeof(char *) * (len + 2));
	if (!result)
		return (0);
	result[0] = ft_strdup(s1);
	i = 1;
	while ((i - 1) < len)
	{
		result[i] = ft_strdup(s2[i - 1]);
		i++;
	}
	result[len + 2] = 0;
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
	while (start)
	{
		i++;
		start = start->next;
	}
	start = env;
	result = (char **)malloc(sizeof(char *) * (i + 1));
	if (!result)
		return (0);
	i = 0;
	while (start)
	{
		result[i] = ft_strdup(start->env_var);
		i++;
		start = start->next;
	}
	result[i] = 0;
	return (result);
}

int	ft_execute(t_command *command, t_minishell *mini)
{
    pid_t	pid;
	int		status;
	int		i;
	char	**splitted;
	char	**argv;
	char	**env;
	char	*path;
	char	*empty;

	pid = fork();
	if (pid == -1)
	{
		printf("Pid failed\n");
		return (0);
	}
	else if (pid == 0)
	{
		if (!ft_strchr(command->command, '/'))
		{
			printf("execute command.\n");
			path = converter_nfree(mini, "$PATH");
			splitted = ft_split(path, ':');
			i = 0;
			while (splitted[i])
			{
				empty = "";
				printf("spllited[%d] : %s\n", i, splitted[i]);
				empty = ft_strjoin(empty, splitted[i]);
				empty = ft_strjoin_f(empty, "/");
				empty = ft_strjoin_f(empty, command->command);
				argv = ft_strstrjoin(empty, command->data);
				env = ft_converter_env(mini->env);
				printf("empty : %s\n", empty);
				execve(empty, argv, env);
				//ft_free_split(argv);
				//ft_free_split(env);
				free(empty);
				i++;
			}
		}
		else
		{
			printf("execute ./ \n");
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		command->status = status;
		printf("celui du dessus a fini.\n");
	}
	return (0);
}
