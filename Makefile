NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS=
ifeq ($(DEBUG), 1)
	CFLAGS += -fsanitize=address -g
endif
DEPFLAGS = -MMD -MP
SYSLIBFLAGS = -lreadline
OBJ_DIR := obj
DEP_DIR := $(OBJ_DIR)/.deps
INC_DIR := includes
# TMP_DIR := tmp
SRC_DIRS := $(shell find ./srcs -type d)
vpath %.c $(SRC_DIRS)
vpath %.h $(INC_DIR)
vpath %.d $(DEP_DIR)
CFLAGS += -I$(INC_DIR)

LIBFT_DIR = $(INC_DIR)/libft
LIBFT = libft.a
LIBFT_LIB = $(LIBFT_DIR)/$(LIBFT)
LIBFTFLAGS = -L$(LIBFT_DIR) -lft
LIBFT_REPO = https://github.com/blueyaGIT/libft.git

# Regular Colors
BLACK       = \033[30m
RED         = \033[31m
GREEN       = \033[32m
YELLOW      = \033[33m
BLUE        = \033[34m
MAGENTA     = \033[35m
CYAN        = \033[36m
WHITE       = \033[37m
LIGHT_PINK  = \033[38;5;168m
NC          = \033[0m   # No Color (Reset)

# Other Formatting
UNDERLINE   = \033[4m
REVERSED    = \033[7m
BLINK       = \033[5m
ITALIC      = \033[3m
STRIKE      = \033[9m
CLEAR_LINE  = \033[2K\r

# Source files
SRCS	:=	main.c \

# BUILTINS
SRCS	+=	cd.c \
			echo.c \
			exit.c \
			pwd.c \

# ENV
SRCS	+=	env_get.c \
			env_idx.c \

# LAURA
SRCS	+=	create_token.c \
			token_to_list.c \

# SHELL
SRCS	+=	shell_static.c \

# SIGNALS
SRCS	+=	handler_hrdc.c \
			handler_nrml.c \
			init_signals.c \

# UTILS
SRCS	+=	posix_log.c \
			print_logo.c \

# Object files
OBJS := $(addprefix $(OBJ_DIR)/, $(SRCS:%.c=%.o))

# HEADER_FILES := builtin.h \
# 				env.h \
# 				exec.h \
# 				format.h \
# 				gcollector.h \
# 				laura.h \
# 				libft.h \
# 				minishell.h \
# 				posix_log.h \
# 				shell.h \
# 				signals.h \
# 				utils.h \

# HEADER = $(addprefix $(INC_DIR)/, $(HEADER_FILES))

TOTAL_SRCS = $(words $(SRCS))
CURRENT = 0

# Default rule to compile all
all: $(NAME)

-include $(OBJS:.o=.d)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(eval CURRENT := $(shell echo $$(($(CURRENT) + 1))))
	@$(eval PERCENT := $(shell echo $$(($(CURRENT) * 100 / $(TOTAL_SRCS)))))
	@printf "$(CLEAR_LINE)$(YELLOW)🚧 Compiling $(PERCENT)%% [$(CURRENT)/$(TOTAL_SRCS)] $(CYAN)$<$(NC) 🚧"
	@$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@

# Initialize submodules
init-submodules: init-libft

# Initialize libft
init-libft:
	@sleep 0.15
	@if [ ! -d "$(LIBFT_DIR)" ]; then \
		echo "$(YELLOW)🚧 Adding LIBFT submodule 🚧$(NC)"; \
		git submodule add $(LIBFT_REPO) $(LIBFT_DIR) > /dev/null 2>&1 || (echo "$(RED)Failed to add libft submodule$(NC)" && exit 1); \
	elif [ -z "$$(ls -A $(LIBFT_DIR) 2>/dev/null)" ]; then \
		echo "$(CYAN)🔄 Updating LIBFT submodule 🔄$(NC)"; \
		git submodule update --init --recursive $(LIBFT_DIR) > /dev/null 2>&1 || (echo "$(RED)Failed to update libft submodule$(NC)" && exit 1); \
	else \
		echo "$(GREEN)✅ LIBFT submodule is already initialized ✅$(NC)"; \
	fi

# Remove submodules
remove-submodules: remove-libft

# Remove libft
remove-libft:
	@if [ -d "$(LIBFT_DIR)" ]; then \
		git submodule deinit -q -f $(LIBFT_DIR) > /dev/null 2>&1; \
		git rm -q -f $(LIBFT_DIR) > /dev/null 2>&1; \
		rm -rf .git/modules/$(LIBFT_DIR) > /dev/null 2>&1; \
	fi

# Rule to compile libft
$(LIBFT_LIB): init-libft
	@if [ ! -f "$(LIBFT_LIB)" ]; then \
		echo "$(CLEAR_LINE)$(YELLOW)🚧 Building LIBFT 🚧$(NC)"; \
		$(MAKE) -C $(LIBFT_DIR); \
	fi

# Rule to compile program
$(NAME): init-submodules $(LIBFT_LIB) $(OBJS)
	@echo "$(CLEAR_LINE)$(YELLOW)🚧 Building 🧚 Minishell 🧚 🚧$(NC)"
	@$(CC) -o $(NAME) $(OBJS) $(LIBFTFLAGS) $(SYSLIBFLAGS) $(LDFLAGS)
	@echo "$(CLEAR_LINE)$(GREEN)✅🧚 Done Compiling 🧚✅$(NC)"

# Clean object files and libraries
clean: remove-submodules
	@rm -rf $(OBJ_DIR)
	@rm -rf $(LIBFT_DIR)

# Clean all generated files
fclean: clean
	@echo "$(YELLOW)🚧 Cleaning 🚧$(NC)"
	@sleep 0.15
	@printf "$(RED)🧹 Cleaning in Progress 🧹$(NC)\n"
	@sleep 0.15
	@printf "$(YELLOW)🛁 Scrubbing Code 🛁$(NC)\n"
	@sleep 0.15
	@printf "$(CYAN)🧽 Polishing Project 🧽$(NC)\n"
	@sleep 0.15
	@printf "$(MAGENTA)🧴 Tidying Up 🧴$(NC)\n"
	@sleep 0.15
	@printf "$(GREEN)✅ Done Cleaning ✅$(NC)\n"
	@rm -rf $(NAME)

# Rebuild everything
re: fclean all

# Rebuild everything faster
fastre: remove-submodules
	@rm -rf $(OBJ_DIR)
	@rm -rf $(LIBFT_DIR)
	@rm -rf $(NAME)
	@make

# Phony targets
.PHONY: all clean fclean re libft init-submodules remove-submodules fastre
