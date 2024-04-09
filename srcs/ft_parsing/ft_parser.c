/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:47:31 by alexafer          #+#    #+#             */
/*   Updated: 2024/04/08 21:33:25 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

int	ft_is_inside(char *command)
{
	if (!ft_strncmp("export", command, ft_strlen("export")))
		return (3);
	else if (!ft_strncmp("unset", command, ft_strlen("unset")))
		return (3);
	else if (!ft_strncmp("exit", command, ft_strlen("exit")))
		return (3);
	else if (!ft_strncmp("cd", command, ft_strlen("cd")))
		return (3);
	return (0);
}

void	ft_execute_pipeline(t_minishell *mini,t_command **commands, int num_cmds, char **splited)
{
	pid_t	pid;
	char	*path;
	char	*empty;
	char	**argv;
	char	**env;
	char	**mul;
	char	*str;
	int		ato;
	int		status;
	int		i;
	int		j;
	int		pipe_fd[2];
	int		in_fd;

	in_fd = 0;
	i = 0;
	while (i < num_cmds)
	{
		if (i < num_cmds -1)
		{
			if (pipe(pipe_fd) == -1)
			{
				printf("Error pipe\n");
				exit(1);
			}
		}
		pid = fork();
		if (pid == -1)
		{
			printf("Error fork\n");
			exit(1);
		}
		else if (pid == 0)
		{
			if (in_fd != 0)
			{
				dup2(in_fd, STDIN_FILENO);
				close(in_fd);
			}
			if (i < num_cmds - 1)
			{
				close(pipe_fd[0]);
				dup2(pipe_fd[1], STDOUT_FILENO);
				close(pipe_fd[1]);
			}
			ft_parser(mini, splited[i], commands[i], 0);
			if (mini->stop)
				return ;
			if (!commands[i]->found)
			{
				if (!ft_strchr(commands[i]->command, '/'))
				{
					path = converter_nfree(mini, "$PATH");
					mul = ft_split(path, ':');
					j = 0;
					while (mul[j])
					{
						empty = "";
						empty = ft_strjoin(empty, mul[j]);
						empty = ft_strjoin_f(empty, "/");
						empty = ft_strjoin_f(empty, commands[i]->command);
						argv = ft_strstrjoin(empty, commands[i]->data);
						env = ft_converter_env(mini->env);
						execve(empty, argv, env);
						free(empty);
						j++;
					}
				}
				else
				{
					empty = ft_strdup(commands[i]->command);
					argv = ft_strstrjoin(empty, commands[i]->data);
					env = ft_converter_env(mini->env);
					execve(empty, argv, env);
				}
				printf("Command not found : %s\n", commands[i]->command);
				exit (1);
			}
			else
				exit(ft_is_inside(commands[i]->command));
			exit(0);
		}
		else
		{
			waitpid(pid, &status, 0);
			commands[i]->status = status;
			mini->status_com = status;
			if (in_fd != 0)
				close(in_fd);
			if (i < num_cmds -1)
			{
				close(pipe_fd[1]);
				in_fd = pipe_fd[0];
			}
			str = ft_strjoin("$?", "");
			str = converter(mini, str);
			ato = ft_atoi(str);
			if (ato == 768)
			{
				ft_parser(mini, splited[i], commands[i], 1);
				mini->status_com = commands[i]->status;
			}
		}
	//printf("Fin de la boucle\n");
		i++;
	}
}

void	ft_all_parser(t_minishell *mini, char *input)
{
	t_command	*command;
	char	**splited;
	int		i;
	int		max;

	if (ft_empty_par(mini, input))
		return ;
	i  = 0;
	ft_replace_quote(input);
	splited = ft_split(input, '|');
	while (splited[i])
		i++;
	max = i;
	command = (t_command *)malloc(sizeof(t_command) * (i));
	if (!command)
		return ;
	ft_execute_pipeline(mini, &command, max, splited);
}
