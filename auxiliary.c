#include "s21_grep.h"

void FR(int* status, int c, int cflags, char* s, char** v,
        regex_t* reg, regmatch_t* chr, s21_grep t) {
  char* pa;
  FILE* f;
  for (int i = 1; i < c; i++) {
    pa = strstr(v[i], "e");
    if (pa != NULL && v[i][0] == '-') {
      if (strlen(pa) > 1) {
        pa = pa + 1;
      } else {
        if (c - i < 2) {
          break;
        } else
          pa = v[i + 1];
      }
      regcomp(reg, pa, cflags);
      *status = regexec(reg, s, M, chr, 0);
      if (*status == 0)
        break;
    }
  }
  if (*status == 1 && t.f == 1) {
    char* str;
    for (int i = 1; i < c; i++) {
      pa = strstr(v[i], "f");
      if (pa != NULL && v[i][0] == '-') {
        if (strlen(pa) > 1) {
          pa = pa + 1;
        } else {
          if (c - i < 2) {
            break;
          } else
            pa = v[i + 1];
        }
        f = fopen(pa, "r");
        if (f != NULL) {
          str = (char*) malloc(max(pa) * sizeof(char));
          while (fgets(str, max(pa), f)) {
            // printf("str = %s ??? pa = %s\n", str, pa);
            strSHN(str);
            regcomp(reg, str, cflags);
            *status = regexec(reg, s, M, chr, 0);
            if (*status == 0)
            {
              break;
            }
          }
          free(str);
        }
        fclose(f);
      }
    }
  }
  return;
}

int fnct(int j, int c, char** v) {
  int ct = 0;
  for (int i = 1; i < c; i++) {
    while (1) {
      if (strstr(v[i], "-e") != NULL || strstr(v[i], "-f") != NULL) {
        if (strlen(v[i]) == 2) {
          if (c - i < 3)
            return ct;
          else
            i += 2;
        } else {
          break;
        }
      } else {
        break;
      }
    }
    if (v[i][0] != '-' && strcmp(v[i], v[j]) != 0)
      ct++;
  }
  return ct;
}

int max(char* v) {
  FILE* f;
  int max1 = 0;
  int max2 = 0;
  int r = 0;

  f = fopen(v, "r");
  if (f != NULL) {
    while ((r = getc(f)) != EOF) {
      if (r != '\n' && r != '\0') {
        max1++;
      } else {
        if (max1 > max2) max2 = max1;
        max1 = 0;
      }
    }
    if (max1 > max2) max2 = max1;
    fclose(f);
    return (max2 + 2);
  } else {
    fclose(f);
    return -3;
  }
}

char* lower(char* a) {
  char* arr1 = a;
  char* arr2;
  int n = strlen(a);

  arr2 = (char*)malloc(sizeof(char) * n);
  for (int i = 0; i < n; i++) {
    arr2[i] = tolower(arr1[i]);
  }
  arr1 = arr2;

  return arr1;
}

char* ft_substr(const char* str, unsigned start, unsigned end) {
  // printf("str = %s, start = %u, end = %u\n", str, start, end);
  unsigned n = end - start;
  static char stbuf[256];
//   printf("%d --- %d --- %s\n", end, start, str);
  strncpy(stbuf, str + start, n);
  stbuf[n] = 0;
  // printf("Hi, iam here!!!\n");
  return stbuf;
}

char* strSHN(char* s) {
  int n = strlen(s);
  int c = 0;
  while (c < n) {
    if (s[c] == '\n')
      s[c] = '\0';
    c++;
  }
  return s;
}
