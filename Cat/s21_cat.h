#ifndef S21_CAT_H_
#define S21_CAT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cat {
  char** fn;
  int fncount;
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
} cat_s;

void cat_parser(int c, char** v, cat_s* t);
void filename(int c, char** v, cat_s* t);
void cat_reader(cat_s t);
void Flags(int ct, int MS, char* s, cat_s t);
int max(char* v);
char* mzstr(char* str, int len);

#endif
