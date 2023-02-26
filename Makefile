# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: cyuzbas <cyuzbas@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2023/02/26 15:00:38 by cyuzbas       #+#    #+#                  #
#    Updated: 2023/02/26 21:51:49 by cyuzbas       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	= cub3d
USER	= cyuzbas
# USER	= hwang

CFLAGS	= -Wextra -Wall -Werror -Wunreachable-code
LIBMLX	= ./lib/MLX42

HEADERS	= -I ./inc -I $(LIBMLX)/include
LIBS	= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
SRCS	= $(shell find ./src -iname "*.c")
OBJS	= ${SRCS:.c=.o}

all: libmlx $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX)/build

fclean: clean
	@rm -rf $(NAME)

re: clean all

.PHONY: all, clean, fclean, re, libmlx