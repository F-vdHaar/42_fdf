# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fvon-der <fvon-der@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/01 22:19:53 by fvon-der          #+#    #+#              #
#    Updated: 2025/03/09 23:10:30 by fvon-der         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RESET_COLOR = \033[0m
YELLOW      = \033[1;33m
BLUE        = \033[1;34m
GREEN       = \033[1;32m
RED         = \033[1;31m

# Project names
NAME        = fdf
NAME_DEBUG  = fdf_debug

# Directories
OBJ_DIR     = obj/v2
SRC_DIR     = src/v2
INCLUDE_DIR = include/v2
LIB42_DIR   = lib/lib42
MLX_DIR     = lib/mlx

# Include paths for libraries and headers
INCLUDE     = -I$(INCLUDE_DIR) -I$(LIB42_DIR)/libft/include -I$(LIB42_DIR)/ft_printf/include -I$(LIB42_DIR)/gnl/include -I$(MLX_DIR)/include/MLX42

# Compiler, rm command, and flags
CC          = cc
MAKE        = make
RM          = rm -f
FLAGS       = -Wall -Wextra -Werror -Wunused -Wunreachable-code -Ofast -ffast-math -march=native -mtune=native -funroll-loops $(INCLUDE)

# Debug flags
DEBUG_FLAGS  = -Wall -Wextra $(INCLUDE) -g -O0 -fsanitize=undefined \
			   -fno-strict-aliasing -fno-omit-frame-pointer -fstack-protector -DDEBUG -fno-inline

# Libraries to link with
LIBRARIES = -L$(LIB42_DIR) -l42 -L$(MLX_DIR)/build -lmlx42 -lglfw -framework OpenGL -framework Cocoa -IOKit -framework CoreVideo

# Source and Object files
SRC          = $(SRC_DIR)/color.c \
			   $(SRC_DIR)/fdf.c \
			   $(SRC_DIR)/gen_utils.c \
			   $(SRC_DIR)/map.c \
			   $(SRC_DIR)/rotate.c \
			   $(SRC_DIR)/draw.c \
			   $(SRC_DIR)/fdf_utils.c \
			   $(SRC_DIR)/hooks.c \
			   $(SRC_DIR)/parse.c
OBJ          = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Default target: build
all: | $(OBJ_DIR) $(LIB42_DIR)/lib42.a $(MLX_DIR)/build/libmlx42.a $(NAME)

# Debug target
debug: | $(OBJ_DIR) $(LIB42_DIR)/lib42.a $(MLX_DIR)/build/libmlx42.a $(NAME_DEBUG)

# Ensure the object directory exists
$(OBJ_DIR):
	@echo "$(YELLOW)Creating directory: $(OBJ_DIR)$(RESET_COLOR)"
	@mkdir -p $(OBJ_DIR)

# Build lib42 if not present
$(LIB42_DIR)/lib42.a:
	@echo "$(YELLOW)Downloading and building lib42...$(RESET_COLOR)"
	@mkdir -p $(LIB42_DIR)
	@git clone https://github.com/F-vdHaar/42_lib.git $(LIB42_DIR) || echo "$(RED)Failed to clone lib42 repository.$(RESET_COLOR)"
	@$(MAKE) -C $(LIB42_DIR)

# Build MLX if not present
$(MLX_DIR)/build/libmlx42.a:
	@echo "$(YELLOW)Downloading and building MLX42...$(RESET_COLOR)"
	@if [ ! -d "$(MLX_DIR)" ] || [ -z "$$(ls -A $(MLX_DIR))" ]; then \
		git clone https://github.com/codam-coding-college/MLX42.git $(MLX_DIR) || \
		{ echo "$(RED)Failed to clone MLX42 repository.$(RESET_COLOR)"; exit 1; }; \
	fi
	@if ! command -v cmake &> /dev/null; then \
		echo "$(YELLOW)CMake is not installed. Installing...$(RESET_COLOR)"; \
		brew install cmake || { echo "$(RED)Failed to install CMake.$(RESET_COLOR)"; exit 1; }; \
	fi
	@if ! ls /opt/homebrew/lib/libglfw* 1> /dev/null 2>&1 && ! ls /usr/local/lib/libglfw* 1> /dev/null 2>&1; then \
		echo "$(YELLOW)GLFW is not installed. Installing...$(RESET_COLOR)"; \
		brew install glfw || { echo "$(RED)Failed to install GLFW.$(RESET_COLOR)"; exit 1; }; \
	fi
	@mkdir -p $(MLX_DIR)/build
	@cd $(MLX_DIR)/build && cmake .. && make -j
	@echo "$(GREEN)MLX42 built successfully.$(RESET_COLOR)"


# Compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR) $(LIB42_DIR)/lib42.a $(MLX_DIR)/build/libmlx42.a
	@echo "$(GREEN)Compiling fdf object: $<$(RESET_COLOR)"
	@$(CC) $(FLAGS) -c $< -o $@

# Link the final executable
$(NAME): $(OBJ) $(LIB42_DIR)/lib42.a $(MLX_DIR)/build/libmlx42.a
	@echo "$(BLUE)Linking $(NAME)$(RESET_COLOR)"
	@$(CC) $(FLAGS) $(OBJ) -o $(NAME) $(LIBRARIES)
	@echo "$(GREEN)$(NAME) built successfully.$(RESET_COLOR)"

# Link the final debug executable
$(NAME_DEBUG): $(OBJ) $(LIB42_DIR)/lib42.a $(MLX_DIR)/build/libmlx42.a
	@echo "$(BLUE)Linking $(NAME_DEBUG)$(RESET_COLOR)"
	@$(CC) $(DEBUG_FLAGS) $(OBJ) -o $(NAME_DEBUG) $(LIBRARIES)
	@echo "$(GREEN)$(NAME_DEBUG) built successfully.$(RESET_COLOR)"

# Clean object files
clean:
	@echo "$(YELLOW)Cleaning object files...$(RESET_COLOR)"
	@$(RM) $(OBJ)
	@$(RM) -rf $(OBJ_DIR)
	@echo "$(GREEN)Object files cleaned.$(RESET_COLOR)"

# Clean everything (executables and libraries)
fclean: clean
	@echo "$(RED)Cleaning executables and libraries...$(RESET_COLOR)"
	@$(RM) $(NAME) $(NAME_DEBUG)
	@$(MAKE) fclean -C $(LIB42_DIR)
	@if [ -d "$(MLX_DIR)" ]; then \
		$(MAKE) clean -C $(MLX_DIR); \
		rm -rf $(MLX_DIR)/build; \
	fi
	@echo "$(GREEN)All files cleaned.$(RESET_COLOR)"


# Rebuild everything
re: fclean all

# Rebuild debug everything
redebug: fclean debug

# Norm checking
norm:
	@echo "$(BLUE)Running Norminette...$(RESET_COLOR)"
	@norminette $(SRC_DIR) $(INCLUDE_DIR) | grep -v 'OK!' || true
	@echo "$(GREEN)Norminette check complete.$(RESET_COLOR)"

.PHONY: all debug clean fclean re redebug norm