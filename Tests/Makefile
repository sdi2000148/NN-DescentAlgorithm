CC = gcc
CFLAGS = -Wall -Wextra -pthread
INCLUDE_DIR = ../Include
TESTS_DIR = .
CURRENT_DIR = .

LIST_OBJS = ../List/list.o
AVL_OBJS = ../List/list.o ../Avl/avl.o
HEAP_OBJS = ../List/list.o ../Heap/heap.o ../Avl/avl.o
SERVICES_OBJS = ../List/list.o ../Heap/heap.o ../Avl/avl.o ../Services/services.o
RECALL_OBJS = ../Heap/heap.o ../Avl/avl.o ../Evaluation/recall.o ../Dataset/dataset.o ../Services/services.o ../Algorithms/brute_force.o ../Metrics/metrics.o ../List/list.o
ALGORITHMS_OBJS = ../Avl/avl.o ../Services/services.o ../ReadData/read.o ../Dataset/dataset.o ../Heap/heap.o ../Algorithms/brute_force.o ../List/list.o ../Metrics/metrics.o ../Algorithms/search.o ../Algorithms/nn_descent.o ../Algorithms/nng_initialization.o ../Evaluation/recall.o
DATASET_OBJS = ../Dataset/dataset.o
METRIC_OBJS = ../Metrics/metrics.o


TEST_SRCS = $(wildcard $(TESTS_DIR)/*.c)
TEST_TARGETS = $(TEST_SRCS:.c=)

.PHONY: all clean run valgrind

all: outer_make inner_make

outer_make: 
	$(MAKE) -C ..

inner_make: $(TEST_TARGETS)

%: %.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) $< -o $@

list_tests: list_tests.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) $< $(LIST_OBJS) -o $@

avl_tests: avl_tests.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) $< $(AVL_OBJS) -o $@

heap_tests: heap_tests.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) $< $(HEAP_OBJS) -o $@

services_tests: services_tests.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) $< $(SERVICES_OBJS) -o $@

recall_tests: recall_tests.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) $< $(RECALL_OBJS) -o $@ -lm

algorithms_tests: algorithms_tests.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) $< $(ALGORITHMS_OBJS) -o $@ -lm

dataset_tests: dataset_tests.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) $< $(DATASET_OBJS) -o $@
	
metrics_tests: metrics_tests.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) $< $(METRIC_OBJS) -o $@ -lm

clean:
	$(MAKE) -C .. clean
	rm -rf $(TEST_TARGETS) *.o

run: outer_make $(TEST_TARGETS)
	./list_tests
	./avl_tests
	./heap_tests
	./services_tests
	./recall_tests
	./algorithms_tests
	./dataset_tests
	./metrics_tests

valgrind: outer_make $(TEST_TARGETS)
	valgrind --leak-check=full ./list_tests
	valgrind --leak-check=full ./avl_tests
	valgrind --leak-check=full ./heap_tests
	valgrind --leak-check=full ./services_tests
	valgrind --leak-check=full ./recall_tests
	valgrind --leak-check=full ./algorithms_tests
	valgrind --leak-check=full ./dataset_tests
	valgrind --leak-check=full ./metrics_tests
