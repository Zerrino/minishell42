/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 00:10:09 by alexafer          #+#    #+#             */
/*   Updated: 2024/03/15 18:59:09 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>

typedef struct s_data
{
	char			conv;
	int				len_conv;
	int				len_wr;
	int				flag_space;
	int				flag_plus;
	int				flag_hastag;
	int				flag_minus;
	int				flag_zero;
	int				flag_dot;
	int				flag_minus_len;
	int				flag_zero_len;
	int				flag_dot_len;
	int				len;
	int				arg_int;
	unsigned int	arg_uint;
	char			*arg_str;
	char			arg_char;
	void			*arg_void;
}	t_data;

int		ft_printf(const char *fmt, ...);
void	ft_lentilarg(const char *fmt, t_data *data);
int		ft_first_digit(int nb);
int		ft_last_digit(int nb);
int		ft_return_last(const char *fmt);
void	ft_parse(va_list ap, const char *fmt, t_data *data);
void	ft_fill_minus(int len, t_data *data);
void	ft_fill_zero(t_data *data);
void	ft_putadd(void *add, t_data *data, int w);
void	ft_putstring(char *str, t_data *data, int w);
void	ft_putchart(char c, t_data *data, int w);
void	ft_fill_correct(t_data *data);
void	ft_fillx(t_data *data);
void	ft_fill_sign(t_data *data);
void	ft_fill_tot(int tot, t_data *data, int w);
void	ft_fill_dot_int(t_data *data);
int		ft_arguments(va_list ap, const char *fmt, t_data *data);
int		ft_count_digit(unsigned long nb);
void	ft_putuint(unsigned int nb, t_data *data, int w);
void	ft_puthexa_u(unsigned int nb, t_data *data, int w);
void	ft_puthexa_l(unsigned int nb, t_data *data, int w);
int		ft_putdigit(int nb, t_data *data, int w);
int		ft_is_digit(t_data *data);
int		ft_char_in_arg(char c);
void	ft_reset_flags(t_data *data);
int		ft_write(char *str, t_data *data, int w, int max);
int		ft_atoi_f(const char *str);
void	ft_actual_print(va_list ap, t_data *data, int w);

#endif
