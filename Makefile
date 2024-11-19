NAME 			=	minishell

LIBFT 			=	libft
SRC_DIR			=	src
OBJ_DIR			=	obj
INC_DIR			=	includes

GREEN=\033[0;32m
NC=\033[0m

LIBFT_PATH		=	$(addprefix $(LIBFT)/, libft.a)
HEADERS			=	-I$(INC_DIR)
SRCS			=	$(SRC_DIR)/main.c $(wildcard $(SRC_DIR)/**/*.c)
OBJS 			=	$(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))
VPATH			=	$(dir $(SRCS))

CC				=	gcc
RM				=	rm -f
CFLAGS			=	-Wall -Wextra -Werror -g $(HEADERS)
RFLAGS 			=	-lreadline

all:			libft $(NAME)

libft:
				@make -C libft

$(NAME):		$(OBJS)
				@$(CC) $(CFLAGS) $(OBJS) -I $(INC_DIR) $(LIBFT_PATH) -o $(NAME) $(RFLAGS)
				@echo "$(GREEN)Compiled$(NC)"
$(OBJ_DIR)/%.o:	%.c
				@mkdir -p $(OBJ_DIR)
				@$(CC) $(CFLAGS) -c $< -o $@

clean:
				@$(RM) $(OBJS)
				@make clean -C $(LIBFT)
				@echo "$(GREEN)Cleaned$(NC)"

fclean:			clean
				@$(RM) $(NAME)
				@$(RM) $(LIBFT_PATH)

re:				fclean all

.PHONY:			clean fclean re all test libft