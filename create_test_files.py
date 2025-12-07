import random

with open("small.txt", "w") as f:
    numbers = [5, 2, 8, 1, 9, 3, 7, 4, 6, 10]
    f.write(" ".join(str(x) for x in numbers))

with open("medium.txt", "w") as f:
    numbers = list(x for x in range(1, 101))
    random.shuffle(numbers)  # перемешиваем
    for i in range(0, 100, 10):
        line = " ".join(str(x) for x in numbers[i : i + 10])
        f.write(' '.join(str(x) for x in numbers))

with open("large.txt", "w") as f:
    numbers = list(x for x in range(1, 1001))
    random.shuffle(numbers)
    f.write(" ".join(str(x) for x in numbers))

print("Файлы созданы:")
print("- small.txt (10 чисел)")
print("- medium.txt (100 чисел)")
print("- large.txt (1000 чисел)")
