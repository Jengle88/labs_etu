import math


def calc_aver_item(array: list):
    ans = 0
    for it in array:
        ans += it
    return ans / len(array)


def calc_aver_SKO(array: list, averItem):
    averSKO = 0
    for it in array:
        averSKO += (averItem - it) ** 2
    averSKO /= len(array) - 1
    return math.sqrt(averSKO)


def check_for_SKO(minItem, maxItem, averItem, valSKO):
    val1 = math.fabs(minItem - averItem) / valSKO
    val2 = math.fabs(maxItem - averItem) / valSKO
    return [val1, val2]


def check_good_SKO(val, koefPogr):
    if val < koefPogr:
        return "V (" + str(round(val,3)) + ")"
    else:
        return "X (" + str(round(val,3)) + ")"


def calc_lucky_defect(averageSKO, koefStud):
    return koefStud * averageSKO


def calc_full_defect(luckyDefect, toolDefect):
    return math.sqrt(luckyDefect ** 2 + toolDefect ** 2)


array = input("Выборка = ").split(' ')
toolDefect = float(input("Приборная погрешность = "))
koefStud = float(input("Коэффициент Стьюдента(t) = "))
koefPogr = float(input("Коэффициент грубой погрешности(V) = "))
n = len(array)
if n <= 1:
    exit(0)
for i in range(0, n):
    array[i] = float(array[i])
array.sort()
print("Ранжированный список: ")
print(array, sep=' ')

print("Макс:", array[-1], "\tМин:", array[0], "\tРазмах: ", round(array[-1] - array[0],3))
averItem = calc_aver_item(array)
print("Выборочное среднее:", round(averItem,3))

averSKO = calc_aver_SKO(array, averItem)
print("Вычисление СКО:", averSKO)

checkedSKO = check_for_SKO(array[0], array[-1], averItem, averSKO)
print("Проверка по СКО: Мин -", check_good_SKO(checkedSKO[0], koefPogr), "Макс -", check_good_SKO(checkedSKO[1], koefPogr))

print("Среднее СКО =", averSKO / math.sqrt(len(array)))

luckyDefect = calc_lucky_defect(averSKO / math.sqrt(len(array)), koefStud)
print("Случайная погрешность по Стьюденту:", luckyDefect)

print("Полная погрешность:", calc_full_defect(luckyDefect, toolDefect))

