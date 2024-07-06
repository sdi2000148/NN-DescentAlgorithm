#include "acutest.h"

#include "avl.h"


void test_initialize(void) {
  Avl avl;

  avl_initialize( & avl);

  TEST_CHECK(avl_search(avl, 0) == 0);

  avl_free(avl);
}

void test_insert(void) {
  int N = 100;
  Avl avl;

  avl_initialize( & avl);

  for (int i = 0; i <= N / 2; i++)
    TEST_CHECK(avl_insert(avl, i) == 1);

  for (int i = N - 1; i > N / 2; i--)
    TEST_CHECK(avl_insert(avl, i) == 1);

  for (int i = 0; i < N; i++)
    TEST_CHECK(avl_insert(avl, i) == 0);

  avl_free(avl);
}

void test_remove(void) {
  int N = 100;
  Avl avl;

  avl_initialize( & avl);

  for (int i = 0; i < N; i++)
    TEST_CHECK(avl_insert(avl, i) == 1);

  for (int i = 0; i <= N / 2; i++) {
    TEST_CHECK(avl_remove(avl, i) == 1);
    TEST_CHECK(avl_remove(avl, i) == 0);
  }

  for (int i = N - 1; i > N / 2; i--) {
    TEST_CHECK(avl_remove(avl, i) == 1);
    TEST_CHECK(avl_remove(avl, i) == 0);
  }

  avl_free(avl);
}

void test_search(void) {
  int N = 100;
  Avl avl;

  avl_initialize( & avl);

  for (int i = 0; i < N; i++) {
    TEST_CHECK(avl_insert(avl, i) == 1);
    TEST_CHECK(avl_search(avl, i) == 1);
  }

  for (int i = 0; i < N; i++) {
    TEST_CHECK(avl_remove(avl, i) == 1);
    TEST_CHECK(avl_search(avl, i) == 0);
  }

  avl_free(avl);
}

TEST_LIST = {
  {
    "avl_initialize",
    test_initialize
  },
  {
    "avl_insert",
    test_insert
  },
  {
    "avl_remove",
    test_remove
  },
  {
    "avl_search",
    test_search
  },
  {
    NULL,
    NULL
  }
};