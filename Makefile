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
CFLAGS			= -Wall -Wextra -Werror -fsanitize=address -g
#LIBFLAGS		= -lreadline
LIBFLAGS		= -Llib/readline/lib -lreadline -lhistory

ifeq ($(PLATFORM), Linux)
	LFLAGS	+=	-ltinfo
endif

MK				= mkdir -p

LIBFT			= ./libraries/libft/libft.a
LIBFT_PATH		= ./libraries/libft

PRINTF			= printf

TOTAL_SRC		:= $(shell expr $(shell echo -n $(SRCS) | wc -w) - $(shell ls -l $(OBJ_DIR) 2>&1 | grep ".o" | wc -l) + 1)
#				ensures that division by zero errors are avoided when calculating the percentage of source files processed 
				ifeq ($(shell test $(TOTAL_SRC) -le 0; echo $$?),0)
					TOTAL_SRC := $(shell echo -n $(SRCS) | wc -w)
				endif
CURRENT_SRC		:= 0
SRC_PCT			= $(shell expr 100 \* $(CURRENT_SRC) / $(TOTAL_SRC))

all:			$(OBJ_DIR) $(NAME)

$(OBJ_DIR): 	$(SRC_DIR)
				@$(MK) $(OBJ_DIR)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c $(HEADERS) Makefile
				@$(eval CURRENT_SRC = $(shell expr $(CURRENT_SRC) + 1))
				@$(PRINTF) "\r%100s\r[ %d/%d (%d%%) ] Compiling $(PURPLE)$<$(RESET)..." "" $(CURRENT_SRC) $(TOTAL_SRC) $(SRC_PCT)
				@$(CC) $(CFLAGS) $(INCS) -c $< -o $@

$(NAME):		$(OBJS) $(LIBFT)
				@$(CC) $(CFLAGS) $(INCS) -o $(NAME) $(OBJS) $(LIBFT) $(LIBFLAGS)
				@$(PRINTF) "\r%100s\r$(PINK)✧ $(PURPLE)Minishell $(PINK)successfully compiled! ✧$(RESET)\n"

clean:			
				@$(MAKE) clean -C ${LIBFT_PATH}  > /dev/null 2>&1
				@$(RM) $(OBJ_DIR)
				@$(PRINTF) "$(PINK)✧ $(PURPLE)Minishell $(PINK)successfully cleaned! ✧$(RESET)\n"

fclean:			clean
				@$(RM) $(NAME)
				
re:				fclean all

.PHONY:			all clean fclean re

#####################################################################################################################
#																											  		#
#				-le			Less than or equal																  		#
#																											  		#
#				echo $$?	To capture the exit status of the test command.									  		#
#				The $$ is used to escape the dollar sign because the Makefile uses $ for variable expansion.  		#
#				The ? represents the exit status of the previous command, in this case, the test command.	  		#
#																											  		#
#####################################################################################################################