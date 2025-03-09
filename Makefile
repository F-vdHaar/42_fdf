NAME = fdf

SRC_VERSION ?= v2

SRC_DIR = src/$(SRC_VERSION)
OBJ_DIR = obj/$(SRC_VERSION)
LIB42_DIR = lib/lib42
MLX_DIR = lib/MLX42
BUILD_DIR = build
INC_DIR = include/$(SRC_VERSION)  # Dynamically determined include directory

# Find all source files in the directory
SRC = $(wildcard $(SRC_DIR)/*.c)

# Create a list of object files corresponding to the source files
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

CC = cc -g
CFLAGS = -I$(INC_DIR) -I$(MLX_DIR)/include -I$(LIB42_DIR)/libft/include -I$(LIB42_DIR)/ft_printf/include -I$(LIB42_DIR)/gnl/include
LDFLAGS = -L$(LIB42_DIR) -l42 -L$(MLX_DIR)/build -lmlx42 -ldl -lglfw -pthread -lm -g

# Default target
all: $(NAME)

# Build the main target
$(NAME): $(OBJ) | $(LIB42_DIR)/lib42.a $(MLX_DIR)/build/libmlx42.a
	@$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $(NAME)

# Rule to compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

# Ensure the object directory exists
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Build lib42 static library if not present
$(LIB42_DIR)/lib42.a: | $(LIB42_DIR)
	@$(MAKE) -C $(LIB42_DIR)

# Clone and build lib42 if not already present
$(LIB42_DIR):
	@mkdir -p $(dir $(LIB42_DIR))  # Ensure the parent directory exists
	@cd $(dir $(LIB42_DIR)) && git clone --recurse-submodules git@github.com:F-vdHaar/42_lib.git
	@make -C
# Build libmlx42 static library if not present
$(MLX_DIR)/build/libmlx42.a:
	cmake $(MLX_DIR) -B $(MLX_DIR)/build
	make -C $(MLX_DIR)/build -j4

# Clone and build MLX42 if not already present
$(MLX_DIR):
	@mkdir -p $(dir $(MLX_DIR))  # Ensure the parent directory exists
	@cd $(dir $(MLX_DIR)) && git clone https://github.com/codam-coding-college/MLX42.git
	cmake $(MLX_DIR) -B $(MLX_DIR)/build
	make -C $(MLX_DIR)/build -j4

# Clean object files and libraries
clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIB42_DIR) clean
	@rm -rf $(MLX_DIR)/build

# Clean everything
fclean: clean
	@rm -f $(NAME)

# Rebuild from scratch
re: fclean all

# Makefile targets that don't correspond to actual files
.PHONY: all clean fclean re
