CC := gcc

CFLAGS := -std=c99 -MMD -Wall -Wpedantic -Wextra -Wfloat-conversion -Wfloat-equal -Wvla -lcheck

.PHONY: debug
debug: main.exe
debug: CFLAGS += -DDEBUG -g

.PHONY: debug_tests
debug_tests: CFLAGS += -DDEBUG -g
debug_tests: test.exe

src = $(filter-out test.c main.c,  $(wildcard *.c))
obj = $(src:.c=.o)
dep = $(obj:.o=.d)

main.exe: main.o $(obj)
	$(CC) $(CFLAGS) -o $@ $^

test.exe: test.o $(obj)
	$(CC) $(CFLAGS) -o $@ $^

-include $(dep)

.PHONY: unit
unit: test.exe
	./test.exe

.PHONY: func
func: main.exe
	python ./func_tests/test.py .

.PHONY: clean
clean:
	$(RM) -f $(obj) ./main.exe ./test.exe main.o test.o
	$(RM) -f $(dep) main.d test.d