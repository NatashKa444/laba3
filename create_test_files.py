import random

# 1. smallest.txt - 100 чисел (было 10)
with open("smallest.txt", "w") as f:
    numbers = [random.randint(1, 10000) for _ in range(100)]
    f.write(" ".join(str(x) for x in numbers))

# 2. small.txt - 500 чисел (было 50)
with open("small.txt", "w") as f:
    numbers = [random.randint(1, 10000) for _ in range(500)]
    f.write(" ".join(str(x) for x in numbers))

# 3. medium.txt - 1000 чисел
with open("medium.txt", "w") as f:
    numbers = [random.randint(1, 10000) for _ in range(1000)]
    f.write(" ".join(str(x) for x in numbers))

# 4. big.txt - 5000 чисел (было 500)
with open("big.txt", "w") as f:
    numbers = [random.randint(1, 10000) for _ in range(5000)]
    f.write(" ".join(str(x) for x in numbers))

# 5. biggest.txt - 10000 чисел (было 1000)
with open("biggest.txt", "w") as f:
    numbers = [random.randint(1, 10000) for _ in range(10000)]
    f.write(" ".join(str(x) for x in numbers))

print("Файлы созданы:")
print("- smallest.txt (100 чисел)")
print("- small.txt (500 чисел)")
print("- medium.txt (1000 чисел)")
print("- big.txt (5000 чисел)")
print("- biggest.txt (10000 чисел)")
