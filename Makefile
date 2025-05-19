SRC_DIR := src
OBJ_DIR := obj

CC := cc
CFLAGS := -g -Wall -Werror -Wextra -fsanitize=address

TARGET := philo

SRC_FILE := $(SRC_DIR)/test.c

all:	$(TARGET)

$(TARGET): $(SRC_FILE)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(TARGET)

fclean: clean
	rm -rf $(OBJ_DIR)/*.o

re: fclean all
