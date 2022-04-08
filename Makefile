NAME = minishell
CC = cc
OBJDIR = ./objs
LIBFT = libft/libft.a
CFLAGS = -g -Wall -Wextra -Werror -fsanitize=address
HEADER = minishell.h
SRCDIR = ./srcs
HEADDIR = ./includes
SRC = $(wildcard $(SRCDIR)/*.c)
OBJ = $(addprefix $(OBJDIR)/,$(notdir $(SRC:.c=.o)))
LIBFT_DIR = libft/

all:    $(LIBFT) $(NAME)

$(OBJDIR)/%.o :	$(SRCDIR)/%.c $(HEADDIR)/$(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJDIR) $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(LIBFT_DIR)/libft.a -I $(HEADER) $(OBJ) -lreadline
	@echo "\033[32mminishell compile"

$(OBJDIR):
	@if [ ! -d $(OBJDIR) ] ; then mkdir $(OBJDIR); fi

$(LIBFT):
	@make -C $(LIBFT_DIR)

clean:
	@if [ -d $(OBJDIR) ] ; then rm -r $(OBJDIR); fi
	@make fclean -C $(LIBFT_DIR)
	@echo "\033[32mclean minishell done"

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
