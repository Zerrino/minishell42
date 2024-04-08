/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_manage.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 20:27:20 by alexafer          #+#    #+#             */
/*   Updated: 2024/04/02 17:33:29 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_minishell.h"

int	ft_printf_error(void)
{
	ft_putstr_fd("Error : ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

int	ft_error_msg(char *command)
{
	ft_putstr_fd("minishell: command not found: ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}
