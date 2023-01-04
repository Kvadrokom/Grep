#include "s21_grep.h"

void reader(int c, int i, char** v, char* str, s21_grep t) {
  if (t.l == 1)
    ifl(i, c, str, v, t);
  else if (t.c == 1)
    ifc(i, c, str, v, t);
  else if (t.e == 1)
    ife(i, c, str, v, t);
  else
    ifv(i, c, str, v, t);
  return;
}

void ifl(int i, int c, char* str, char** v, s21_grep t) {
  FILE* f;
  int maxstr = 0;

  if (t.e != 1) {
    for (i = i + 1; i < c; i++) {
      int ct = 0;
      if (v[i][0] != '-') {
        f = fopen(v[i], "r");
        maxstr = max(v[i]) + 2;
        if (maxstr != -1) {
          char* s = (char*)malloc(sizeof(char) * maxstr);
          while (fgets(s, maxstr, f)) {
            if (t.v != 1) {
              if (t.i != 1) {
                if (strstr(s, str) != NULL) ct = 1;
              } else {
                if (strcasestr(s, str) != NULL) ct = 1;
              }
            } else {
              if (t.i != 1) {
                if (strstr(s, str) == NULL) ct = 1;
              } else {
                if (strcasestr(s, str) == NULL) ct = 1;
              }
            }
          }
          if (ct == 1) printf("%s\n", v[i]);
          free(s);
        } else {
          if (t.s != 1) printf("grep: %s: No such file or directory\n", v[i]);
        }
        fclose(f);
      }
    }
  } else {
    ifle(i, c, str, v, t);
  }
}

void ifle(int j, int c, char* str, char** v, s21_grep t) {
  FILE* f;
  int ct, status, maxstr, cflags;
  if (t.i == 1) {
    cflags = REG_ICASE;
  } else {
    cflags = REG_EXTENDED;
  }

  for (int i = 1; i < c; i++) {
    while (1) {
      if (strstr(v[i], "-e") != NULL) {
        if (strlen(v[i]) == 2) {
          if (c - i < 3)
            break;
          else
            i += 2;
        } else {
          break;
        }
      } else {
        break;
      }
    }
    ct = 0;
    regex_t reg;
    if (v[i][0] != '-' && strcmp(v[i], v[j]) != 0) {
      f = fopen(v[i], "r");
      if (f != NULL) {
        maxstr = max(v[i]) + 2;
        char* s = (char*)malloc(sizeof(char) * maxstr);
        while (fgets(s, maxstr, f)) {
          FR(&status, c, cflags, str, s, v, &reg);
          if (t.v != 1) {
            if (status == 0) ct = 1;
          } else {
            if (status != 0) ct = 1;
          }
        }
        if (ct == 1) printf("%s\n", v[i]);
        fclose(f);
        free(s);
      } else {
        if (t.s != 1) printf("grep: %s: No such file or directory\n", v[i]);
      }
    }
  }
}

