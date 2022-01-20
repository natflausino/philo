
NAME = philo

CFLAGS = -Wall -Wextra -Werror
INCLUDES = ./includes/philo.h

SRC_PATH =	./source \

SRC =		main.c\
			parse.c\
			time.c\
			ft_atoi.c\
			ft_isdigit.c\
			ft_memset.c\


OBJ_DIR	=	./builds
OBJ		=	$(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))

vpath %.c $(SRC_PATH)

all: $(NAME)

$(NAME): $(OBJ)
		gcc $(CFLAGS) -pthread -g -o $(NAME) $(OBJ) -I includes

$(OBJ_DIR)/%.o:	%.c ./includes/philo.h
	mkdir -p $(OBJ_DIR)
	gcc -c -o $@ $(CFLAGS) -I includes -g3 $<

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file="out.txt" ./philo 5 20 21 80 5
#	valgrind --tool=helgrind ./philo 5 20 21 80 5

git:
	@git add .
	@git commit -m "$m"
	@git push
#make git m="blablabla"

clean:
		rm -f $(OBJ)
		rm -rf ./buldis

fclean: clean
		rm -f $(NAME) $(OBJ)

re: fclean all