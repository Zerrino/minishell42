# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alexafer <alexafer@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/06 09:46:53 by zerrino           #+#    #+#              #
#    Updated: 2024/04/05 18:00:26 by alexafer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc

INCLUDES = #-lreadline
CFLAGS = #-g -fsanitize=address -Wall -Wextra -Werror

SRC_DIR = srcs
GNL_DIR = get_next_line
PATH_DIR = ft_path
UTILS_DIR = ft_utils
MEM_DIR = ft_memory
PARS_DIR = ft_parsing
COM_DIR = ft_command

OBJ_DIR = objs
GNL_OBJ_DIR = objs/get_next_line
PATH_OBJ_DIR = objs/ft_path
UTILS_OBJ_DIR = objs/ft_utils
MEM_OBJ_DIR = objs/ft_memory
PARS_OBJ_DIR = objs/ft_parsing
COM_OBJ_DIR = objs/ft_command

INC_DIR = includes
LIBFT_DIR = libft
FT_PRINTF_DIR = ft_printf

MEM_FILES = ft_free.c
MEM_FILES := $(addprefix $(MEM_DIR)/, $(MEM_FILES))

COM_FILES = ft_echo.c ft_env.c ft_export.c ft_unset.c test_converter.c ft_exit.c
COM_FILES := $(addprefix $(COM_DIR)/, $(COM_FILES))

GNL_FILES = get_next_line.c get_next_line_utils.c
GNL_FILES := $(addprefix $(GNL_DIR)/, $(GNL_FILES))

PATH_FILES = ft_path.c ft_cd.c
PATH_FILES := $(addprefix $(PATH_DIR)/, $(PATH_FILES))

UTILS_FILES = ft_error_manage.c ft_prompt.c ft_wildscards.c ft_init_env.c converter.c converter_tilde.c ft_split_new.c ft_change.c
UTILS_FILES := $(addprefix $(UTILS_DIR)/, $(UTILS_FILES))

PARS_FILES = ft_parser.c ft_action.c ft_get_arr_com.c ft_get_arr_red.c ft_put_dir.c ft_rem_quo.c ft_replace.c ft_right.c ft_small_pars.c ft_utils.c ft_parser_utils.c ft_parser_utils_2.c ft_parser_i.c
PARS_FILES := $(addprefix $(PARS_DIR)/, $(PARS_FILES))

SRC_FILES = main.c $(GNL_FILES) $(UTILS_FILES) $(PATH_FILES) $(MEM_FILES) $(PARS_FILES) $(COM_FILES)

SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))

SRCS := $(GNL) $(SRCS)

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

READ = #/Users/alexafer/.brew/opt/readline/include
REAB = #/Users/alexafer/.brew/opt/readline/lib

READ = /usr/local/opt/readline/include
REAB = /usr/local/opt/readline/lib

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(GNL_OBJ_DIR)
	@mkdir -p $(PATH_OBJ_DIR)
	@mkdir -p $(UTILS_OBJ_DIR)
	@mkdir -p $(MEM_OBJ_DIR)
	@mkdir -p $(PARS_OBJ_DIR)
	@mkdir -p $(COM_OBJ_DIR)
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
