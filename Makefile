NAME        = wordle
CC          = cc
CFLAGS      = -Wall -Werror -Wextra -fpie
DEBUG_FLAGS = -g -DVERBOSE=1

LIBFT_DIR   = inc/libft
LIBFT       = $(LIBFT_DIR)/libft.a

INCLUDES    = -I inc -I $(LIBFT_DIR)
EXT_LIBS    = -lreadline

SRC_DIR     = src
OBJ_DIR     = obj

SRCS = \
	main.c \

OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

# ==========================
# Build rules
# ==========================

all: $(LIBFT) $(NAME)

# Debug-Build: CFLAGS erweitern und komplett neu bauen
debug: CFLAGS += $(DEBUG_FLAGS)
debug: re

# Objektdateien
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c inc/wordle.h
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Executable
$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(EXT_LIBS) -o $(NAME)

# Libft bauen
$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) all

# ==========================
# Clean rules
# ==========================

clean:
	@rm -f $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all debug clean fclean re
