CFLAGS = -Wall
SRC := $(wildcard *.c)
OBJ := $(patsubst %.c,%.o,$(SRC))
EXEC = p3_e1
TARNAME := $(EXEC:%=%.tgz)

# $< primero despues de :
# $^ todo despues de :
# $@ izquierda de :

all: $(EXEC) 

%.o: %.c %.h
	gcc -c $(CFLAGS) $<


$(EXEC): $(OBJ)
	gcc $^ -o $@


dist:
	@tar -czf $(TARNAME) *.h *.c
	@echo Fichero $(TARNAME) creado 

clean:
	rm -f $(EXEC) *.o
