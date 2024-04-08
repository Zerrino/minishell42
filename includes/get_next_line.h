/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:23:11 by alexafer          #+#    #+#             */
/*   Updated: 2024/03/16 19:01:18 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif

int		slen(char *str);
int		ft_s(char *str, char c, int n);
char	*ft_make_it_bigger(char *s1, char *s2);
char	*get_next_line(int fd);

#endif
