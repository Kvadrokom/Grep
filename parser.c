#include "s21_grep.h"

void parser(int c, char** v, s21_grep* t) {
  for (int i = 1; i < c; i++) {
    int ct = 1;
    if (strstr(v[i], "-e") != NULL) {
      t->e = 1;
      if (strcmp(v[i], "-e") != 0) {
        if (c - i < 2) {
          printf("grep: option requires an argument -- e\n");
          return;
        }
      } else {
        if (c - i < 1) {
          printf("grep: option requires an argument -- e\n");
          return;
        }
      }
    } else if (v[i][0] == '-') {
      while (v[i]) {
        if (v[i][ct] == 'i')
          t->i = 1;
        else if (v[i][ct] == 'e') {
          t->e = 1;
          break;
        } else if (v[i][ct] == 'n')
          t->n = 1;
        else if (v[i][ct] == 'c')
          t->c = 1;
        else if (v[i][ct] == 'l')
          t->l = 1;
        else if (v[i][ct] == 'v')
          t->v = 1;
        else if (v[i][ct] == 's')
          t->s = 1;
        else if (v[i][ct] == 'h')
          t->h = 1;
        else if (v[i][ct] == 'o')
          t->o = 1;
        else if (v[i][ct] == 'f') {
          t->f = 1;
          break;
        } else if (v[i][ct] == '\0')
          break;
        ct++;
      }
    }
  }
  tp(c, v, *t);
}

void tp(int c, char** v, s21_grep t) {
  char* a;
  if (t.e == 1) {
    for (int i = 1; i < c; i++) {
      if ((a = strstr(v[i], "e")) != NULL && v[i][0] == '-') {
        if (strlen(a) > 1) {
          a = a + 1;
        } else {
          if (c - i >= 1)
            a = v[i + 1];
          else
            break;
        }
        reader(c, i, v, a, t);
        break;
      }
    }
  } else {
    for (int i = 1; i < c; i++) {
      if (v[i][0] != '-') {
        a = v[i];
        reader(c, i, v, a, t);
        break;
      }
    }
  }
}
