CC := gcc

CFLAGS := -std=c99 -Wall -Wpedantic -Wextra -Wfloat-conversion -Wfloat-equal -Wvla 
LDFLAGS := -lcheck
INC := -I inc/

.PHONY: debug_tests
debug_tests: CFLAGS += -DDEBUG -g
debug_tests: test.exe

SRC_DIR = ../src
OUT_DIR = ../out

src1 = $(filter-out $(SRC_DIR)/main.c,  $(wildcard $(SRC_DIR)/*.c))
src2 = $(filter-out ./check_main.c, $(wildcard ./*.c))
src = $(src1) $(src2)
obj1 = $(src1:$(SRC_DIR)/%.c=$(OUT_DIR)/%.o)
obj2 = $(src2:./%.c=$(OUT_DIR)/%.o)
obj = $(obj1) $(obj2)
dep = $(obj3:.o=.d)

test.exe: $(OUT_DIR)/check_main.o $(obj)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OUT_DIR)/%.d: $(SRC_DIR)/%.c 
	@$(CC) $(CFLAGS) $< -MM -MT $(@:%d=$(OUT_DIR)/@.o) >$@

-include $(dep)

$(OUT_DIR)/check_main.o: check_main.c $(obj)
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

$(OUT_DIR)/util.o: $(SRC_DIR)/util.c
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

$(OUT_DIR)/%.o: %.c 
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

.PHONY: unit
unit: test.exe
	./test.exe

.PHONY: clean
clean:
	$(RM) -f $(OUT_DIR)/*
	$(RM) -f ./*.exe