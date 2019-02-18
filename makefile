########################################################
CC=gcc
CFLAGS= -g -Wall
EJS = p1_e1 p1_e2 p1_e3
########################################################
OBJECTSP1E1 = p1_e1.o node.o
OBJECTSP1E2 = p1_e2.o graph.o node.o
OBJECTSP1E3 = p1_e3.o graph.o node.o
########################################################

EXEC = p1_e1 p1_e2 p1_e3
EXECOBJ := $(EXEC:%=%.o)

p1_e1: $(OBJECTSP1E1)
	$(CC) $(CFLAGS) -o p1_e1 $(OBJECTSP1E1)

p1_e2: $(OBJECTSP1E2)
	$(CC) $(CFLAGS) -o p1_e2 $(OBJECTSP1E2)

p1_e3: $(OBJECTSP1E3)
	$(CC) $(CFLAGS) -o p1_e3 $(OBJECTSP1E3)

p1_e3.o: p1_e3.c node.h graph.h
	$(CC) $(CFLAGS) -c p1_e3.c

p1_e2.o: p1_e2.c node.h graph.h
	$(CC) $(CFLAGS) -c p1_e2.c

p1_e1.o: p1_e2.c node.h
	$(CC) $(CFLAGS) -c p1_e1.c

node.o: node.c node.h
	$(CC) $(CFLAGS) -c node.c

graph.o: graph.c graph.h node.h
	$(CC) $(CFLAGS) -c graph.c

clear:
	rm -rf *.o 

clean:
	rm -rf *.o $(EJS)

p1_e3: p1_e3.o graph.o node.o
	gcc $^ -o $@

p1_e3.o: p1_e3.c graph.h node.h types.h
	gcc -c $< -o $@

graph.o: graph.c graph.h node.h types.h
	gcc -c $< -o $@

runv:
	@echo ">>>>>>Running p1_e1 with valgrind"
	valgrind --leak-check=full ./p1_e1
	@echo ">>>>>>Running p1_e2 with valgrind"
	valgrind --leak-check=full --track-origins=yes ./p1_e2 
	@echo ">>>>>>Running p1_e2 with valgrind
	valgrind --leak-check=full ./p1_e3 g2_s.txt
