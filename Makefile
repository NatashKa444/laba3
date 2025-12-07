TARGET = program
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




# .PHONY: all clean run
# PROGRAM = lab_stack 
# FILES = main.c stack.c sorting.c  
# all:
#  	gcc $(FILES) -o $(PROGRAM)
# clean:
# 	rm -f $(PROGRAM)
# run:
# 	./$(PROGRAM)



# CC = gcc

# # Имя программы
# TARGET = program.exe

# # Все .c файлы
# SOURCES = main.c stack.c sorting.c

# # Правило по умолчанию - собираем программу
# all: $(TARGET)

# # Как собрать программу
# $(TARGET): $(SOURCES)
# 	$(CC) -o $(TARGET) $(SOURCES)

# # Очистка - удаляем скомпилированные файлы
# clean:
# 	if exist $(TARGET) del $(TARGET)

# # Запуск программы
# run: $(TARGET)
# 	$(TARGET)

# # Запуск с тестовым файлом
# test: $(TARGET)
# 	$(TARGET) --file small.txt