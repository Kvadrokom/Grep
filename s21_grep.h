#ifndef S21_GREP_H_
#define S21_GREP_H_

#include <ctype.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M 1

typedef struct grep {
  int n;
  int e;
  int l;
  int v;
  int c;
  int i;
  int s;
  int h;
  int o;
  int f;
} s21_grep;

int max(char* v);
void parser(int c, char** v, s21_grep* t);
void reader(int c, int i, char** v, char* str, s21_grep t);
void tp(int c, char** v, s21_grep* t);
void ifl(int i, int c, char* str, char** v, s21_grep t);
void ifle(int j, int c, char* str, char** v, s21_grep t);
void ifv(int i, int c, char* str, char** v, s21_grep t);
void ifc(int i, int c, char* str, char** v, s21_grep t);
void ifce(int j, int c, char* str, char** v, s21_grep t);
void ife(int j, int c, char* str, char** v, s21_grep t);
void ifo(int fnc, int ct, char* s, char* str, char* v, s21_grep t);
int FlagF(char* s, char* str, s21_grep t);
int FlagFe(int c, int cflags, char* s, char** v,
        regex_t* reg, regmatch_t* chr);
void FR(int* status, int c, int cflags, char* s, char** v,
        regex_t* reg, regmatch_t* chr);
int fnct(int j, int c, char** v);
char* lower(char* a);
char* ft_substr(const char* str, unsigned start, unsigned end);

#endif  // S21_GREP_H_
