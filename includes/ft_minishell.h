/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 19:34:16 by alexafer          #+#    #+#             */
/*   Updated: 2024/04/08 21:00:53 by alexafer         ###   ########.fr       */
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
#include <sys/wait.h>
#include <signal.h>
#include <limits.h>
#include <errno.h>
#include <fcntl.h>
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
	int		status_com;
	int		pid;
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
	char	*command;
	char	*option;
	int		op;
	char	*in;
	char	**data;
	char	*output_str;
	int		status;
	int		next;
	int		found;
}	t_command;


char	**ft_strstrjoin(char *s1, char **s2);
char	**ft_converter_env(t_env *env);
int	ft_env(t_env *env);
int	ft_export(t_command *com, t_minishell *mini);
int	ft_unset(t_command *com, t_minishell *mini);
int	update_node(t_env *node, char *str);
char	*converter(t_minishell *mini, char *str);
char	*converter_tilde(t_minishell *mini, char *str);
t_env	*ft_newnode(char *str);
t_env	*ft_getenv(t_env *env, char *str, int c);
t_env	*init_env_var(t_minishell *mini, char **env);
void	ft_clearlst(t_env *node);
void	test_converter(t_minishell *mini, t_command *com);

void	ft_replace_quote(char *str);
void	ft_reverse_quote(char *str);
int		ft_exit(t_minishell *mini, t_command *com);
int		ft_printf_error(void);
int		*ft_get_arr_com(t_minishell *mini, t_command *command, char *input);
int		*ft_get_arr_red(t_minishell *mini, t_command *command, char *input);
int		ft_output_com(t_minishell *mini, char *input);
char	*ft_input_dir(t_minishell *mini, char *input);
char	*ft_rem_quote(char *str, int f);
int		ft_empty_par(t_minishell *mini, char *input);
int		ft_redir_right(char *folder_name, int doub);
char	*ft_redir_left(char *folder_name, int doub);
int		ft_in_arr(int nb, int *array);
char	**ft_get_data(char **split, t_command *command, int l, int *array_max[2]);
int		ft_get_path(t_minishell *shell);
void	ft_printf_path(t_minishell *shell);
char	*ft_get_folder(t_minishell shell);
char	*ft_make_prompt(t_minishell mini);
void	ft_parser(t_minishell *mini, char *input, t_command	*command);
void	ft_all_parser(t_minishell *mini, char *input);
int		ft_wildscards(char *s1, char *s2);
void	ft_free_split(char **split);
int		ft_cd(t_command *command, t_minishell *mini);
void	ft_take_action(t_command *com, t_minishell *mini);
int		ft_error_msg(char *command);
void	ft_echo(t_command *command);
int		ft_execute(t_command *command, t_minishell *mini);
char	*converter_nfree(t_minishell *mini, char *str);

#endif
