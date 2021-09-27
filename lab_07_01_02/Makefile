CC := gcc

CFLAGS := -std=c99 -Wall -Wpedantic -Wextra -Wfloat-conversion -Wfloat-equal -Wvla
LDFLAGS := -lcheck
INC := -I inc/

.PHONY: debug
debug: app.exe
debug: CFLAGS += -DDEBUG -g

.PHONY: release
release: app.exe

.PHONY: all
all: app.exe

debug_tests:
	cd unit_tests && make debug_tests

src = $(filter-out src/main.c src/profile.c,  $(wildcard src/*.c))
obj = $(src:src/%.c=out/%.o)
dep = $(obj:.o=.d)

app.exe: out/main.o $(obj)
	$(CC) -o $@ $^ $(LDFLAGS)

profile.exe: out/profile.o $(obj)
	$(CC) -o $@ $^ $(LDFLAGS)

%.d: src/%.c
	@$(CC) $(CFLAGS) $< -MM -MT $(@:%d=out/@.o) >$@

-include $(dep)

out/%.o: src/%.c
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

.PHONY: unit
unit:
	cd ./unit_tests && $(MAKE) unit

.PHONY: func
func: app.exe
	python ./func_tests/test_simple.py .

.PHONY: clean
clean:
	$(RM) -f ./out/*.o
	$(RM) -f ./**/*.exe
	$(RM) -f ./*.exe