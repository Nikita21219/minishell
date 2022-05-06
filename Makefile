NAME = minishell
CC = cc
OBJDIR = ./objs
LIBFT = libft/libft.a
CFLAGS = -g -Wall -Wextra -Werror -fsanitize=address
HEADER = minishell.h
SRCDIR = ./srcs
HEADDIR = ./includes
IREADFL = -I/Users/${USER}/.brew/opt/readline/include
LREADFL = -L/Users/${USER}/.brew/opt/readline/lib
SRC = $(wildcard $(SRCDIR)/*.c)
OBJ = $(addprefix $(OBJDIR)/,$(notdir $(SRC:.c=.o)))
LIBFT_DIR = libft/

all:    $(LIBFT) $(NAME)

$(OBJDIR)/%.o :	$(SRCDIR)/%.c $(HEADDIR)/$(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@ ${IREADFL}

$(NAME):	$(OBJDIR) $(OBJ)
	@$(CC) $(CFLAGS) -lreadline ${IREADFL} ${LREADFL}  -o $(NAME) $(LIBFT_DIR)libft.a -I$(HEADER) $(OBJ) 
	@echo "\033[32mminishell compile\033[0m"

$(OBJDIR):
	@if [ ! -d $(OBJDIR) ] ; then mkdir $(OBJDIR); fi

$(LIBFT):
	@make -C $(LIBFT_DIR)

clean:
	@if [ -d $(OBJDIR) ] ; then rm -r $(OBJDIR); fi
	@make fclean -C $(LIBFT_DIR)
	@echo "\033[32mclean minishell done\033[0m"


fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
