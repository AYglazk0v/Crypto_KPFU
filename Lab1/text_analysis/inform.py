filename = input("Введите имя файла: ")

with open(filename, 'r') as f:
    text = f.read()
    size = len(text) - 1
    print("Общее количество символов:", size)
    for c in sorted(set(text), key=lambda c: text.count(c), reverse=True):
        count_c = text.count(c)
        print("Количество символа '{}': {} вероятность: {}".format(c, count_c, round((count_c/size),4)))
