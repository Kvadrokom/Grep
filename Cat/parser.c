#include "s21_cat.h"

void cat_parser(int c, char** v, cat_s* t) {
  for (int i = 1; i < c; i++) {
    int ct = 1;
    if (v[i][0] != '-')
      break;
    else if (strstr(v[i], "--number-nonblank") != NULL)
      t->b = 1;
    else if (strstr(v[i], "--number") != NULL)
      t->n = 1;
    else if (strstr(v[i], "--squeeze-blank") != NULL)
      t->s = 1;
    else if (v[i][0] == '-') {
      while (v[i]) {
        if (v[i][ct] == 'b')
          t->b = 1;
        else if (v[i][ct] == 'E')
          t->e = 1;
        else if (v[i][ct] == 'e') {
          t->e = 1;
          t->v = 1;
        } else if (v[i][ct] == 'n')
          t->n = 1;
        else if (v[i][ct] == 's')
          t->s = 1;
        else if (v[i][ct] == 't') {
          t->t = 1;
          t->v = 1;
        } else if (v[i][ct] == 'v')
          t->v = 1;
        else if (v[i][ct] == 'T')
          t->t = 1;
        else if (v[i][ct] == '\0')
          break;
        ct++;
      }
    }
  }
  if (t->b == 1) t->n = 0;
  filename(c, v, t);
}

void filename(int c, char** v, cat_s* t) {
  int ct = 0;
  for (int i = 1; i < c; i++) {
    if (v[i][0] != '-') ct++;
  }
  t->fncount = ct;

  t->fn = (char**)malloc(ct * sizeof(char*));
  ct = 0;
  for (int i = 1; i < c; i++) {
    if (v[i][0] != '-') {
      int str = strlen(v[i]);
      t->fn[ct] = (char*)malloc(str * sizeof(char) + 1);
      t->fn[ct][str] = '\0';
      for (int j = 0; j < str; j++) {
        t->fn[ct][j] = v[i][j];
      }
      ct++;
    }
  }
}
