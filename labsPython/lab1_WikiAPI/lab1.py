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


# количество слов в строке
def cnt_word(string):
    a = list(string.replace('\n', ' ').replace('\t', ' ').split())
    return len(a)


# максимальное количество слов в кратком содержании страницы
def max_cnt_word_in_summary(array_page):
    maxCount = -1
    answerPage = None
    for page in array_page:
        cntIterPage = cnt_word(wikipedia.page(page).summary)
        if maxCount <= cntIterPage:
            answerPage = page
            maxCount = cntIterPage
    return [maxCount, answerPage]


# точка входа в программу
array = input().split(', ')
if is_right_lang(array[-1]):
    wikipedia.set_lang(array[-1])
else:
    print("no results")
    exit(0)
print(*max_cnt_word_in_summary(array))

#print(cnt_word(wikipedia.page(array[1]).summary))