void ifv(int i, int c, char* str, char** v, s21_grep t) {
  FILE* f;
  int maxstr = 0;
  int fc = fnct(i, c, v);

  for (i = i + 1; i < c; i++) {
    int ct = 1;
    if (v[i][0] != '-') {
      maxstr = max(v[i]) + 2;
      char* s = (char*)malloc(sizeof(char) * maxstr);
      if (maxstr == -1) {
        if (t.s != 1) printf("grep: %s: No such file or directory\n", v[i]);
        return;
      }
      f = fopen(v[i], "r");
      if (f != NULL) {
        while (fgets(s, maxstr, f)) {
          if (t.f == 1) {
            FlagF(s, str, t);
          }
          if (t.v != 1) {
            if (t.i != 1) {
              if (strstr(s, str) != NULL) {
                if (t.o != 1) {
                  if (fc > 1 && t.h == 1) {
                    printf("%s:", v[i]);
                  }
                  if (t.n == 1) {
                    printf("%d:", ct);
                  }
                  printf("%s", s);
                } else {
                  ifo(fc, ct, s, str, v[i], t);
                }
              }
            } else {
              if (t.o != 1) {
                if (strcasestr(s, str) != NULL) {
                  if (fc > 1) printf("%s:", v[i]);
                  if (t.n == 1) printf("%d:", ct);
                  printf("%s", s);
                }
              } else {
                ifo(fc, ct, s, str, v[i], t);
              }
            }
          } else {
            if (t.i != 1) {
              if (t.o != 1) {
                if (strstr(s, str) == NULL) {
                  if (fc > 1 && t.h == 1) printf("%s:", v[i]);
                  if (t.n == 1) printf("%d:", ct);
                  printf("%s", s);
                }
              } else {
                ifo(fc, ct, s, str, v[i], t);
              }
            } else {
              if (t.o != 1) {
                if (strcasestr(s, str) == NULL) {
                  if (fc > 1 && t.h == 1) printf("%s:", v[i]);
                  if (t.n == 1) printf("%d:", ct);
                  printf("%s", s);
                }
              } else {
                ifo(fc, ct, s, str, v[i], t);
              }
            }
          }
          if (t.o != 1) {
            if (feof(f) != 0) printf("\n");
          }
          ct++;
        }
        fclose(f);
        free(s);
      }
    }
  }
}

void ifc(int i, int c, char* str, char** v, s21_grep t) {
  FILE* f;
  int fnc = fnct(i, c, v);

  if (t.e == 1) {
    ifce(i, c, str, v, t);
  } else {
    for (i = i + 1; i < c; i++) {
      int ct = 0;
      int maxstr = 0;
      if (v[i][0] != '-') {
        f = fopen(v[i], "r");
        if (f != NULL) {
          maxstr = max(v[i]) + 2;
          char* s = (char*)malloc(sizeof(char) * maxstr);
          while (fgets(s, maxstr, f)) {
            if (t.v != 1) {
              if (t.i != 1) {
                if (strstr(s, str) != NULL) {
                  ct++;
                }
              } else {
                if (strcasestr(s, str) != NULL) {
                  ct++;
                }
              }
            } else {
              if (t.i != 1) {
                if (strstr(s, str) == NULL) {
                  ct++;
                }
              } else {
                if (strcasestr(s, str) == NULL) {
                  ct++;
                }
              }
            }
          }
          if (fnc > 1 && t.h == 1) {
            printf("%s:%d\n", v[i], ct);
          } else {
            printf("%d\n", ct);
          }
          fclose(f);
          free(s);
        } else {
          if (t.s != 1) printf("grep: %s: No such file or directory\n", v[i]);
        }
      }
    }
  }
}

void ifce(int j, int c, char* str, char** v, s21_grep t) {
  FILE* f;
  int fnc = fnct(j, c, v);
  int status, cflags;
  if (t.i == 1) {
    cflags = REG_ICASE;
  } else {
    cflags = REG_EXTENDED;
  }

  for (int i = 1; i < c; i++) {
    regex_t reg;
    int ct = 0;
    int maxstr = 0;

    while (1) {
      if (strstr(v[i], "-e") != NULL) {
        if (strlen(v[i]) == 2) {
          if (c - i < 3)
            break;
          else
            i += 2;
        } else {
          break;
        }
      } else {
        break;
      }
    }
    if (v[i][0] != '-' && strcmp(v[i], v[j]) != 0) {
      f = fopen(v[i], "r");
      if (f != NULL) {
        maxstr = max(v[i]) + 2;
        char* s = (char*)malloc(sizeof(char) * maxstr);
        while (fgets(s, maxstr, f)) {
          FR(&status, c, cflags, str, s, v, &reg);
          if (t.v != 1) {
            if (status == 0) ct++;
          } else {
            if (status != 0) ct++;
          }
        }
        if (fnc > 1 && t.h != 1) {
          printf("%s:%d\n", v[i], ct);
        } else {
          printf("%d\n", ct);
        }
        fclose(f);
        free(s);
      } else {
        if (t.s != 1) printf("grep: %s: No such file or directory\n", v[i]);
      }
    }
  }
}

