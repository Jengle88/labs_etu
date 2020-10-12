import wikipedia


# существует ли такая страница
def is_page_valid(page):
    try:
        wikipedia.page(page)
    except Exception:
        return False
    return True


# существует ли такой язык
def is_right_lang(language):
    return language in wikipedia.languages()


# максимальное количество слов в кратком содержании страницы
def max_cnt_word_in_summary(array_page):
    # количество слов в строке
    def cnt_word(string):
        a = list(string.replace('\n', ' ').replace('\t', ' ').split())
        return len(a)

    maxCount = 0
    answerPage = None
    for page in array_page:
        if not is_page_valid(page):  # если не существует
            continue
        cntInIterPage = cnt_word(wikipedia.page(page).summary)
        if maxCount <= cntInIterPage:
            answerPage = page
            maxCount = cntInIterPage
    return [maxCount, answerPage]


# ищем цепочку
def find_chain(pageArray):
    # ищем промежуточное звено
    def find_support_chain(pagesSuppArray, index):

        nonlocal pageArray

        for page in pagesSuppArray:
            if not is_page_valid(page):  # если не существует
                continue
            if pageArray[index] in wikipedia.page(page).links:  # если есть ссылка
                return page

    # поиск первого элемента цепочки и проверка массива
    firstIndex = 0
    # двигаем firstIndex, пока идут несущ страницы
    while firstIndex < len(pageArray) and not is_page_valid(pageArray[firstIndex]):
        firstIndex += 1
    if firstIndex == len(pageArray):
        return []

    # поиск самой цепочки
    answer = [pageArray[firstIndex]]
    for i in range(0, len(pageArray) - 1):
        if not is_page_valid(pageArray[i]):
            continue
        linksArray = wikipedia.page(pageArray[i]).links
        if not (pageArray[i + 1] in linksArray):
            answer.append(find_support_chain(linksArray, i + 1))
        answer.append(pageArray[i + 1])
    return answer


# точка входа в программу
array = input().split(', ')
if is_right_lang(array[-1]):
    wikipedia.set_lang(array[-1])
else:
    print("no results")
    quit(0)
array.pop()
print(*max_cnt_word_in_summary(array))
print(find_chain(array))
# print(cnt_word(wikipedia.page(array[1]).summary))
