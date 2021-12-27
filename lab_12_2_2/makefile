CC := gcc

all: library/libarr.so

library/libarr.so: ./library/libarr.c ./library/libarr.h
	$(CC) $(CFLAGS) -fPIC -shared -o $@ ./library/libarr.c -lc

.PHONY: clean
clean:
	rm ./library/*.so


test_c:
	cd c_test && $(MAKE) all