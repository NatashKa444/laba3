# TARGET = program
# .PHONY: all clean 

# all: $(TARGET)
# clean:
# 	del /Q $(TARGET) *.o

# main.o: main.c
# 	gcc -c -o main.o main.c

# stack.o: stack.c
# 	gcc -c -o stack.o stack.c

# sorting.o: sorting.c
# 	gcc -c -o sorting.o sorting.c

# $(TARGET): main.o stack.o sorting.o
# 	gcc -o $(TARGET) main.o stack.o sorting.o





# ----------------
TARGET = program
CC = gcc

.PHONY: all clean 

all: $(TARGET)

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