#include "s21_cat.h"

void cat_reader(cat_s t) {
  FILE* f;
  char* s;
  for (int i = 0; i < t.fncount; i++) {
    f = fopen(t.fn[i], "r");
    if (f == NULL) {
      // printf("cat: %s: No such file or directory\n", t.fn[i]);
    } else {
      int ct = 0;
      int MS = 0;
      int mx = max(t.fn[i]) + 2;
      s = (char*)malloc(mx * sizeof(char));
      while (fgets(s, mx, f)) {
        mzstr(s, mx);
        if (strlen(s) == 1 && strstr(s, "\n") != NULL && t.s == 1)
          MS++;
        else
          MS = 0;
        if (t.b == 1) {
          if (strlen(s) == 1) {
            if (strstr(s, "\n") == NULL) ct++;
          } else
            ct++;
        } else if (MS <= 1)
          ct++;
        Flags(ct, MS, s, t);
      }
      free(s);
    }
    if (f != NULL) fclose(f);
  }
}

void Flags(int ct, int MS, char* s, cat_s t) {
  int lenstr = strlen(s);
  int count = 0;
  int b = 0;
  while (count < lenstr) {
    if (lenstr == 1 && strstr(s, "\n") != NULL && t.b == 1) b = 1;
    if ((t.n == 1 || t.b == 1) && count == 0 && b == 0) {
      if (MS <= 1 && ct < 10)
        printf("     %d\t", ct);
      else if (MS <= 1 && ct < 100)
        printf("    %d\t", ct);
      else if (MS <= 1 && ct < 1000)
        printf("   %d\t", ct);
      else if (MS <= 1 && ct < 10000)
        printf("  %d\t", ct);
      else if (MS <= 1 && ct < 100000)
        printf(" %d\t", ct);
      else if (MS <= 1 && ct < 100000)
        printf("%d\t", ct);
    }
    if (MS <= 1) {
      if (t.v == 1) {
        if (s[count] == 9 || s[count] == 10 ||
            (s[count] > 31 && s[count] <= 126)) {
          if (t.t == 1 && s[count] == '\t')
            printf("^I");
          else if (t.e == 1 && s[count] == '\n') {
            printf("$");
            printf("%c", s[count]);
          } else
            printf("%c", s[count]);
        } else if (s[count] == 127)
          printf("^?");
        else if ((s[count] > -1 && s[count] < 9) ||
                 (s[count] >= 11 && s[count] <= 31))
          printf("^%c", s[count] + 64);
      } else if (t.t == 1 && s[count] == '\t')
        printf("^I");
      else if (t.e == 1 && s[count] == '\n') {
        printf("$");
        putchar(s[count]);
      } else
        putchar(s[count]);
    }
    count++;
  }
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
    if (f != NULL) fclose(f);
    return (max2 + 2);
  } else {
    return -3;
  }
}

char* mzstr(char* str, int len) {
  int ct = strlen(str);
  if (ct != len) {
    while (ct < len) {
      str[ct] = '\0';
      ct++;
    }
  }
  return str;
}
