import matplotlib.pyplot as plt

sizes = []
insertion = []
merge = []

with open("results.txt", "r") as f:
    lines = f.readlines()
    for line in lines[1:]:
        line = line.replace(",", ".")
        parts = line.split()  # разделили на части
        sizes.append(int(parts[0]))
        insertion.append(float(parts[1]))
        merge.append(float(parts[2]))

# Строим график
plt.figure(figsize=(10, 6))
plt.plot(sizes, insertion, "ro-", label="Прямое включение")
plt.plot(sizes, merge, "bo-", label="Слиянием")
plt.title("Сравнение сортировок")
plt.xlabel("Размер данных")
plt.ylabel("Время (с)")
plt.legend()
plt.grid(True)
plt.savefig("graph.png")
plt.show()

print("Прямое включение - медленнее на больших данных")
print("Слиянием - быстрее на больших данных")
print("График сохранен как graph.png")
