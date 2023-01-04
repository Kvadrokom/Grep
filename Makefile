CC=g++
CFLAGS=-Wall -Werror -Wextra
LDFLAGS=
SOURCES=s21_grep.c parser.c reader.c auxiliary.c
OBJECTS=$(SOURCES:.c)
EXECUTABLE=s21_grep

all:
	$(CC) $(CFLAGS) $(SOURCES) -o $(EXECUTABLE)

clean:
	rm -rf grep a.out *.o a.exe s21_grep