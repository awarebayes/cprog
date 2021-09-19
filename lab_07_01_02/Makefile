CC := gcc

CFLAGS := -std=c99 -MMD -Wall -Wpedantic -Wextra -Wfloat-conversion -Wfloat-equal -Wvla -lcheck
LDFLAGS := -lcheck
INC := -I inc/

.PHONY: debug
debug: main.exe
debug: CFLAGS += -DDEBUG -g

.PHONY: debug_tests
debug_tests: CFLAGS += -DDEBUG -g
debug_tests: test.exe

src = $(filter-out src/test.c src/main.c,  $(wildcard src/*.c))
obj = $(src:src/%.c=out/%.o)
dep = $(obj:.o=.d)

main.exe: out/main.o $(obj)
	$(CC) -o $@ $^ $(LDFLAGS)

test.exe: out/check_test.o $(obj)
	$(CC) -o $@ $^ $(LDFLAGS)

%.d: src/%.c
	@$(CC) $(CFLAGS) $< -MM -MT $(@:%d=out/@.o) >$@

-include $(dep)

out/%.o: src/%.c
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

.PHONY: unit
unit: /check_test.exe
	./test.exe

.PHONY: func
func: main.exe
	python ./func_tests/test.py .

.PHONY: clean
clean:
	$(RM) -f ./out/*
	$(RM) -f ./*.exe