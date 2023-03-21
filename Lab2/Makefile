NAME		=	lab1

CC			=	gcc -lstdc++ -pthread -lm -lboost_program_options -std=c++20 -O2
CFLAGS		=	-Wall -Werror -Wextra

HEADER_DIR	=	./inc
SRC_DIR		=	./src
OBJ_DIR		=	./obj

HEADER		=	namespaces.hpp

SRC			=	main.cc \
				settings.cc \
				generator.cc \
				cypher.cc \
				corr_test.cc \
				pocker_test.cc \
				serial_test.cc

OBJ			=	$(addprefix $(OBJ_DIR)/, $(SRC:.cc=.o)) \

RM_DIR		=	rm -rf
RM_FILE		=	rm -f

#COLORS
# C_NO		=	"\033[00m"
# C_OK		=	"\033[32m"
# C_GOOD		=	"\033[32m"

SUCCESS		=	$(C_GOOD)SUCCESS$(C_NO)
OK			=	$(C_OK)OK$(C_NO)

all			:	$(NAME)

$(OBJ)		: 	| $(OBJ_DIR)	

$(OBJ_DIR)	:
				@mkdir -p $(OBJ_DIR)
			
$(OBJ_DIR)/%.o	:	$(SRC_DIR)/%.cc ${HEADER_DIR}/*.hpp Makefile
					$(CC) $(CFLAG) -c $< -o $@


$(NAME)		:	$(OBJ)
				$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
				@echo "Compiling..." [ $(NAME) ] $(SUCCESS)

clean		:
				@$(RM_DIR) $(OBJ_DIR) $(RET_DIR)
				@echo "Cleaning..." [ $(OBJ_DIR) $(RET_DIR) ] $(OK)

fclean		:	clean
				@$(RM_FILE) $(NAME)
				@echo "Deleting..." [ $(NAME) ] $(OK)

re			:	fclean all

.PHONY		:	all, clean, fclean, re, test