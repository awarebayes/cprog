CC := gcc

CFLAGS := -std=c99 -MMD -Wall -Wpedantic -Wextra -Wfloat-conversion -Wfloat-equal -Wvla 

src = $(filter-out test.c main.c,  $(wildcard *.c))
obj = $(src:.c=.o)
dep = $(obj:.o=.d)

main: main.o $(obj)
	$(CC) $(CFLAGS) -o $@ $^

test: test.o $(obj)
	$(CC) $(CFLAGS) -o $@ $^

-include $(dep)

.PHONY: clean
clean:
	$(RM) -f $(obj) ./main main.o test.o

.PHONY: cleandep
cleandep:
	rm -f $(dep) main.d test.d