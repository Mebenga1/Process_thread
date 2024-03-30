
CC= gcc
ARGS= -g -Wall
OBJ= ./build/process_thread.o ./build/Process_thread_main.o
EXEC= ./process_thread

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(ARGS) -o $(EXEC) $(OBJ) -lpthread

./build/process_thread.o: ./src/process_thread.c ./src/process_thread.h
	$(CC) $(ARGS) -o ./build/process_thread.o -c ./src/process_thread.c -I./src/ -lpthread

./build/Process_thread_main.o: ./src/Process_thread_main.c ./src/process_thread.h
	$(CC) $(ARGS) -o ./build/Process_thread_main.o -c ./src/Process_thread_main.c -I./src/


clean:
	rm -r -f ./build/* && rm -f $(EXEC) && rm -f ./file/*
