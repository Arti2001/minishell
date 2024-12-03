NAME 			=	minishell

LIBFT 			=	libft
SRC_DIR			=	src
OBJ_DIR			=	obj
INC_DIR			=	includes

GREEN=\033[0;32m
NC=\033[0m

LIBFT_PATH		=	$(addprefix $(LIBFT)/, libft.a)
HEADERS			=	-I$(INC_DIR)
SRCS 			= \
					$(SRC_DIR)/main.c \
					$(SRC_DIR)/main_utils.c \
					$(SRC_DIR)/built_in/cd.c \
					$(SRC_DIR)/built_in/echo.c \
					$(SRC_DIR)/built_in/env.c \
					$(SRC_DIR)/built_in/exit.c \
					$(SRC_DIR)/built_in/export.c \
					$(SRC_DIR)/built_in/pwd.c \
					$(SRC_DIR)/built_in/setup.c \
					$(SRC_DIR)/built_in/unset.c \
					$(SRC_DIR)/environment/env_utils.c \
					$(SRC_DIR)/environment/llist_utils.c \
					$(SRC_DIR)/environment/set_env.c \
					$(SRC_DIR)/execution/free_utils.c \
					$(SRC_DIR)/execution/one_cmd.c \
					$(SRC_DIR)/execution/path_utils.c \
					$(SRC_DIR)/execution/redir_utils.c \
					$(SRC_DIR)/execution/setup_exec.c \
					$(SRC_DIR)/herdoc/herdoc.c \
					$(SRC_DIR)/herdoc/herdoc_utils.c \
					$(SRC_DIR)/multiple_cmd/child_process.c \
					$(SRC_DIR)/multiple_cmd/multi_cmd.c \
					$(SRC_DIR)/multiple_cmd/redir_multi_cmd.c \
					$(SRC_DIR)/parsing/combine_tokens.c \
					$(SRC_DIR)/parsing/convert_tokens.c \
					$(SRC_DIR)/parsing/convert_tokens_utils.c \
					$(SRC_DIR)/parsing/expand_vars.c \
					$(SRC_DIR)/parsing/expand_vars_str.c \
					$(SRC_DIR)/parsing/lexer.c \
					$(SRC_DIR)/parsing/parser.c \
					$(SRC_DIR)/parsing/split_tokens.c \
					$(SRC_DIR)/parsing/token.c \
					$(SRC_DIR)/parsing/tokenize_quotes.c \
					$(SRC_DIR)/parsing/tokenizer.c \
					$(SRC_DIR)/parsing/tokenize_sym.c \
					$(SRC_DIR)/parsing/utils.c \
					$(SRC_DIR)/parsing/validation.c \
					$(SRC_DIR)/signals/handlers.c \
					$(SRC_DIR)/signals/signals.c

OBJS 			=	$(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))
VPATH			=	$(dir $(SRCS))

CC				=	gcc
RM				=	rm -f
CFLAGS			=	-Wall -Wextra -Werror -g $(HEADERS) #-fsanitize=address
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