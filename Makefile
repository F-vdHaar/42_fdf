# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fvon-der <fvon-der@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/01 22:19:53 by fvon-der          #+#    #+#              #
#    Updated: 2025/03/09 22:50:45 by fvon-der         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Hardcoded version selection (either 1 or 2)
VERSION = 1  # Change this to 2 to build the v2 version

# Colors
RESET_COLOR = \033[0m
YELLOW      = \033[1;33m
BLUE        = \033[1;34m
GREEN       = \033[1;32m
RED         = \033[1;31m

# Project names
NAME        = fdf
NAME_DEBUG  = fdf_debug

# Directories
OBJ_DIR_V1     = obj/v1
SRC_DIR_V1     = src/v1
OBJ_DIR_V2     = obj/v2
SRC_DIR_V2     = src/v2
LIB42_DIR   = lib/lib42
MLX_DIR     = lib/mlx
INCLUDE_DIR = include

# Include paths for libraries and headers
INCLUDE     = -I$(INCLUDE_DIR)/v$(VERSION) -I$(LIB42_DIR)/libft/include -I$(LIB42_DIR)/ft_printf/include -I$(LIB42_DIR)/gnl/include -I$(MLX_DIR)/include/MLX42

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

# List of source files for version v1
SRC_V1 = $(SRC_DIR_V1)/fdf.c \
		 $(SRC_DIR_V1)/camera.c \
		 $(SRC_DIR_V1)/map_utils.c \
		 $(SRC_DIR_V1)/color_utils.c \
		 $(SRC_DIR_V1)/fdf_test_utils.c \
		 $(SRC_DIR_V1)/projection.c \
		 $(SRC_DIR_V1)/debug_utils.c \
		 $(SRC_DIR_V1)/fdf_utils.c \
		 $(SRC_DIR_V1)/renderer.c \
		 $(SRC_DIR_V1)/draw.c \
		 $(SRC_DIR_V1)/key_handler.c \
		 $(SRC_DIR_V1)/rotation.c \
		 $(SRC_DIR_V1)/event_handler.c \
		 $(SRC_DIR_V1)/line.c \
		 $(SRC_DIR_V1)/transformation.c \
		 $(SRC_DIR_V1)/events.c \
		 $(SRC_DIR_V1)/map.c
		 
# List of source files for version v2
SRC_V2 = $(SRC_DIR_V2)/color.c \
		 $(SRC_DIR_V2)/fdf.c \
		 $(SRC_DIR_V2)/gen_utils.c \
		 $(SRC_DIR_V2)/map.c \
		 $(SRC_DIR_V2)/rotate.c \
		 $(SRC_DIR_V2)/draw.c \
		 $(SRC_DIR_V2)/fdf_utils.c \
		 $(SRC_DIR_V2)/hooks.c \
		 $(SRC_DIR_V2)/parse.c
		 
SRC = $(SRC_V1)
SRC_2 = $(SRC_V2)
SRC := $(if $(findstring 2,$(VERSION)),$(SRC_V2),$(SRC_V1))

# Debug information to check the value of SRC
$(info VERSION: $(VERSION))
$(info SRC: $(SRC))

# Define the object files using pattern substitution
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)_v$(VERSION)/%.o)

# Debug information: Check the value of SRC
$(info SRC: $(SRC))

# Default target: build
all: | $(OBJ_DIR) $(LIB42_DIR)/lib42.a $(MLX_DIR)/build/libmlx42.a $(NAME)

# Debug target
debug: | $(OBJ_DIR) $(LIB42_DIR)/lib42.a $(MLX_DIR)/build/libmlx42.a $(NAME_DEBUG)

# Ensure the object directory exists
$(OBJ_DIR_V1) $(OBJ_DIR_V2):
	@echo "$(YELLOW)Creating directory: $(OBJ_DIR)$(RESET_COLOR)"
	@mkdir -p $(OBJ_DIR_V1) $(OBJ_DIR_V2)

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
$(OBJ_DIR_V1)/%.o: $(SRC_DIR_V1)/%.c | $(OBJ_DIR_V1) $(LIB42_DIR)/lib42.a $(MLX_DIR)/build/libmlx42.a
	@echo "$(GREEN)Compiling fdf object: $<$(RESET_COLOR)"
	@$(CC) $(FLAGS) -c $< -o $@

$(OBJ_DIR_V2)/%.o: $(SRC_DIR_V2)/%.c | $(OBJ_DIR_V2) $(LIB42_DIR)/lib42.a $(MLX_DIR)/build/libmlx42.a
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
	@$(RM) -rf $(OBJ_DIR_V1) $(OBJ_DIR_V2)
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
	@norminette $(SRC_DIR_V1) $(SRC_DIR_V2) $(INCLUDE_DIR) | grep -v 'OK!' || true
	@echo "$(GREEN)Norminette check complete.$(RESET_COLOR)"

.PHONY: all debug clean fclean re redebug norm
