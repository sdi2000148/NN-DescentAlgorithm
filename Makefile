CC = gcc
CFLAGS = -g -Wall -Wextra -pthread
SRC_DIR = .
INCLUDE_DIR = Include
TESTS_DIR = Tests

EXCLUDED_DIRS = $(INCLUDE_DIR) $(TESTS_DIR)

DIRS_TO_INCLUDE := $(filter-out $(EXCLUDED_DIRS), $(wildcard */))

SRCS_NN = nn.c $(foreach dir, $(DIRS_TO_INCLUDE), $(wildcard $(dir)*.c))
SRCS_BRUTE = brute.c $(foreach dir, $(DIRS_TO_INCLUDE), $(wildcard $(dir)*.c))
OBJS_NN = $(filter-out $(TESTS_DIR)/%.o, $(SRCS_NN:.c=.o))
OBJS_BRUTE = $(filter-out $(TESTS_DIR)/%.o, $(SRCS_BRUTE:.c=.o))
DEPS = $(wildcard $(INCLUDE_DIR)/*.h)

TARGET_NN = nn
TARGET_BRUTE = brute

ARGS_NN = Datasets/00002000-1.bin l2 100 0.1 0.001 solution.txt output.csv
ARGS_BRUTE = Datasets/00002000-1.bin l2 100 solution.txt output.csv

.PHONY: all clean run-nn run-brute valgrind-nn valgrind-brute

all: $(TARGET_NN) $(TARGET_BRUTE)

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@ 

$(TARGET_NN): $(OBJS_NN)
	$(CC) $(CFLAGS) $^ -o $@ -lm

$(TARGET_BRUTE): $(OBJS_BRUTE)
	$(CC) $(CFLAGS) $^ -o $@ -lm

clean:
	rm -rf $(OBJS_NN) $(TARGET_NN) $(OBJS_BRUTE) $(TARGET_BRUTE)

clean-nn:
	rm -rf $(OBJS_NN) $(TARGET_NN)

clean-brute:
	rm -rf $(OBJS_BRUTE) $(TARGET_BRUTE)

run-nn: $(TARGET_NN)
	./$(TARGET_NN) $(ARGS_NN)

run-brute: $(TARGET_BRUTE)
	./$(TARGET_BRUTE) $(ARGS_BRUTE)

valgrind-nn: $(TARGET_NN)
	valgrind --leak-check=full ./$(TARGET_NN) $(ARGS_NN)

valgrind-brute: $(TARGET_BRUTE)
	valgrind --leak-check=full ./$(TARGET_BRUTE) $(ARGS_BRUTE)
