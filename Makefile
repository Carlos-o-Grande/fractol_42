# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/06 12:12:04 by cjoao-de          #+#    #+#              #
#    Updated: 2024/04/12 16:17:59 by cjoao-de         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Pretty colors
include include/pretty_colors_ANSI

# Project files
SOURCE	= 	fractol.c	hooks.c			render_shader.c		render_select.c \
			aux.c		mlx_aux.c		help.c				render_menu.c \
			mandelbrot.c	mandelbox.c		julia.c	shaders.c
SRC		= $(addprefix source/,$(SOURCE))
SRC_DIR = ./source/

OBJ_DIR = ./object/
OBJ		= $(patsubst source/%.c,$(OBJ_DIR)%.o,$(SRC))

INC_DIR = -I ./include/
LIBFT_DIR = libs/libft/
MLX_DIR = libs/minilibx-linux/
LIBFT = $(LIBFT_DIR)libft.a
MLX = $(MLX_DIR)libmlx.a

# Project settings
#
NAME = fractol
LFLAGS = -lmlx -L$(LIBFT_DIR) -L$(MLX_DIR) -lXext -lX11 -lm -lft
CFLAGS = -Wall -Wextra -Werror -I${LIBFT_DIR} -I${MLX_DIR} -Ofast #-pg
debug: CFLAGS += -g3 -O0 #-fsanitize=address #-pg #-fPIE
MAKEFLAGS += --no-print-directory # --silent
.SILENT: $(OBJ) $(NAME) clean fclean $(MLX)
ARFLAGS = rvs
RM = rm -rf
CC = cc
# AR = ar

all: $(NAME)

libft: $(LIBFT)

mlx: $(MLX)

$(NAME): $(MLX) $(LIBFT) $(OBJ)
	@printf "$(YELLOW)** compiling **		"$(NAME)"$(RST)\n"
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LFLAGS)
	@printf "$(GREEN_B)$(NAME) created\n$(RST)"

$(OBJ):
	@mkdir -p $(OBJ_DIR)
	@printf "$(CYAN_I)** compiling **		"$@"$(RST)\n"
	$(CC) $(CFLAGS) $(INC_DIR) -c $(SRC_DIR)$(*F).c -o $@

debug: clean $(LIBFT) $(OBJ)
	@printf "$(YELLOW)"
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LFLAGS)
	@printf "$(RST)$(GREEN_B)[Debug version created]\n$(RST)"

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(MLX):
	@printf "$(CYAN_I)** compiling **		MLX$(RST)\n"
	@printf "$(YELLOW)"
	@make -C $(MLX_DIR) > /dev/null 2>&1
	@printf "$(RST)"
	@printf "$(GREEN_B)MLX created\n$(RST)"

clean:
	$(RM) $(OBJ_DIR)
	make clean -C $(LIBFT_DIR)
	@printf "$(RED)[All minilibx objects deleted]    $(RST)\n"
	# make clean -C $(MLX_DIR) > /dev/nullmake fclean
	@printf "$(RED)[All $(NAME) objects deleted]    $(RST)\n"

fclean: clean
	$(RM) $(NAME)
	$(RM) $(LIBFT)
	# $(RM) $(MLX)
	@printf "$(RED)[All binaries deleted]    $(RST)\n"

re: fclean all
