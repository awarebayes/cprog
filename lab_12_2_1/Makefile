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

unit_tests.exe:
	cd ./unit_tests && $(MAKE) ../unit_tests.exe

%.d: src/%.c
	@$(CC) $(CFLAGS) $< -MM -MT $(@:%d=out/@.o) >$@

-include $(dep)

out/%.o: src/%.c
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

out/libio.a: out/io.o
	ar cr out/libio.a out/io.o
	ranlib out/libio.a

out/libutil.a: out/util.o
	ar cr out/libutil.a out/util.o
	ranlib out/libutil.a

out/libio.so: ./src/io.c ./inc/io.h
	$(CC) $(CFLAGS) -fPIC -shared -o $@ ./src/io.c -lc $(INC)

out/libutil.so: ./src/util.c ./inc/util.h
	$(CC) $(CFLAGS) -fPIC -shared -o $@ ./src/util.c -lc $(INC)

.PHONY: unit
unit:
	cd ./unit_tests && $(MAKE) unit

.PHONY: compile_static
compile_static: out/main.o out/libio.a out/libutil.a
	$(CC) -o app.exe ./out/main.o -L ./out/ -lio -lutil

.PHONY: compile_dynamic
compile_dynamic: out/main.o out/libio.so out/libutil.so
	$(CC) -o app.exe ./out/main.o -L ./out/ -lio -lutil

.PHONY: func
func: 
	python ./func_tests/test_simple.py .

.PHONY: clean
clean:
	$(RM) -f ./out/*.o
	$(RM) -f ./out/*.a
	$(RM) -f ./out/*.so
	$(RM) -f ./**/*.exe
	$(RM) -f ./*.exe
