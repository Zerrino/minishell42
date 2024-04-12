/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 22:46:12 by alexafer          #+#    #+#             */
/*   Updated: 2024/04/12 18:31:49 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

void	search_and_execute_command(t_pipeline_data *data)
{
	char	**directories;
	char	*path;
	char	*command_path;
	int		j;

	path = converter_nfree(data->mini, "$PATH");
	directories = ft_split(path, ':');
	j = 0;
	while (directories[j])
	{
		command_path = ft_strjoin(directories[j], "/");
		command_path = ft_strjoin_f(command_path, data->commands->command);
		execute_path_command(data, command_path);
		free(command_path);
		j++;
	}
	free(path);
	ft_free_split(directories);
}

void	execute_path_command(t_pipeline_data *data, char *command_path)
{
	char	**argv;
	char	**env;

	argv = ft_strstrjoin(command_path, data->commands->data);
	env = ft_converter_env(data->mini->env);
	execve(command_path, argv, env);
	ft_free_split(argv);
	ft_free_split(env);
}

void	execute_command(t_pipeline_data *data)
{
	int	i;

	handle_file_out_redirection(data);
	handle_file_in_redirection(data);
	if (!data->commands->found)
	{
		if (!ft_strchr(data->commands->command, '/'))
			search_and_execute_command(data);
		else
			execute_path_command(data, data->commands->command);
		ft_error_msg(data->commands->command);
		ft_clearlst(data->mini->env);
		ft_free_split(data->commands->data);
		exit(1);
	}
	ft_free_split(data->commands->data);
	i = ft_is_inside(data->commands->command);
	free(data->commands->command);
	exit(i);
}

void	handle_redirections(t_pipeline_data *data)
{
	if (data->i > 0)
	{
		if (!data->commands->file_in.file_name)
			dup2(data->in_fd, STDIN_FILENO);
		close(data->in_fd);
	}
	if (data->i < data->num_cmds - 1)
	{
		close(data->pipe_fd[0]);
		if (!data->commands->file_out.file_name)
			dup2(data->pipe_fd[1], STDOUT_FILENO);
		close(data->pipe_fd[1]);
	}
}

void	writing_file(t_pipeline_data *data)
{
	int	len;

	len = ft_strlen(data->commands->output_str);
	write(data->pipe_fd[1], data->commands->output_str, len);
}
