CC := gcc

CFLAGS := -std=c99 -MMD -Wall -Wpedantic -Wextra -Wfloat-conversion -Wfloat-equal -Wvla -lcheck
LDFLAGS := -lcheck
INC := -I inc/

.PHONY: debug
debug: main.exe
debug: CFLAGS += -DDEBUG -g

.PHONY: release
release: main.exe

debug_tests:
	cd unit_tests && make debug_tests

src = $(filter-out src/main.c,  $(wildcard src/*.c))
obj = $(src:src/%.c=out/%.o)
dep = $(obj:.o=.d)

main.exe: out/main.o $(obj)
	$(CC) -o $@ $^ $(LDFLAGS)

%.d: src/%.c
	@$(CC) $(CFLAGS) $< -MM -MT $(@:%d=out/@.o) >$@

-include $(dep)

out/%.o: src/%.c
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

.PHONY: unit
unit:
	cd ./unit_tests && make unit

.PHONY: func
func: main.exe
	python ./func_tests/test_simple.py .

.PHONY: clean
clean:
	$(RM) -f ./out/*
	$(RM) -f ./**/*.exe
	$(RM) -f ./*.exe