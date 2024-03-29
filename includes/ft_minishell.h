/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 19:34:16 by alexafer          #+#    #+#             */
/*   Updated: 2024/03/29 13:50:33 by lpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H

//Users/Alexandre/.brew/opt/readline/include
#include "../ft_printf/ft_printf.h"
#include "../libft/libft.h"
#include "get_next_line.h"
//#include "/usr/alexafer/.brew/opt/readline/lib"
//#include "/usr/alexafer/.brew/opt/readline/include"
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <limits.h>
#include <errno.h>
#include <string.h>

typedef	struct s_env
{
	char	*env_var;
	struct s_env	*next;
}	t_env;

typedef struct s_minishell
{
	char	*program_name;
	char	*prompt;
	char	*folder;
	char	*start_path;
	char	*path;
	char	*line;
	int		error;
	int		stop;
	t_env	*env;
}	t_minishell;

typedef struct s_wilds
{
	char	**split;
	int		j;
	int		i;
	int		first;
	int		last;
}	t_wilds;

typedef struct s_command
{
	char	command[100];
	char	*option;
	int		op;
	char	**data;
	char	*output_str;
	int		status;
}	t_command;

int	ft_env(t_env *env);
int	ft_export(t_command *com, t_minishell *mini);
int	update_node(t_env *node, char *str);
t_env	*ft_newnode(char *str);
t_env	*init_env_var(t_minishell *mini, char **env);
void	ft_clearlst(t_env *node);

int		ft_printf_error(void);
int		ft_get_path(t_minishell *shell);
void	ft_printf_path(t_minishell *shell);
char	*ft_get_folder(t_minishell shell);
char	*ft_make_prompt(t_minishell mini);
void	ft_parser(t_minishell *mini, char *input);
int		ft_wildscards(char *s1, char *s2);
void	ft_free_split(char **split);
int		ft_cd(t_command *command, t_minishell *mini);
int		ft_execute(char **split, t_minishell *mini);
void	ft_take_action(t_command *com, t_minishell *mini);
void	ft_error_msg(char *command);
void	ft_echo(t_command *command);
#endif
