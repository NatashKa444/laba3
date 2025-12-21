TARGET = myprogram
FILES = main.o stack.o sorting.o

.PHONY: all clean run

all: $(TARGET)

run: 
	./$(TARGET) 

run_file: all
	./$(TARGET) --file input.txt

clean:
	del /Q $(TARGET) *.o

main.o: main.c
	gcc -c -o main.o main.c

stack.o: stack.c
	gcc -c -o stack.o stack.c

sorting.o: sorting.c
	gcc -c -o sorting.o sorting.c

$(TARGET): main.o stack.o sorting.o
	gcc -o $(TARGET) main.o stack.o sorting.o