# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amysiv <amysiv@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/17 20:08:38 by ydidenko          #+#    #+#              #
#    Updated: 2024/12/03 21:23:50 by amysiv           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			=	libft.a

OBJ_DIR			=	obj
SRC_DIR			=	src

GREEN=\033[0;32m
NC=\033[0m

SRCS			= \
					$(SRC_DIR)/checkers/ft_isalnum.c \
					$(SRC_DIR)/checkers/ft_isalpha.c \
					$(SRC_DIR)/checkers/ft_isascii.c \
					$(SRC_DIR)/checkers/ft_isdigit.c \
					$(SRC_DIR)/checkers/ft_isprint.c \
					$(SRC_DIR)/ft_printf/ft_printf.c \
					$(SRC_DIR)/ft_printf/ft_printf_utils.c \
					$(SRC_DIR)/ft_printf/print_char.c \
					$(SRC_DIR)/ft_printf/print_hex.c \
					$(SRC_DIR)/ft_printf/print_nbr.c \
					$(SRC_DIR)/ft_printf/print_percent.c \
					$(SRC_DIR)/ft_printf/print_ptr.c \
					$(SRC_DIR)/ft_printf/print_s.c \
					$(SRC_DIR)/ft_printf/print_unknown.c \
					$(SRC_DIR)/ft_printf/print_unsigned.c \
					$(SRC_DIR)/get_next_line/get_next_line.c \
					$(SRC_DIR)/linklist/ft_lstadd_back.c \
					$(SRC_DIR)/linklist/ft_lstadd_front.c \
					$(SRC_DIR)/linklist/ft_lstclear.c \
					$(SRC_DIR)/linklist/ft_lstdelone.c \
					$(SRC_DIR)/linklist/ft_lstiter.c \
					$(SRC_DIR)/linklist/ft_lstlast.c \
					$(SRC_DIR)/linklist/ft_lstnew.c \
					$(SRC_DIR)/linklist/ft_lstsize.c \
					$(SRC_DIR)/memory/ft_bzero.c \
					$(SRC_DIR)/memory/ft_calloc.c \
					$(SRC_DIR)/memory/ft_memchr.c \
					$(SRC_DIR)/memory/ft_memcmp.c \
					$(SRC_DIR)/memory/ft_memcpy.c \
					$(SRC_DIR)/memory/ft_memmove.c \
					$(SRC_DIR)/memory/ft_memset.c \
					$(SRC_DIR)/string/ft_atoi.c \
					$(SRC_DIR)/string/ft_atol.c \
					$(SRC_DIR)/string/ft_itoa.c \
					$(SRC_DIR)/string/ft_split.c \
					$(SRC_DIR)/string/ft_splitset.c \
					$(SRC_DIR)/string/ft_strchr.c \
					$(SRC_DIR)/string/ft_strchrset.c \
					$(SRC_DIR)/string/ft_strdup.c \
					$(SRC_DIR)/string/ft_striteri.c \
					$(SRC_DIR)/string/ft_strjoin3.c \
					$(SRC_DIR)/string/ft_strjoin.c \
					$(SRC_DIR)/string/ft_strlcat.c \
					$(SRC_DIR)/string/ft_strlcpy.c \
					$(SRC_DIR)/string/ft_strlen.c \
					$(SRC_DIR)/string/ft_strmapi.c \
					$(SRC_DIR)/string/ft_strncmp.c \
					$(SRC_DIR)/string/ft_strnstr.c \
					$(SRC_DIR)/string/ft_strrchr.c \
					$(SRC_DIR)/string/ft_strtrim.c \
					$(SRC_DIR)/string/ft_substr.c \
					$(SRC_DIR)/string/ft_tolower.c \
					$(SRC_DIR)/string/ft_toupper.c \
					$(SRC_DIR)/write/ft_putchar_fd.c \
					$(SRC_DIR)/write/ft_putendl_fd.c \
					$(SRC_DIR)/write/ft_putnbr_fd.c \
					$(SRC_DIR)/write/ft_putstr_fd.c

OBJS 			=	$(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))
VPATH			=	$(dir $(SRCS))

CC				=	cc
RM				=	rm -f
CFLAGS			=	-Wall -Wextra -Werror -I. -fPIC

all:			$(NAME)

$(NAME):		$(OBJS)
				@ar rcs $(NAME) $(OBJS)
				@echo "$(GREEN)Compiled: libft$(NC)"

$(OBJ_DIR)/%.o:	%.c
				@mkdir -p $(OBJ_DIR)
				@$(CC) $(CFLAGS) -c $< -o $@

clean:
				@$(RM) $(OBJS)
				@echo "$(GREEN)Cleaned: libft$(NC)"

fclean:			clean
				@$(RM) $(NAME)

re:				fclean $(NAME)

test:			$(NAME) test.c
				@$(CC) $(CFLAGS) -o test test.c -L. -lft -g

.PHONY:			clean fclean re all
