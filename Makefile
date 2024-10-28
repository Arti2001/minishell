NAME 			=	minishell

LIBFT 			=	libft
SRC_DIR			=	src
OBJ_DIR			=	obj
INC_DIR			=	includes

GREEN=\033[0;32m
NC=\033[0m

LIBFT_NAME      =	$(addprefix $(LIBFT)/, libft.a)
SRCS			=	$(SRC_DIR)/main.c $(wildcard $(SRC_DIR)/**/*.c)
OBJS 			=	$(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))
VPATH			=	$(dir $(SRCS))

CC				=	gcc
RM				=	rm -f
CFLAGS			=	-Wall -Wextra -Werror -g
RFLAGS = 			-lreadline

all:			$(NAME)

$(NAME):		$(OBJS)
				@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_NAME) -I $(INC_DIR) -o $(NAME) $(RFLAGS)
				@echo "$(GREEN)Compiled$(NC)"
$(OBJ_DIR)/%.o:	%.c
				@mkdir -p $(OBJ_DIR)
				@$(CC) $(CFLAGS) -c $< -o $@
$(LIBFT_NAME) :
	@make -C $(LIBFT)

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