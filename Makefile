CC=g++
CFLAGS= 
EXECUTABLE=program

program: ht_linked_list.o func.o  ht_functions.o main.o
	@$(CC) -g $(CFLAGS) -o program ht_linked_list.o func.o ht_functions.o main.o 

ht_linked_list.o: ./hash/ht_linked_list.cpp 
	@$(CC) $(CFLAGS) -g -c ./hash/ht_linked_list.cpp

func.o: func.cpp
	@$(CC) $(CFLAGS) -g -c func.cpp

ht_functions.o: ./hash/ht_functions.cpp 
	@$(CC) $(CFLAGS) -g -c ./hash/ht_functions.cpp

main.o: main.cpp 
	@$(CC) $(CFLAGS) -g -c main.cpp

test:
	bash ./tests/bash.sh

clean: 
	rm *.o program
	rm *.c~ 
	rm *.h~
