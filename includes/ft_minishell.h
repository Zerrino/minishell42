/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 19:34:16 by alexafer          #+#    #+#             */
/*   Updated: 2024/03/16 21:06:43 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H

#include "../ft_printf/ft_printf.h"
#include "../libft/libft.h"
#include "get_next_line.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <limits.h>
#include <errno.h>
#include <string.h>

typedef struct s_minishell
{
	char	*start_path;
	char	*path;
	int		error;
}	t_minishell;

int		ft_printf_error(void);
int		ft_get_path(t_minishell *mini);
void	ft_printf_path(t_minishell *mini);

#endif
