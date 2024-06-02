# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abelov <abelov@student.42london.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/18 07:25:52 by abelov            #+#    #+#              #
#    Updated: 2024/05/18 07:25:52 by abelov           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abelov <abelov@student.42london.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/23 22:28:51 by abelov            #+#    #+#              #
#    Updated: 2023/10/23 22:34:31 by abelov           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:= fdf
CC				:= cc
INC_DIR			=  ./include
INCLUDE_FLAGS	:= -I. -I $(INC_DIR) -I/usr/include -I./lib/mlx
OPTIMIZE_FLAGS	:= -O0
DEBUG_FLAGS		:= -g3 -gdwarf-3
#MANDATORY_FLAGS	:= -Wall -Wextra -Werror
MANDATORY_FLAGS	:=
CFLAGS			= $(MANDATORY_FLAGS) $(DEBUG_FLAGS) $(OPTIMIZE_FLAGS) $(INCLUDE_FLAGS)

TEST_MAPS		=  ./resources/test_maps
LIBFT_PATH		=  ./lib/ft
LIBFT			=  $(LIBFT_PATH)/libft.a
LIBX_PATH		=  ./lib/mlx
LIBX			=  $(LIBX_PATH)/libmlx.a
LIBFDF_PATH		=  ./lib/fdf
LIBFDF			=  $(LIBFDF_PATH)/libfdf.a
LIBS			:= $(LIBX) $(LIBFT) $(LIBFDF)

LINK_FLAGS		:= -L $(LIBFT_PATH) -L $(LIBX_PATH)  -L $(LIBFDF_PATH) \
					-lfdf -lmlx -lft -lX11 -lXext -lm

CTAGS			:= ctags
RM				:= /bin/rm

BUILD_DIR		= build
SRC_DIR			= src
OBJ_DIR			= $(BUILD_DIR)/obj

SRC_FS	 		:= cleanup.c \
 					data_convert.c \
 					hooks.c \
 					load_data.c \
 					main.c \
 					on_expose.c \
 					rotate.c
SRCS	 		:= $(SRC_FS:%.c=$(SRC_DIR)/%.c)
OBJS			= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

.PHONY: all clean test re

all: $(NAME) test

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
		@mkdir -p $(@D)
		$(CC) $(CFLAGS) $(INCLUDE_FLAGS) -o $@ -c $<

$(LIBFT):
		@$(MAKE) -C $(LIBFT_PATH) -j8

$(LIBX):
		@$(MAKE) -C $(LIBX_PATH)

$(LIBFDF):
		@$(MAKE) -C $(LIBFDF_PATH) -j8

$(NAME): $(LIBS) $(OBJS)
		$(CC) $(CFLAGS) $(INCLUDE_FLAGS) -o $@ $^  $(LINK_FLAGS)

test: $(NAME)
		@printf '\033[36m%s\033[0m\n' 'this is a test'
#		@rm -rf $(TEST_MAPS)
#		@cd resources && unzip maps.zip
		./$(NAME) $(TEST_MAPS)/elem-col.fdf || true
		./$(NAME) $(TEST_MAPS)/elem2.fdf || true
		./$(NAME) $(TEST_MAPS)/t1.fdf || true
		./$(NAME) $(TEST_MAPS)/t2.fdf || true

clean:
		@$(RM) -fr $(OBJ_DIR)
		@$(MAKE) -C $(LIBFT_PATH) clean
		@$(MAKE) -C $(LIBX_PATH) clean
		@$(MAKE) -C $(LIBX_PATH) clean

fclean: clean
		@$(RM) -fr $(NAME) $(BUILD_DIR) a.out

re: fclean all

norm:
		@norminette $(SRCS)
		@$(MAKE) -C $(LIBFT_PATH) norm
		@$(MAKE) -C $(LIBFDF_PATH) norm


