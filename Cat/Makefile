CC=g++
CFLAGS=-Wall -Werror -Wextra
LDFLAGS=
SOURCES=s21_cat.c parser.c reader.c
OBJECTS=$(SOURCES:.c)
EXECUTABLE=s21_cat

all:
	$(CC) $(CFLAGS) $(SOURCES) -o $(EXECUTABLE)

clean:
	rm -rf cat a.out *.o a.exe s21_cat
