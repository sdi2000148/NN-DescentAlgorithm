CC = gcc
CFLAGS = -Wall -Wextra -pthread
INCLUDE_DIR = ../Include
TESTS_DIR = .
CURRENT_DIR = .

LIST_OBJS = ../List/list.o
HEAP_OBJS = ../List/list.o ../Heap/heap.o
SERVICES_OBJS = ../List/list.o ../Heap/heap.o ../Services/services.o
RECALL_OBJS = ../Heap/heap.o ../Evaluation/recall.o ../Dataset/dataset.o ../Services/services.o ../Algorithms/brute_force.o ../Metrics/metrics.o ../List/list.o
ALGORITHMS_OBJS = ../Avl/avl.o ../Services/services.o ../Dataset/dataset.o ../Heap/heap.o ../Algorithms/brute_force.o ../List/list.o ../Metrics/metrics.o ../Algorithms/nn_descent.o ../Algorithms/nng_initialization.o ../Evaluation/recall.o
DATASET_OBJS = ../Dataset/dataset.o
METRIC_OBJS = ../Metrics/metrics.o


TEST_SRCS = $(wildcard $(TESTS_DIR)/*.c)
TEST_TARGETS = $(TEST_SRCS:.c=)

.PHONY: all clean run valgrind

all: $(TEST_TARGETS)

%: %.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) $< -o $@

list_tests: list_tests.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) $< $(LIST_OBJS) -o $@

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
	rm -rf $(TEST_TARGETS) *.o

run: list_tests heap_tests services_tests recall_tests algorithms_tests dataset_tests
	./list_tests
	./heap_tests
	./services_tests
	./recall_tests
	./algorithms_tests
	./dataset_tests
	./metrics_tests

valgrind: $(TEST_TARGETS)
	valgrind --leak-check=full ./$^ $(ARGS)
