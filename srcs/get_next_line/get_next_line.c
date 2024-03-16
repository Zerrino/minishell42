/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 12:30:18 by alexafer          #+#    #+#             */
/*   Updated: 2024/03/16 19:38:44 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

char	*ft_read_static(int fd, char *str)
{
	char	*buffer;
	int		r_len;

	r_len = 42;
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
	{
		free(str);
		return (0);
	}
	while (r_len != 0 && (!ft_s(str, '\n', 1)))
	{
		r_len = read(fd, buffer, BUFFER_SIZE);
		if (r_len < 0)
		{
			free(str);
			free(buffer);
			return (0);
		}
		buffer[r_len] = '\0';
		str = ft_make_it_bigger(str, buffer);
	}
	free(buffer);
	return (str);
}

char	*ft_line(char *str)
{
	int		i;
	char	*result;

	if (!str[0])
		return (0);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	result = (char *)malloc(sizeof(char) * (i + (str[i] == '\n') + 1));
	if (!result)
		return (0);
	i = 0;
	while (str[i])
	{
		result[i] = str[i];
		if (result[i++] == '\n')
			break ;
	}
	result[i] = '\0';
	return (result);
}

char	*ft_str_update(char *str, char *result_atm)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i] || !result_atm)
	{
		free(str);
		return (0);
	}
	result = (char *)malloc(sizeof(char) * (slen(&str[i]) + 1));
	if (!result)
	{
		free(str);
		return (0);
	}
	j = 0;
	i++;
	while (str[i])
		result[j++] = str[i++];
	result[j] = '\0';
	free(str);
	return (result);
}

char	*get_next_line(int fd)
{
	static char	*str[100000];
	char		*result;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd >= 100000)
		return (0);
	str[fd] = ft_read_static(fd, str[fd]);
	if (!str[fd])
		return (0);
	result = ft_line(str[fd]);
	str[fd] = ft_str_update(str[fd], result);
	return (result);
}
