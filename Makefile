NAME			=	philo

CFLAGS			=	-Wall -Wextra -Werror -MMD
EFLAGS			=	#-pthread -fsanitize=thread -g

DIR_SRC			=	src
DIR_OBJ			=	obj

SRC				=	philo_utils.c philo.c

OBJ				=	$(SRC:%.c=$(DIR_OBJ)/%.o)
DEP				=	$(SRC:%.c=$(DIR_OBJ)/%.d)

RED				=	$'\e[0;31m
GREEN			=	$'\e[32m
YELLOW			=	$'\e[33m
BOLD			=	$'\e[1m
UNDER			=	$'\e[4m
END				=	$'\e[0m

$(DIR_OBJ)/%.o:		$(DIR_SRC)/%.c Makefile
					mkdir -p $(DIR_OBJ)
					echo "Compiling - ${YELLOW}${BOLD}${UNDER}$<${END}..."
					$(CC) $(CFLAGS) -c $< -o $@
					echo "${GREEN}Done !${END}"

$(NAME):			$(OBJ)
					echo "Compiling - ${YELLOW}${BOLD}${UNDER}./$(NAME)${END}..."
					$(CC) $(EFLAGS) $(OBJ) -o $(NAME)
					echo "${GREEN}Done !${END}"
					echo "${GREEN}${BOLD}${UNDER}Task completed successfully.${END}"

all:				$(NAME)

clean:
					echo "Deleting - ${RED}${BOLD}${UNDER}./$(DIR_OBJ)/${END}..."
					rm -rf $(DIR_OBJ)
					echo "${GREEN}Done !${END}"
					echo "${GREEN}${BOLD}${UNDER}Task completed successfully.${END}"

fclean:
					echo "Deleting - ${RED}${BOLD}${UNDER}./$(DIR_OBJ)/${END}..."
					rm -rf $(DIR_OBJ)
					echo "${GREEN}Done !${END}"
					echo "Deleting - ${RED}${BOLD}${UNDER}./$(NAME)${END}..."
					rm -rf $(NAME)
					echo "${GREEN}Done !${END}"
					echo "${GREEN}${BOLD}${UNDER}Task completed successfully.${END}"

re:
					echo "Deleting - ${RED}${BOLD}${UNDER}./$(DIR_OBJ)/${END}..."
					rm -rf $(DIR_OBJ)
					echo "${GREEN}Done !${END}"
					echo "Deleting - ${RED}${BOLD}${UNDER}./$(NAME)${END}..."
					rm -rf $(NAME)
					echo "${GREEN}Done !${END}"
					make --no-print-directory all

git:
					git add .
					git commit -m "$(NAME)"
					git push

-include $(DEP)

.PHONY:				all clean fclean re git
.SILENT:
