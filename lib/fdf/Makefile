# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abelov <abelov@student.42london.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/19 05:48:00 by abelov            #+#    #+#              #
#    Updated: 2024/05/19 05:48:00 by abelov           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:= libfdf.a
TOPDIR			= $(PWD)
CC				:= cc
CFLAGS			:= -Wall -Wextra -Werror -Wimplicit -Wno-error=parentheses -Wno-error=unused-parameter
INCLUDE_FLAGS	:= -I. -I../mlx -I../ft/include -I../../include -I./include -I/usr/include
# GCC 8 implements -fmacro-prefix-map.
#	Like -fdebug-prefix-map, it replaces a string prefix for the FILE macro.
#	-ffile-prefix-map is the union of -fdebug-prefix-map and -fmacro-prefix-map
DEBUG_FLAGS		:= -g3 -gdwarf-3 -ffile-prefix-map=$(TOPDIR)=./staging/

CTAGS			:= ctags
LIB_COMMAND		:= ar rcs
RM				:= /bin/rm

SRCS	 		:=
DIRS			:= utils draw

include $(addsuffix /Makefile.mk,$(DIRS))

BUILD_DIR		= build
OBJS			= $(SRCS:%.c=%.o)
BUILD_OBJS		= $(SRCS:%.c=$(BUILD_DIR)/%.o)
ASM_FILES		= $(SRCS:.c=.s)

all: $(NAME)
	nm --defined-only -f sysv $(NAME) | grep -v 'wm.'

# We need this for the output to go in the right place.  It will default to
# empty if make was configured to work with a cc that can't grok -c and -o
# together.  You can't compile the C library with such a compiler.
OUTPUT_OPTION	= -o $@

$(BUILD_DIR)/%.o:	%.c
		@if [ ! -d $(@D) ]; then mkdir -pv $(@D); fi
		$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(INCLUDE_FLAGS) -c $< -o $@

$(NAME): $(BUILD_OBJS)
		$(LIB_COMMAND) $(NAME) $(BUILD_OBJS)

clean:
		$(RM) -f $(OBJS) $(ASM_FILES)

fclean: clean
		$(RM) -fr $(NAME) $(BUILD_DIR) a.out

re: fclean all

norm:
		@norminette $(SRCS)

.PHONY: all clean flean re bonus $(BUILD_DIR)
