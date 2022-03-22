NAME = minishell
CC = cc
OBJDIR = ./objs
LIBFT = libft/libft.a
CFLAGS = -g -Wall -Wextra -Werror
HEADER = minishell.h
SRCDIR = ./srcs
HEADDIR = ./includes
SRC = $(wildcard $(SRCDIR)/*.c)
OBJ = $(addprefix $(OBJDIR)/,$(notdir $(SRC:.c=.o)))
LIBFT_DIR = libft/

all:    $(LIBFT) $(NAME)

$(OBJDIR)/%.o :	$(SRCDIR)/%.c $(HEADDIR)/$(HEADER)
	@$(CC) $(FLAGS) -c $< -o $@

$(NAME):	$(OBJDIR) $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(LIBFT_DIR)/libft.a -I $(HEADER) $(OBJ) -lreadline
	@echo "\033[32mminishell compile"

$(OBJDIR):
	@if [ ! -d $(OBJDIR) ] ; then echo "creating $(OBJDIR)" ; mkdir $(OBJDIR); fi

$(LIBFT):
	@make -C $(LIBFT_DIR)

clean:
	@if [ -d $(OBJDIR) ] ; then echo "\033[32mdeleting $(OBJDIR)" ; rm -r $(OBJDIR); fi
	@make fclean -C $(LIBFT_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
