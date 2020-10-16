import wikipedia


# существует ли такая страница
def is_page_valid(page):
    try:
        wikipedia.page(page)
    except Exception:
        return False
    return True


# проверка существования языка
def is_right_lang(lang):
    return lang in wikipedia.languages()


# количество слов в строке
def cnt_word(string):
    return len(string.replace('\n', ' ').replace('\t', ' ').split(' '))


# максимальное количество слов в строке
def max_cnt_words_summary(page_array):
    maxCnt = 0
    ansPage = ""
    for page in page_array:
        cntInStr = cnt_word(wikipedia.page(page).summary)
        if cntInStr >= maxCnt:
            maxCnt = cntInStr
            ansPage = page
    return [maxCnt, wikipedia.page(ansPage).title]


# поиск промежуточного звена
def find_support_chain(page_array, i):
    linksArray = wikipedia.page(page_array[i]).links
    for item in linksArray:
        if not is_page_valid(item):
            continue
        if page_array[i + 1] in wikipedia.page(item).links:
            return item


# поиск цепочки
def find_chain(page_array):
    answerArray = [page_array[0]]
    for i in range(0, len(page_array) - 1):
        if page_array[i + 1] not in wikipedia.page(page_array[i]).links:
            answerArray.append(find_support_chain(page_array, i))
        answerArray.append(page_array[i + 1])
    return answerArray


# точка начала программы
array = input().split(', ')
if is_right_lang(array[-1]):
    wikipedia.set_lang(array.pop())
else:
    print("no results")
    quit(0)
print(*max_cnt_words_summary(array))
print(find_chain(array))
