# CFLAGS = -Wall
# SRC := $(wildcard *.c)
# OBJ := $(patsubst %.c,%.o,$(SRC))
# EXEC = p2_e1
# TARNAME := $(EXEC:%=%.tgz)

# # $< primero despues de :
# # $^ todo despues de :
# # $@ izquierda de :

# all: $(EXEC) 

# %.o: %.c %.h
# 	gcc -c $(CFLAGS) $<


# $(EXEC): $(OBJ)
# 	gcc $^ -o $@


# dist:
# 	@tar -czf $(TARNAME) *.h *.c
# 	@echo Fichero $(TARNAME) creado 

# clean:
# 	rm -f $(EXEC) *.o

########################################################
CC=gcc
CFLAGS= -g -Wall -pedantic
########################################################
OBJECTSP1E1 = p1_e1.o node.o
OBJECTSP1E2 = p1_e2.o graph.o node.o
OBJECTSP1E3 = p1_e3.o graph.o node.o
OBJECTSP2E1 = p2_e1.o graph.o node.o stack_elestack.o elestack.o
OBJECTSP2E2 = p2_e2.o graph.o node.o stack_elestack.o elestack.o
OBJECTSP2E31 = p2_e3-node.o stack_fp.o
OBJECTSP2E32 = p2_e3-int.o stack_fp.o
########################################################

EXEC = p1_e1 p1_e2 p1_e3 p2_e2 p2_e3-node p2_e3-int
EXECOBJ := $(EXEC:%=%.o)
all: $(EXEC)

p1_e1: $(OBJECTSP1E1)
	$(CC) $(CFLAGS) -o p1_e1 $(OBJECTSP1E1)
p1_e1.o: p1_e1.c node.h
	$(CC) $(CFLAGS) -c p1_e1.c

p1_e2: $(OBJECTSP1E2)
	$(CC) $(CFLAGS) -o p1_e2 $(OBJECTSP1E2)

p1_e2.o: p1_e2.c node.h graph.h
	$(CC) $(CFLAGS) -c p1_e2.c

p1_e3: $(OBJECTSP1E3)
	$(CC) $(CFLAGS) -o p1_e3 $(OBJECTSP1E3)

p1_e3.o: p1_e3.c node.h graph.h
	$(CC) $(CFLAGS) -c p1_e3.c

p2_e1: $(OBJECTSP2E1)
	$(CC) $(CFLAGS) -o p2_e1 $(OBJECTSP2E1)

p2_e1.o: p2_e1.c graph.h node.h types.h stack_elestack.h elestack.h 
	gcc -c $< -o $@

p2_e2: $(OBJECTSP2E2)
	$(CC) $(CFLAGS) -o p2_e2 $(OBJECTSP2E2)

p2_e2.o: p2_e2.c graph.h node.h types.h stack_elestack.h elestack.h 
	gcc -c $< -o $@

p2_e3-node: $(OBJECTSP2E31)
	$(CC) $(CFLAGS) -o p2_e3-node $(OBJECTSP2E31)

p2_e3-node.o: p2_e3-node.c types.h stack_fp.h
	gcc -c $< -o $@

p2_e3-int: $(OBJECTSP2E32)
	$(CC) $(CFLAGS) -o p2_e3-int $(OBJECTSP2E32)

p2_e3-int.o: p2_e3-int.c types.h stack_fp.h
	gcc -c $< -o $@

node.o: node.c node.h
	$(CC) $(CFLAGS) -c node.c

graph.o: graph.c graph.h node.h
	$(CC) $(CFLAGS) -c graph.c

stack_elestack.o: stack_elestack.c stack_elestack.h
	$(CC) $(CFLAGS) -c stack_elestack.c

elestack.o: elestack.c elestack.h
	$(CC) $(CFLAGS) -c elestack.c

stack_fp.o: stack_fp.c stack_fp.h
	$(CC) $(CFLAGS) -c stack_fp.c

clean:
	rm -rf *.o $(EXEC)

runv:
	@echo ">>>>>>Running p1_e1 with valgrind"
	valgrind --leak-check=full ./p1_e1
	@echo ">>>>>>Running p1_e2 with valgrind"
	valgrind --leak-check=full --track-origins=yes ./p1_e2 
	@echo ">>>>>>Running p1_e2 with valgrind
	valgrind --leak-check=full ./p1_e3 g2_s.txt
