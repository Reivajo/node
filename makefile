SRC := $(wildcard *.c)
EXEC := $(SRC:%.c=%)

all: $(EXEC)

%: %.c
	gcc -o $@ $< -I.


clean:
	rm -rf $(EXEC)
