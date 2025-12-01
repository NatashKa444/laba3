import matplotlib.pyplot as plt

# Читаем результаты из файла
sizes = []
insertion_times = []
merge_times = []

try:
    with open("results.txt", "r", encoding="utf-8") as f:
        lines = f.readlines()
        # Пропускаем первую строку с заголовками
        for line in lines[1:]:
            if line.strip():
                parts = line.split()
                sizes.append(int(parts[0]))
                insertion_times.append(float(parts[1]))
                merge_times.append(float(parts[2]))
except FileNotFoundError:
    print("Файл results.txt не найден!")
    print(
        "Сначала запустите программу и выберите опцию 3 для сравнения методов сортировки"
    )
    exit()

# Создаем график
plt.figure(figsize=(10, 6))

# Рисуем линии для каждого метода
plt.plot(sizes, insertion_times, "ro-", label="Прямое включение", linewidth=2)
plt.plot(sizes, merge_times, "bo-", label="Слиянием", linewidth=2)

# Подписи
plt.title("Сравнение скорости сортировки стека")
plt.xlabel("Размер данных (количество чисел)")
plt.ylabel("Время выполнения (секунды)")
plt.legend()

# Сетка для удобства чтения
plt.grid(True)

# Сохраняем график в файл
plt.savefig("sorting_comparison.png")

# Показываем график на экране
plt.show()

# Выводим объяснение в консоль
print("\n" + "=" * 50)
print("ОБЪЯСНЕНИЕ РЕЗУЛЬТАТОВ:")
print("=" * 50)
print("Сортировка ПРЯМЫМ ВКЛЮЧЕНИЕМ (красная линия):")
print("- Простая в понимании")
print("- Медленная на больших данных")
print("- Хороша для маленьких наборов чисел")

print("\nСортировка СЛИЯНИЕМ (синяя линия):")
print("- Сложнее в реализации")
print("- Быстрая на больших данных")
print("- Лучший выбор для больших наборов чисел")

print("\nВЫВОД:")
print("- Мало чисел (10-100): разница небольшая")
print("- Много чисел (1000+): сортировка слиянием быстрее")
print("- График сохранен в файл 'sorting_comparison.png'")
