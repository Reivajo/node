CFLAGS = -Wall -ansi -pedantic

EXEC = p1_e1 p1_e2
EXECOBJ := $(EXEC:%=%.o)

DEPS := $(wildcard *.h)
SRC := $(wildcard *.c)
OBJ := $(filter-out $(EXECOBJ),$(patsubst %.c,%.o,$(SRC)))



# $< primero despues de :
# $^ todo despues de :
# $@ izquierda de :

all: $(EXEC) 

# %.o: %.c $(DEPS)
# 	gcc -c $(CFLAGS) $<

p1_e1: p1_e1.o graph.o node.o
	gcc $^ -o $@

p1_e1.o: p1_e1.c graph.h node.h types.h
	gcc -c $< -o $@

p1_e2: p1_e2.o graph.o node.o
	gcc $^ -o $@

p1_e2.o: p1_e2.c graph.h node.h types.h
	gcc -c $< -o $@

graph.o: graph.c graph.h node.h types.h
	gcc -c $< -o $@

node.o: node.c node.h types.h
	gcc -c $< -o $@

# $(EXEC): $(OBJ)
# 	gcc $^ -o $@ 


# # $(CFLAGS)

# $(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPS)
# 	@echo -n Compilando objeto \'$<\'...
# 	@gcc -c -o $@ $< $(CFLAGS)
# 	@echo [OK]


print-%  : ; @echo $* = $($*)

dist:
	@tar -czf $(TARNAME) *.h *.c
	@echo Fichero $(TARNAME) creado 

clean:
	rm -f $(EXEC) $(OBJ) *.o