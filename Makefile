NAME 			=	minishell

LIBFT 			=	libft
SRC_DIR			=	src
OBJ_DIR			=	obj
INC_DIR			=	includes

GREEN=\033[0;32m
NC=\033[0m

LIBFT_NAME		=	$(addprefix $(LIBFT)/, libft.a)
HEADERS			=	-I$(INC_DIR)
SRCS			=	$(SRC_DIR)/main.c $(wildcard $(SRC_DIR)/**/*.c)
OBJS 			=	$(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))
VPATH			=	$(dir $(SRCS))

CC				=	gcc
RM				=	rm -f
CFLAGS			=	-Wall -Wextra -Werror -g
RFLAGS = 			-lreadline

all:			libft $(NAME)

libft:
				@make -C $(LIBFT)

$(NAME):		$(OBJS)
				@$(CC) $(CFLAGS) $(OBJS) ./libft/libft.a -o $(NAME) $(RFLAGS)
				@echo "$(GREEN)Compiled$(NC)"
$(OBJ_DIR)/%.o:	%.c
				@mkdir -p $(OBJ_DIR)
				@$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS)

clean:
				@$(RM) $(OBJS)
				@make clean -C $(LIBFT)
				@$(RM) test
				@echo "$(GREEN)Cleaned$(NC)"

fclean:			clean
				@$(RM) $(NAME)

re:				fclean $(NAME)

test:			all
				$(CC) -I$(INC_DIR) -o test test.c $(NAME)

.PHONY:			clean fclean re all test