TARGET = myprogram
FILES = main.o stack.o sorting.o

.PHONY: all clean run

all: $(TARGET)
	gcc -o $(TARGET) $(FILES)

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
	gcc -c sorting.c -o sorting.o

$(TARGET): main.o stack.o sorting.o
	gcc -o $(TARGET) main.o stack.o sorting.o