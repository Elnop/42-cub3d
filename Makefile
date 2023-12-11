NAME = cub3d

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

FILES = main init image_utils destroy draw_minimap check_map hooks utils render

SRCS_DIR = srcs
SRCS = $(addprefix $(SRCS_DIR)/, $(addsuffix .c, $(FILES)))

OBJS_DIR = .obj
OBJS = ${patsubst ${SRCS_DIR}/%.c, ${OBJS_DIR}/%.o, ${SRCS}}

LIBS_FOLDER = libs

LIBLP_DIR = liblp_c
LIBLP = $(LIBS_FOLDER)/$(LIBLP_DIR)/liblp_c.a

MLX_DIR = minilibx-linux
MLX = ./$(LIBS_FOLDER)/$(MLX_DIR)/libmlx_Linux.a

LIBS = $(MLX) $(LIBLP)

INCLUDES_DIR = includes
INCLUDES_FILES = cub3d.h
INCLUDES = $(addprefix $(INCLUDES_DIR)/, $(INCLUDES_FILES))

all: $(NAME)

$(NAME): $(LIBS) $(OBJS)
	$(CC) $(OBJS) $(LIBS) -lm -lXext -lX11 -o $@

${OBJS_DIR}/%.o: ${SRCS_DIR}/%.c $(INCLUDES)
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -o $@ -c $<

clean: cleanlibs
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: clean all

$(LIBS):
	make -C $(LIBS_FOLDER)/$(MLX_DIR)
	make -C $(LIBS_FOLDER)/$(LIBLP_DIR)

cleanlibs:
	make fclean -C $(LIBS_FOLDER)/$(LIBLP_DIR)
	make clean -C $(LIBS_FOLDER)/$(MLX_DIR)

.PHONY: all clean fclean re makelib cleanlib