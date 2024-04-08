/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 04:16:31 by alexafer          #+#    #+#             */
/*   Updated: 2024/04/08 15:49:30 by alexafer         ###   ########.fr       */
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
void	ft_pipe_exe(char *str)
{


}

int	ft_execute(t_command *command, t_minishell *mini)
{
    pid_t	pid;
	int		status;
	int		i;
	char	**splitted;
	int		pipefd_input[2];
	int		pipefd_output[2];
	char	**argv;
	char	**env;
	char	*path;
	char	*empty;


	if (command->next)
		printf("Next\n");
	else
		printf("No next\n");
	if (command->next)
	{
		if (pipe(pipefd_output) != 0)
		{
			printf("Pipe failed\n");
			exit(0);
		}
	}
	if (command->in)
	{
		if (pipe(pipefd_output) != 0)
		{
			printf("Pipe failed\n");
			exit(0);
		}
	}
	pid = fork();
	if (pid == -1)
	{
		printf("Pid failed\n");
		return (0);
	}
	else if (pid == 0)
	{
		if (command->in)
		{
			close(pipefd_input[1]);
			dup2(pipefd_input[0], STDIN_FILENO);
			close(pipefd_input[0]);
		}
		if (command->next)
		{
			close(pipefd_output[0]);
			dup2(pipefd_output[1], STDOUT_FILENO);
			close(pipefd_output[1]);
		}

		if (!ft_strchr(command->command, '/'))
		{
			path = converter_nfree(mini, "$PATH");
			splitted = ft_split(path, ':');
			i = 0;
			while (splitted[i])
			{
				empty = "";
				//printf("spllited[%d] : %s\n", i, splitted[i]);
				empty = ft_strjoin(empty, splitted[i]);
				empty = ft_strjoin_f(empty, "/");
				empty = ft_strjoin_f(empty, command->command);
				argv = ft_strstrjoin(empty, command->data);
				env = ft_converter_env(mini->env);
				//printf("empty : %s\n", empty);
				execve(empty, argv, env);
				//ft_free_split(argv);
				//ft_free_split(env);
				free(empty);
				i++;
			}
		}
		else
		{
			empty = ft_strdup(command->command);
			argv = ft_strstrjoin(empty, command->data);
			env = ft_converter_env(mini->env);
			execve(empty, argv, env);
		}
		mini->stop = 1;
	}
	else
	{
		char	*buffer_v;
		char	*tot;
		close(pipefd_input[0]);

		//printf("INPUT : %s\n", command->in);
		if (command->in)
		{
			//printf("INPUT2 : %s\n", command->in);
			write(pipefd_input[1], command->in, ft_strlen(command->in));
		}
		if (command->in)
			close(pipefd_input[1]);
		if (command->next)
		{

			//int nbytes = read(fd[0], buffer, sizeof(buffer));
			//write(STDOUT_FILENO, buffer, nbytes);
			buffer_v = "1";
			tot = ft_calloc(1, 1);
			//tot = buffer_v;
			while (buffer_v)
			{
				buffer_v = get_next_line(pipefd_output[0]);
				//printf("buff : %s", buffer_v);
				if (buffer_v)
					tot = ft_strjoin_f(tot, buffer_v);
				//tot = ft_strjoin(tot, buffer_v);
			}
			//printf("tot : %s", tot);
			command->output_str = tot;
			close(pipefd_output[0]);
		}
		//printf("celui du dessus a fini.\n");
		waitpid(pid, &status, 0);
		command->status = status;
	}
	return (0);
}
