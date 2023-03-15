# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: cyuzbas <cyuzbas@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2023/02/26 15:00:38 by cyuzbas       #+#    #+#                  #

#    Updated: 2023/03/15 15:38:04 by cyuzbas       ########   odam.nl          #

#    Updated: 2023/03/15 15:47:18 by hwang         ########   odam.nl          #

#                                                                              #
# **************************************************************************** #

NAME	= cub3d

SRC_DIR = src/
BUILD_DIR = build/
BUILD_SUBDIRS = build/parse

UNPREFIXED_SRC	= main.c\
				utils.c\
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

# CFLAGS	= -Wextra -Wall -Werror
CFLAGS	= -Wextra -Wall -Werror -Wunreachable-code -fsanitize=address
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

run: all 
	./cub3d map_files/simple.cub

.PHONY: all, clean, fclean, re, libmlx, libft