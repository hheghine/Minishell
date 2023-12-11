# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbalasan <hbalasan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/12 01:49:43 by hbalasan          #+#    #+#              #
#    Updated: 2023/12/12 01:52:56 by hbalasan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell

PLATFORM		= $(shell uname -s)

PURPLE			:= \033[0;34m
PINK			:= \033[0;35m
RESET			:= \033[0m

SRC_DIR 		= src
SRCS			= $(wildcard $(SRC_DIR)/*.c)
HEADERS			= $(wildcard includes/*.h)
OBJ_DIR			= obj
OBJS			= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
INCS			= -I./includes -I./readline_heghine/include
CC				= cc 
RM				= rm -rf
CFLAGS			= -fsanitize=address -g #-Wall -Wextra -Werror
LIBFLAGS		= -Lreadline_heghine/lib -lreadline -lhistory

ifeq ($(PLATFORM), Linux)
	LFLAGS	+=	-ltinfo
	LIBFLAGS = -lreadline -lhistory
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

all:			readline_install libft_compile $(OBJ_DIR) $(NAME) 

readline_install:
				@$(MK) readline_heghine
				@echo -n "$(PURPLE)Compiling Readline: "
				@./readline_config.sh readline_heghine > /dev/null 2>&1 & \
				pid=$$!; \
				while ps -p $$pid > /dev/null; do \
					printf "$(PINK)✧$(RESET)"; \
					sleep 0.5; \
				done; \
				echo "$(PURPLE) Readline compiled.$(RESET)"

libft_compile:
				@echo -n "$(PURPLE)Compiling Libft: "
				@$(MAKE) -C $(LIBFT_PATH) > /dev/null 2>&1 & \
				pid=$$!; \
				while ps -p $$pid > /dev/null; do \
					printf "$(PINK)✧$(RESET)"; \
					sleep 0.5; \
				done; \
				echo "$(PURPLE) Libft compiled.$(RESET)"

$(OBJ_DIR): 	$(SRC_DIR)
				@$(MK) $(OBJ_DIR)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c $(HEADERS) Makefile
				@$(eval CURRENT_SRC = $(shell expr $(CURRENT_SRC) + 1))
				@$(PRINTF) "\r%100s\r[ %d/%d (%d%%) ] Compiling $(PURPLE)$<$(RESET)..." "" $(CURRENT_SRC) $(TOTAL_SRC) $(SRC_PCT)
				@$(CC) $(CFLAGS) $(INCS) -c $< -o $@

$(NAME):		$(OBJS) $(LIBFT)
				@$(CC) $(CFLAGS) $(INCS) -o $(NAME) $(OBJS) $(LIBFT) $(LIBFLAGS)
				@$(PRINTF) "\r%100s\r$(PINK)✧ $(PURPLE)Minishell $(PINK)successfully compiled! ✧$(RESET)\n"
			
configure:
				mkdir -p readline-8.2
				./readline_config.sh readline-8.2

clean:			clean_lib clean_readline
				@$(RM) $(OBJ_DIR)
				@$(PRINTF) "$(PINK)☽ $(PURPLE)Minishell $(PINK)successfully cleaned!$(RESET)\n"

clean_readline:
				@$(RM) -r readline_heghine
				@$(PRINTF) "$(PINK)☽ Readline $(PINK)successfully cleaned!$(RESET)\n"

clean_lib:
				@$(MAKE) clean -C $(LIBFT_PATH) > /dev/null 2>&1
				@$(PRINTF) "$(PINK)☽ Libft $(PINK)successfully cleaned!$(RESET)\n"

fclean:			clean
				@$(RM) $(NAME)
				
re:				fclean all

.PHONY:			all clean fclean re readline_install libft_compile

#####################################################################################################
#																									#
#	-le			Less than or equal																	#
#																									#
#	echo $$?	To capture the exit status of the test command.										#
#	The $$ is used to escape the dollar sign because the Makefile uses $ for variable expansion. 	#
#	The ? represents the exit status of the previous command, in this case, the test command.		#
#																									#
#####################################################################################################