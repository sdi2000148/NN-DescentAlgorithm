CC = gcc
CFLAGS = -Wall -Wextra -pthread
INCLUDE_DIR = ../Include
TESTS_DIR = .

TEST_SRCS = $(wildcard $(TESTS_DIR)/*.c)
TEST_TARGETS = $(TEST_SRCS:.c=)

.PHONY: all clean run valgrind

all: $(TEST_TARGETS)

%: %.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) $< -o $@

clean:
	rm -rf $(TEST_TARGETS)

run: $(TEST_TARGETS)
	./$^

valgrind: $(TEST_TARGETS)
	valgrind --leak-check=full ./$^ $(ARGS)