#include "s21_grep.h"

void FR(int* status, int c, int cflags, char* pa, char* s, char** v,
        regex_t* reg) {
  for (int i = 1; i < c; i++) {
    if (strstr(v[i], "-e") != NULL) {
      if (strlen(v[i]) == 2) {
        pa = v[i + 1];
        regcomp(reg, pa, cflags);
        *status = regexec(reg, s, 0, NULL, 0);
        if (status == 0) {
          break;
        }
      } else {
        pa = strstr(v[i], "-e") + 2;
        regcomp(reg, pa, cflags);
        *status = regexec(reg, s, 0, NULL, 0);
        if (status == 0) {
          break;
        }
      }
    } else if (strstr(v[i], "e") != NULL && v[i][0] == '-') {
      pa = v[i + 1];
      regcomp(reg, pa, cflags);
      *status = regexec(reg, s, 0, NULL, 0);
      if (status == 0) {
        break;
      }
    }
    regfree(reg);
  }
  return;
}

int fnct(int j, int c, char** v) {
  int ct = 0;
  for (int i = 1; i < c; i++) {
    if (strstr(v[i], "-e") != NULL) {
      if (strlen(v[i]) == 2) {
        if (c - i < 3) {
          break;
        } else {
          i += 2;
        }
      }
    } else if (v[i][0] != '-' && strcmp(v[i], v[j]) != 0)
      ct++;
  }
  return ct;
}

int max(char* v) {
  FILE* f;
  int max1 = 0;
  int max2 = 0;
  int ct = 0;
  int r = 0;

  f = fopen(v, "r");
  if (f != NULL) {
    while ((r = getc(f)) != EOF) {
      if (r != '\n') {
        max1++;
      } else {
        if (max1 > max2) max2 = max1;
        max1 = 0;
        ct++;
      }
    }
    if (ct > 0) {
      return max2;
    } else {
      return max1;
    }
  } else {
    return -3;
  }
  fclose(f);
}

char* lower(char* a) {
  char* arr = a;
  int n = strlen(a);

  for (int i = 0; i < n; i++) {
    arr[i] = tolower(a[i]);
  }

  return arr;
}
