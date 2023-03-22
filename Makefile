# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: cyuzbas <cyuzbas@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2023/02/26 15:00:38 by cyuzbas       #+#    #+#                  #
#    Updated: 2023/03/22 20:26:12 by cyuzbas       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

RESET		=	"\033[0m"
GREEN		=	"\033[0;32m"
RED			=	"\033[0;31m"
YELLOW		=	"\033[0;33m"

NAME	= cub3d

SRC_DIR = src/
BUILD_DIR = build/
BUILD_SUBDIRS = build/parse

UNPREFIXED_SRC	= main.c\
				hook.c\
				draw_map.c\
				draw_utils.c\
				minimap.c\
				parse/parse.c\
				parse/parse_wall.c\
				parse/parse_colour.c\
				parse/parse_map.c\
				parse/check_map.c\
				parse/get_next_line.c\
				parse/init_cube.c\
				parse/clean_cube.c\
				
OBJS = $(addprefix $(BUILD_DIR), $(UNPREFIXED_SRC:.c=.o))
SRCS = $(addprefix $(SRC_DIR), $(UNPREFIXED_SRC))

CFLAGS	= -Wextra -Wall -Werror -Wunreachable-code
LIBMLX	= ./lib/MLX42
LIBFT	= ./lib/libft

HEADERS	= -I ./inc -I $(LIBMLX)/include
LIBS	= $(LIBMLX)/build/libmlx42.a -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit $(LIBFT)/libft.a
# LIBS	= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm lib/libft/libft.a

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
	@echo $(GREEN)"Cub3d is ready to execute...! "$(RESET)

$(BUILD_DIR)%.o: $(SRC_DIR)%.c | $(BUILD_DIR) $(BUILD_SUBDIRS)
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)
	@printf $(YELLOW)"%-33.33s\r"$(RESET) $@

clean:
	@rm -rdf $(BUILD_DIR)
	@rm -rf $(LIBMLX)/build
	@$(MAKE) clean -C $(LIBFT)/

fclean: clean
	@rm -rf $(NAME)
	@$(MAKE) fclean -C $(LIBFT)/
	@echo $(RED)"Cub3d deleted"$(RESET)

re: clean all

run: all 
	./cub3d map_files/normal.cub

.PHONY: all, clean, fclean, re, libmlx, libft, run
