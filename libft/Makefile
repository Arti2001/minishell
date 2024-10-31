# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amysiv <amysiv@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/17 20:08:38 by ydidenko          #+#    #+#              #
#    Updated: 2024/10/29 15:55:57 by amysiv           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			=	libft.a

OBJ_DIR			=	obj
SRC_DIR			=	src

GREEN=\033[0;32m
NC=\033[0m

SRCS			=	$(wildcard $(SRC_DIR)/*/*.c)
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
