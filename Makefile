NAME			= minishell

PURPLE			:= \033[0;34m
PINK			:= \033[0;35m
RESET			:= \033[0m

SRC_DIR 		= src
SRCS			= $(wildcard $(SRC_DIR)/*.c)
HEADERS			= $(wildcard includes/*.h)
OBJ_DIR			= obj
OBJS			= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
INCS			= -Iincludes
CC				= cc 
RM				= rm -rf
CFLAGS			= #-Wall -Wextra -Werror #-fsanitize=address -g
LIBFLAGS		= -lreadline
RLFLAG			= -I $(HOME)/goinfre/.brew/opt/readline/include/ -L $(HOME)/goinfre/.brew/opt/readline/lib/ -lreadline
MK				= mkdir -p

LIBFT			= ./libraries/libft/libft.a
LIBFT_PATH		= ./libraries/libft

all:			$(OBJ_DIR) $(NAME)

$(OBJ_DIR): 	$(SRC_DIR)
				@$(MK) $(OBJ_DIR)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c $(HEADERS) Makefile
				$(CC) $(CFLAGS) $(INCS) -c $< $(RLFLAG) -o $@

$(NAME):		$(OBJS) $(LIBFT)
				@$(CC) $(CFLAGS) $(INCS) -o $(NAME) $(OBJS) $(LIBFT) $(LIBFLAGS) $(RLFLAGS)
				@echo "$(PINK)Minishell successfully compiled!$(RESET)\n"

clean:			
				@$(MAKE) clean -C ${LIBFT_PATH}  > /dev/null 2>&1
				$(RM) $(OBJ_DIR)
				@echo "$(PINK)Minishell successfully cleaned!$(RESET)\n"

fclean:			clean
				@$(RM) $(NAME)
				
re:				fclean all

.PHONY:			all clean fclean re