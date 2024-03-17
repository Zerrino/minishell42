# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alexafer <alexafer@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/06 09:46:53 by zerrino           #+#    #+#              #
#    Updated: 2024/03/17 15:23:06 by alexafer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc

INCLUDES = #-lreadline
CFLAGS = $(INCLUDES) #-Wall -Wextra -Werror

SRC_DIR = srcs
GNL_DIR = get_next_line
PATH_DIR = ft_path
UTILS_DIR = ft_utils


OBJ_DIR = objs
GNL_OBJ_DIR = objs/get_next_line
PATH_OBJ_DIR = objs/ft_path
UTILS_OBJ_DIR = objs/ft_utils


INC_DIR = includes
LIBFT_DIR = libft
FT_PRINTF_DIR = ft_printf


GNL_FILES = get_next_line.c get_next_line_utils.c
GNL_FILES := $(addprefix $(GNL_DIR)/, $(GNL_FILES))

PATH_FILES = ft_path.c
PATH_FILES := $(addprefix $(PATH_DIR)/, $(PATH_FILES))

UTILS_FILES = ft_error_manage.c ft_prompt.c ft_wildscards.c
UTILS_FILES := $(addprefix $(UTILS_DIR)/, $(UTILS_FILES))


SRC_FILES = main.c $(GNL_FILES) $(UTILS_FILES) $(PATH_FILES)

SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))

SRCS := $(GNL) $(SRCS)

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

READ = /usr/local/opt/readline/include
REAB = /usr/local/opt/readline/lib

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(GNL_OBJ_DIR)
	@mkdir -p $(PATH_OBJ_DIR)
	@mkdir -p $(UTILS_OBJ_DIR)
	$(CC) $(CFLAGS) -I $(INC_DIR) -I $(READ) -c $< -o $@

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT_DIR)
	$(MAKE) -C $(FT_PRINTF_DIR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L$(LIBFT_DIR) -lft -L$(FT_PRINTF_DIR) -lftprintf -lreadline -L$(REAB)

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(FT_PRINTF_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(FT_PRINTF_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
