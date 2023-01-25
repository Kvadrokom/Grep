#include "s21_cat.h"

void init(cat_s* t) {
  t->fncount = 0;
  t->v = 0;
  t->e = 0;
  t->n = 0;
  t->b = 0;
  t->s = 0;
  t->v = 0;
}

int main(int argc, char** argv) {
  cat_s t;
  init(&t);

  if (argc <= 1) return 0;
  cat_parser(argc, argv, &t);
  cat_reader(t);
  for (int i = 0; i < t.fncount; i++) {
    free(t.fn[i]);
  }
  free(t.fn);

  return 0;
}
