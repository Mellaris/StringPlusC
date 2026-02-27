CFLAGS = -std=c11 -Wall -Werror -Wextra
SRCS = s21_string.c
OBJS = s21_string.o

all: s21_string.a

s21_string.a: $(OBJS)
	ar rcs s21_string.a $(OBJS)
	ranlib s21_string.a

s21_string.o: s21_string.c s21_string.h
	gcc $(CFLAGS) -c s21_string.c -o s21_string.o

test: s21_string.a test.c
	gcc $(CFLAGS) test.c s21_string.a -o test -lcheck -lm -lsubunit -lpthread
	./test

gcov_report: test.c s21_string.c
	gcc $(CFLAGS) -fprofile-arcs -ftest-coverage test.c s21_string.c -o gcov_test -lcheck -lm -lsubunit -lpthread
	./gcov_test
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	@echo "Report generated in report/index.html"

clean:
	rm -f *.o *.a test gcov_test *.gcda *.gcno *.info
	rm -rf report

.PHONY: all test gcov_report clean