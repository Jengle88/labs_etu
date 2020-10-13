import wikipedia


# существует ли такая страница
def is_page_valid(page):
    try:
        wikipedia.page(page)
    except Exception:
        return False
    return True
# безопасное обращение к странице
def safe_page(page):
    try:
        pageAnswer = wikipedia.page(page)
    except wikipedia.DisambiguationError as e:
        pageAnswer = wikipedia.page(e.options[0])
    return pageAnswer.title

# существует ли такой язык
def is_right_lang(language):
    return language in wikipedia.languages()


# максимальное количество слов в кратком содержании страницы
def max_cnt_word_summary(array_page):
    # количество слов в строке
    def cnt_word(string):
        return len(list(string.replace('\n', ' ').replace('\t', ' ').split()))

    maxCount = 0
    answerPage = None
    for page in array_page:
        cntInIterPage = cnt_word(wikipedia.page(safe_page(page)).summary)
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
            if not is_page_valid(page):
                continue
            if pageArray[index] in wikipedia.page(safe_page(page)).links:  # если есть ссылка
                return page

    # поиск первого элемента цепочки и проверка массива
    firstIndex = 0
    if firstIndex == len(pageArray):
        return []

    # поиск самой цепочки
    answer = [pageArray[firstIndex]]
    for i in range(firstIndex, len(pageArray) - 1):
        linksArray = wikipedia.page(safe_page(pageArray[i])).links
        if pageArray[i + 1] not in linksArray:
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
rightPageArray = list(filter(is_page_valid, array))
print(*max_cnt_word_summary(rightPageArray))
print(find_chain(rightPageArray))
# print(cnt_word(wikipedia.page(array[1]).summary))
#Still on My Mind, Семпл, Сустейн, ru
#May be answer: Still on My Mind, Thank You (песня Дайдо), Семпл, Сустейн