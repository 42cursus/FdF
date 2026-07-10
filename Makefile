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

NAME			:= fdf
CC				:= cc
INC_DIR			=  ./include
INCLUDE_FLAGS	:= -I. -I $(INC_DIR) -I/usr/include -I./lib/mlx -I./lib/ft/include
OPTIMIZE_FLAGS	:= -Og
DEBUG_FLAGS		:= -g3 -gdwarf-3

MANDATORY_FLAGS	:= -Wall -Wextra -Werror

CFLAGS			= $(MANDATORY_FLAGS) $(DEBUG_FLAGS) $(OPTIMIZE_FLAGS) $(INCLUDE_FLAGS)

TEST_MAPS		=  ./resources/test_maps
LIBFT_DIR		=  ./lib/ft
LIBFT			=  $(LIBFT_DIR)/libft.a
LIBX_DIR		=  ./lib/mlx
LIBX			=  $(LIBX_DIR)/libmlx.a
LIBS			:= $(LIBX) $(LIBFT)

LINK_FLAGS		:= -L $(LIBFT_DIR) -L $(LIBX_DIR) \
					-lmlx -lft -lX11 -lXext -lm

CTAGS			:= ctags
RM				:= /bin/rm

BUILD_DIR		= build
SRC_DIR			= src
OBJ_DIR			= $(BUILD_DIR)/obj

SRC_FS	 		:= cleanup.c \
					data_convert.c \
					draw_line_d.c \
					hooks.c \
					key_hooks.c \
 					load_data.c \
 					main.c \
					mouse_hooks.c \
 					on_expose.c \
					projection.c \
					rotate.c \
					view.c
SRCS	 		:= $(SRC_FS:%.c=$(SRC_DIR)/%.c)
OBJS			= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

.PHONY: all bonus clean fclean norm re test

all: $(NAME)

bonus: all

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
		@if [ ! -d $(@D) ]; then mkdir -p $(@D); fi
		$(CC) $(CFLAGS) $(INCLUDE_FLAGS) -o $@ -c $<

$(LIBFT):
		@$(MAKE) -C $(LIBFT_DIR) -j8

$(LIBX):
		@$(MAKE) -C $(LIBX_DIR)

$(NAME): $(LIBS) $(OBJS)
		$(CC) $(CFLAGS) $(INCLUDE_FLAGS) -o $@ $^  $(LINK_FLAGS)

test: fdf
		@printf '\033[36m%s\033[0m\n' 'this is a test'
#		@rm -rf $(TEST_MAPS)
#		@cd resources && unzip maps.zip
		./fdf $(TEST_MAPS)/elem-col.fdf || true
		./fdf $(TEST_MAPS)/elem2.fdf || true
		./fdf $(TEST_MAPS)/t1.fdf || true
		./fdf $(TEST_MAPS)/t2.fdf || true

## clean_libft
clean_libft:
		+$(MAKE) -C $(LIBFT_DIR) clean

## clean_libx
clean_libx: $(LIBX_DIR)/Makefile.gen
		+$(MAKE) -C $(LIBX_DIR) -f Makefile.gen clean
		+$(MAKE) -C $(LIBX_DIR)/test -f Makefile.gen clean

## fclean_libft
fclean_libft:
		+$(MAKE) -C $(LIBFT_DIR) fclean

## fclean_libx
fclean_libx: clean_libx
		@$(RM) -f $(LIBX_DIR)/Makefile.gen
		@$(RM) -f $(LIBX_DIR)/test/Makefile.gen

clean: clean_libft #clean_libx
		@if [ -d $(OBJ_DIR) ]; then $(RM) -fr $(OBJ_DIR); fi

fclean: clean fclean_libft
		@$(RM) -fr $(NAME) FdF $(BUILD_DIR) a.out

re: fclean
		+$(MAKE) all

norm:
		@norminette $(SRCS) --use-gitignore
		@$(MAKE) -C $(LIBFT_DIR) norm

# Magic help adapted: from https://gitlab.com/depressiveRobot/make-help/blob/master/help.mk (MIT License)
help:
	@printf "Available targets:\n\n"
	@awk -F: '/^[a-zA-Z\-_0-9%\\ ]+:/ { \
			helpMessage = match(lastLine, /^## (.*)/); \
			if (helpMessage) { \
					helpCommand = $$1; \
					helpMessage = substr(lastLine, RSTART + 3, RLENGTH); \
					printf "  \x1b[32;01m%-35s\x1b[0m %s\n", helpCommand, helpMessage; \
			} \
	} \
	{ lastLine = $$0 }' $(MAKEFILE_LIST) | sort -u
	@printf "\n"

.PHONY: all clean fclean re bonus norm help