void ife(int j, int c, char* str, char** v, s21_grep t) {
  FILE* f;
  int status, cflags;
  int fc = fnct(j, c, v);
  int ct;
  if (t.i == 1) {
    cflags = REG_ICASE;
  } else {
    cflags = REG_EXTENDED;
  }
  regex_t reg;

  for (int i = 1; i < c; i++) {
    ct = 0;
    // fct++;
    // if (fct != 1) {
    //     if(sn == 0)
    //         printf("\n");
    // }
    int maxstr = 0;
    while (1) {
      if (strstr(v[i], "-e") != NULL) {
        if (strlen(v[i]) == 2) {
          if (c - i < 3)
            break;
          else
            i += 2;
        } else {
          break;
        }
      } else {
        break;
      }
    }
    if (v[i][0] != '-' && strcmp(v[i], str) != 0) {
      f = fopen(v[i], "r");
      if (f != NULL) {
        maxstr = max(v[i]) + 2;
        char* s = (char*)malloc(sizeof(char) * maxstr);
        while (fgets(s, maxstr, f)) {
          ct++;
          FR(&status, c, cflags, str, s, v, &reg);
          if (t.v != 1) {
            if (status == 0) {
              if (t.n == 1) {
                if (t.o != 1) {
                  if (fc > 1 && t.h != 1)
                    printf("%s:%d:%s", v[i], ct, s);
                  else
                    printf("%d:%s", ct, s);
                  if (feof(f) == 0) printf("\n");
                } else {
                  ifo(fc, ct, s, str, v[i], t);
                }
              } else {
                if (t.o != 1) {
                  if (fc > 1 && t.h != 1)
                    printf("%s:%s", v[i], s);
                  else
                    printf("%s", s);
                } else {
                  ifo(fc, ct, s, str, v[i], t);
                }
                if (feof(f) == 0) printf("\n");
              }
            }
          } else {
            if (status != 0) {
              if (t.n == 1) {
                if (fc > 1 && t.h != 1)
                  printf("%s:%d:%s", v[i], ct, s);
                else
                  printf("%d:%s", ct, s);
                if (feof(f) == 0) printf("\n");
              } else {
                if (fc > 1 && t.h != 1)
                  printf("%d:%s", ct, s);
                else
                  printf("%s", s);
                if (feof(f) == 0) printf("\n");
              }
            }
          }
        }
        free(s);
        fclose(f);
      } else {
        if (t.s != 1) printf("grep: %s: No such file or directory\n", v[i]);
      }
    }
  }
}

void ifo(int fnc, int ct, char* s, char* str, char* v, s21_grep t) {
  int count = 0;
  int sn = 0, sf = 0;
  int cts = 0;
  int ctstr = strlen(s);
  char *a, *b, *string;

  if (t.i != 1)
    a = s;
  else {
    a = lower(s);
    string = lower(str);
  }
  while (count < ctstr) {
    if (t.i != 1)
      b = strstr(a, str);
    else
      b = strstr(a, string);
    if (b != NULL) {
      cts++;
      a = b + strlen(str);
    }
    count++;
  }

  count = 0;
  if (t.v != 1) {
    while (count < cts) {
      if (fnc > 1 && t.h != 1 && sf != 1) {
        printf("%s:", v);
        sf = 1;
      }
      if (t.n == 1 && sn != 1) {
        printf("%d:", ct);
        sn = 1;
      }
      printf("%s\n", str);
      count++;
    }
  }
}

void FlagF(char* s, char* str, s21_grep t) {
  FILE* f;
  char* pa = (char*)malloc(sizeof(char) * 100);
  f = fopen(str, "r");
  while (fgets(pa, 100, f)) {
    if (t.v != 1) {
      if (t.i == 1) {
        s = lower(s);
        pa = lower(pa);
      }
      if (strstr(s, pa) != NULL || strstr(s, "\0") != NULL) {
        printf("%s", s);
        break;
      }
    } else {
      if (strstr(s, pa) == NULL || strstr(s, "\0") == NULL) {
        printf("%s", s);
        break;
      }
    }
  }
  free(pa);
  fclose(f);
}
