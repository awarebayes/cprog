CC := gcc

CFLAGS := -std=c99 -Wall -Wpedantic -Wextra -Wfloat-conversion -Wfloat-equal -Wvla 
LDFLAGS := -lcheck
INC := -I inc/

COMPILE := $(CC) $(CFLAGS) 

obj := out/check_key.o out/check_mysort.o out/check_n_numbers.o out/check_read.o out/util.o

.PHONY: release
release: app.exe

.PHONY: all
all: app.exe

.PHONY: debug
debug: CFLAGS += -DDEBUG -g
debug: app.exe

.PHONY: tests
tests: unit_tests.exe

.PHONY: func
func: app.exe
	python ./func_tests/test_simple.py .

unit: tests
	./unit_tests.exe

app.exe: out/main.o $(obj)
	$(CC) -o $@ $^ $(LDFLAGS)

unit_tests.exe: out/check_main.o $(obj)
	$(CC) -o $@ $^ $(LDFLAGS)

out/check_key.o: unit_tests/check_key.c inc/check_main.h
	$(COMPILE) -o $@ -c unit_tests/check_key.c

out/check_n_numbers.o: unit_tests/check_n_numbers.c inc/check_main.h
	$(COMPILE) -o $@ -c unit_tests/check_n_numbers.c

out/check_mysort.o: unit_tests/check_mysort.c inc/check_main.h
	$(COMPILE) -o $@ -c unit_tests/check_mysort.c

out/check_read.o: unit_tests/check_read.c inc/check_main.h
	$(COMPILE) -o $@ -c unit_tests/check_read.c

out/check_main.o: unit_tests/check_main.c inc/check_main.h
	$(COMPILE) -o $@ -c unit_tests/check_main.c

out/util.o: src/util.c inc/util.h
	$(COMPILE) -o $@ -c src/util.c

out/main.o: src/main.c
	$(COMPILE) -o $@ -c src/main.c

.PHONY: clean
clean:
	$(RM) -f ./out/*
	$(RM) -f ./**/*.exe
	$(RM) -f ./*.ex