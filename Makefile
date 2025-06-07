SRC_DIR := src
OBJ_DIR := obj
INCLUDE_DIR := INCLUDE

CC := cc
CFLAGS := -g -O1 -O2  -Wall -Werror -Wextra  -I$(INCLUDE_DIR) #-fsanitize=thread -pthread #-fsanitize=address

TARGET := philo

SRC_FILE := $(SRC_DIR)/*.c

all:	$(TARGET)

$(TARGET): $(SRC_FILE)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(TARGET)

fclean: clean
	rm -rf $(OBJ_DIR)/*.o

re: fclean all
