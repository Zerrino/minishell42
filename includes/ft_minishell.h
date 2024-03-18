/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 19:34:16 by alexafer          #+#    #+#             */
/*   Updated: 2024/03/18 03:21:27 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H

//Users/Alexandre/.brew/opt/readline/include
#include "../ft_printf/ft_printf.h"
#include "../libft/libft.h"
#include "get_next_line.h"
//#include "/Users/Alexandre/.brew/opt/readline/lib"
//#include "/Users/Alexandre/.brew/opt/readline/include"
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <limits.h>
#include <errno.h>
#include <string.h>

typedef struct s_minishell
{
	char	*prompt;
	char	*folder;
	char	*start_path;
	char	*path;
	char	*line;
	int		error;
}	t_minishell;

typedef struct s_wilds
{
	char	**split;
	int		j;
	int		i;
	int		first;
	int		last;
}	t_wilds;

int		ft_printf_error(void);
int		ft_get_path(t_minishell *shell);
void	ft_printf_path(t_minishell *shell);
char	*ft_get_folder(t_minishell shell);
char	*ft_make_prompt(t_minishell mini);
int		ft_wildscards(char *s1, char *s2);
void	ft_free_split(char **split);
#endif
