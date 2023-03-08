# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: cyuzbas <cyuzbas@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2023/02/26 15:00:38 by cyuzbas       #+#    #+#                  #
#    Updated: 2023/03/08 12:29:08 by cyuzbas       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	= cub3d

SRC_DIR = src/
BUILD_DIR = build/
BUILD_SUBDIRS = build/parse

UNPREFIXED_SRC	= main.c \
				parse/parse.c
				
OBJS = $(addprefix $(BUILD_DIR), $(UNPREFIXED_SRC:.c=.o))
SRCS = $(addprefix $(SRC_DIR), $(UNPREFIXED_SRC))

CFLAGS	= -Wextra -Wall -Werror -Wunreachable-code
LIBMLX	= ./lib/MLX42
LIBFT	= ./lib/libft

HEADERS	= -I ./inc -I $(LIBMLX)/include 
LIBS	= $(LIBMLX)/build/libmlx42.a -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit $(LIBFT)/libft.a
# LIBS	= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm $(LIBFT)/libft.a


all: libmlx libft $(BUILD_DIR) $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4
	
libft:
	@$(MAKE) -C $(LIBFT)/
	
$(BUILD_DIR):
	@mkdir $@

$(BUILD_SUBDIRS):
	@mkdir $@

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)


$(BUILD_DIR)%.o: $(SRC_DIR)%.c | $(BUILD_DIR) $(BUILD_SUBDIRS)
	@$(CC) $(FLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"



clean:
	@rm -rdf $(BUILD_DIR)
	@rm -rf $(LIBMLX)/build
	@$(MAKE) clean -C $(LIBFT)/

fclean: clean
	@rm -rf $(NAME)
	@$(MAKE) fclean -C $(LIBFT)/

re: clean all

.PHONY: all, clean, fclean, re, libmlx, libft