/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_right.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 17:47:23 by alexafer          #+#    #+#             */
/*   Updated: 2024/04/05 19:21:32 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

int	ft_empty_par(t_minishell *mini, char *input)
{
	int	i;

	i = 0;
	if (!input)
	{
		mini->stop = 1;
		exit (1);
	}
	while (input[i])
	{
		if (input[i] != 10 && input[i] != 32 && input[i] != 9)
			return (0);
		i++;
	}
	return (1);
}

int	ft_redir_right(char *folder_name, int doub)
{
	int		fd_nb;
	//char	*str;

	fd_nb = 1;
	if (!folder_name || !folder_name[0] || ft_strchr(folder_name, '>'))
		return (-1);
	if (doub == 1)
		fd_nb = open(folder_name, O_RDWR | O_APPEND);
	else if (doub == 0)
		fd_nb = open(folder_name, O_RDWR | O_TRUNC);
	if (fd_nb == -1)
	{
		fd_nb = open(folder_name, O_CREAT, 0644);
		if (fd_nb == -1)
		{
			free(folder_name);
			return (ft_printf_error());
		}
		close(fd_nb);
		fd_nb = open(folder_name, O_WRONLY);
	}
	return (fd_nb);
}

static char	*ft_red_u(char *folder_name)
{
	char	*str;
	char	*result;

	str = get_next_line(0);
	folder_name = ft_strjoin_f(folder_name, "\n");
	result = ft_calloc(1, sizeof(char));
	while (ft_strncmp(folder_name, str, ft_strlen(str)))
	{
		result = ft_strjoin_f(result, str);
		free(str);
		str = get_next_line(0);
	}
	free(str);
	result = ft_strjoin_f(result, "\0");
	free(folder_name);
	return (result);
}

static char	*ft_red_u_2(int fd_nb)
{
	char	*result;
	char	*str;

	str = get_next_line(fd_nb);
	result = ft_calloc(1, sizeof(char));
	while (str)
	{
		result = ft_strjoin_f(result, str);
		free(str);
		str = get_next_line(fd_nb);
	}
	free(str);
	result = ft_strjoin_f(result, "\0");
	close(fd_nb);
	return (result);
}

char	*ft_redir_left(char *folder_name, int doub)
{
	//char	*str;
	char	*result;
	int		fd_nb;
	//int		i;

	if (!folder_name || !folder_name[0] || ft_strchr(folder_name, '>'))
		return (0);
	if (doub == 1)
		result = ft_red_u(folder_name);
	else
	{
		fd_nb = open(folder_name, O_RDONLY);
		if (fd_nb == -1)
		{
			free(folder_name);
			ft_printf_error();
			return (0);
		}
		result = ft_red_u_2(fd_nb);
	}
	return (result);
}
