CC = gcc
CFLAGS = -Wall -Wextra -pthread
SRC_DIR = .
INCLUDE_DIR = Include

DIRS_TO_INCLUDE := $(filter-out $(INCLUDE_DIR), $(wildcard */))

SRCS = $(wildcard $(SRC_DIR)/*.c) $(foreach dir, $(DIRS_TO_INCLUDE), $(wildcard $(dir)*.c))
OBJS = $(SRCS:.c=.o)
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