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
  tp(c, v, t);
}

void tp(int c, char** v, s21_grep* t) {
  int ct, ctstr;
  char* a;
  if (t->e == 1) {
    for (int j = 1; j < c; j++) {
      if (strstr(v[j], "-e") != NULL) {
        if (strlen(v[j]) == 2) {
          a = v[j + 1];
          reader(c, j, v, a, *t);
          break;
        } else {
          for (int i = 1; i < c; i++) {
            ct = 0;
            if (strstr(v[i], "-e") != 0) {
              ctstr = strlen(v[i]);
              a = (char*)malloc(sizeof(char) * ctstr);
              while (ct < ctstr) {
                if (v[i][ct] != '\0') {
                  a[ct] = v[i][ct + 2];
                  ct++;
                }
              }
              reader(c, i, v, a, *t);
              free(a);
            }
          }
        }
      }
    }
  } else {
    for (int i = 1; i < c; i++) {
      if (v[i][0] != '-') {
        a = v[i];
        reader(c, i, v, a, *t);
        break;
      }
    }
  }
}
