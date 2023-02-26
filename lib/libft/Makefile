# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: cyuzbas <cyuzbas@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2021/10/11 12:51:21 by cyuzbas       #+#    #+#                  #
#    Updated: 2023/02/26 15:57:25 by cyuzbas       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME    	= 	libft.a
CC			= 	gcc
CFLAGS		= 	-Wall -Wextra -Werror

SRCS		=	ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c \
				ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
				ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
				ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c \
				ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c \
				ft_strcmp.c ft_strdup.c ft_striteri.c ft_strjoin.c \
				ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c \
				ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c \
				ft_substr.c ft_tolower.c ft_toupper.c ft_abs.c\
				ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c \
				ft_lstdelone.c ft_lstiter.c ft_lstlast.c \
				ft_lstmap.c ft_lstnew.c ft_lstsize.c

BUILD_DIR	=	obj/

OBJS = $(addprefix $(BUILD_DIR), $(SRCS:.c=.o))

RESET		=	"\033[0m"
GREEN		=	"\033[0;32m"
RED			=	"\033[0;31m"
YELLOW		=	"\033[0;33m"

all: $(BUILD_DIR) $(NAME)

$(BUILD_DIR):
	@mkdir $@

$(NAME): $(OBJS)
	@ar rc $(NAME) $(OBJS)
	@echo $(GREEN)"Libft is ready..!"$(RESET)

$(BUILD_DIR)%.o: %.c | $(BUILD_DIR)
	@printf $(YELLOW)"%-33.33s\r"$(RESET) $@
	@$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@rm -rdf $(BUILD_DIR)

fclean: clean
	@rm -f $(NAME)
	@echo $(RED)"Libft deleted"$(RESET)
	
re: fclean all

.PHONY: all clean fclean re