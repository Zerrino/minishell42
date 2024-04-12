/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 22:42:10 by alexafer          #+#    #+#             */
/*   Updated: 2024/04/12 20:36:35 by alexafer         ###   ########.fr       */
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

void	parent_process(t_pipeline_data *data)
{
	char	*str;
	int		status;
	int		ato;

	waitpid(data->pid, &status, 0);
	data->mini->status_com = status;
	if (data->in_fd != 0)
		close(data->in_fd);
	if (data->i < data->num_cmds - 1)
	{
		close(data->pipe_fd[1]);
		data->in_fd = data->pipe_fd[0];
	}
	str = ft_strjoin("$?", "");
	str = converter(data->mini, str);
	ato = ft_atoi(str);
	free(str);
	if (ato == 768)
	{
		str = ft_strdup(data->splited[data->i]);
		ft_parser(data->mini, str, data->commands, 1);
		data->mini->status_com = data->commands->status;
		free(data->commands->command);
		ft_free_split(data->commands->data);
	}
}

void	handle_file_out_redirection(t_pipeline_data *data)
{
	char	*f;
	//int		len;

	f = data->commands->file_out.file_name;
	if (data->commands->file_out.file_name)
	{
		if (data->commands->file_out.doub)
			data->pipe_fd[1] = open(f, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			data->pipe_fd[1] = open(f, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (data->pipe_fd[1] < 0)
		{
			perror("Open file redirection out");
			exit(1);
		}
		if (data->commands->output_str && !data->commands->file_out.doub)
			writing_file(data);
		if (dup2(data->pipe_fd[1], STDOUT_FILENO) < 0)
		{
			perror("Dup2 file redirection out");
			close(data->pipe_fd[1]);
			exit(1);
		}
		close(data->pipe_fd[1]);
	}
}

static void	write_data_redirection(t_pipeline_data *data, int id_file_in)
{
	int	len;

	len = ft_strlen(data->commands->in);
	write(id_file_in, data->commands->in, len);
	close(id_file_in);
}

void	handle_file_in_redirection(t_pipeline_data *data)
{
	int		id_file_in;
	//int		len;
	char	*filename;

	filename = data->commands->file_in.file_name;
	if (filename)
	{
		if (data->commands->file_in.doub)
		{
			filename = "./srcs/fichier.txt";
			id_file_in = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
			if (id_file_in >= 0)
				write_data_redirection(data, id_file_in);
		}
		id_file_in = open(filename, O_RDONLY);
		if (id_file_in < 0 || dup2(id_file_in, STDIN_FILENO) < 0)
		{
			perror("Handling file redirection in");
			close(id_file_in);
			exit(1);
		}
		close(id_file_in);
	}
}
