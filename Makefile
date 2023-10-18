CC = gcc
CFLAGS = -Wall -Wextra -pthread
SRC_DIR = .
INCLUDE_DIR = Include
TESTS_DIR = Tests

EXCLUDED_DIRS = $(INCLUDE_DIR) $(TESTS_DIR)

DIRS_TO_INCLUDE := $(filter-out $(EXCLUDED_DIRS), $(wildcard */))

SRCS = $(wildcard $(SRC_DIR)/*.c) $(foreach dir, $(DIRS_TO_INCLUDE), $(wildcard $(dir)*.c))
OBJS = $(filter-out $(TESTS_DIR)/%.o, $(SRCS:.c=.o))
DEPS = $(wildcard $(INCLUDE_DIR)/*.h)

TARGET = main

.PHONY: all clean run valgrind

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -lm

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@ 

clean:
	rm -rf $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

valgrind: $(TARGET)
	valgrind --leak-check=full ./$(TARGET) $(ARGS)