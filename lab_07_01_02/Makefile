CC := gcc

CFLAGS := -std=c99 -Wall -Wpedantic -Wextra -Wfloat-conversion -Wfloat-equal -Wvla -g -DDEBUG
LDFLAGS := -lcheck
INC := -I inc/

COMPILE := $(CC) $(CFLAGS) 

obj := out/check_key.o out/check_mysort.o out/check_n_numbers.o out/check_read.o out/util.o

.PHONY: release
release: app.exe

.PHONY: debug
debug: CFLAGS += -DDEBUG -g
debug: app.exe

.PHONY: tests
tests: unit_tests/test.exe

.PHONY: func
func: app.exe
	python ./func_tests/test_simple.py .

unit: tests
	cd ./unit_tests && ./test.exe

app.exe: out/main.o $(obj)
	 $(CC) -o $@ $^ $(LDFLAGS)

unit_tests/test.exe: out/check_main.o $(obj)
	$(CC) -o $@ $^ $(LDFLAGS)

out/check_key.o: unit_tests/check_key.c 
	$(COMPILE) -o $@ -c $^

out/check_n_numbers.o: unit_tests/check_n_numbers.c 
	$(COMPILE) -o $@ -c $^

out/check_mysort.o: unit_tests/check_mysort.c
	$(COMPILE) -o $@ -c $^

out/check_read.o: unit_tests/check_read.c
	$(COMPILE) -o $@ -c $^

out/check_main.o: unit_tests/check_main.c 
	$(COMPILE) -o $@ -c $^

out/util.o: src/util.c 
	$(COMPILE) -o $@ -c $^

out/main.o: src/main.c
	$(COMPILE) -o $@ -c $^

.PHONY: clean
clean:
	$(RM) -f ./out/*
	$(RM) -f ./**/*.exe
	$(RM) -f ./*.ex