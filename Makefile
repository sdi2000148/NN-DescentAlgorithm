CC = gcc
CFLAGS = -Wall -Wextra -pthread
SRC_DIR = .
DATASET_DIR = Dataset
HEAP_DIR = Heap
INCLUDE_DIR = Include

SRCS = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(DATASET_DIR)/*.c) $(wildcard $(HEAP_DIR)/*.c)
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