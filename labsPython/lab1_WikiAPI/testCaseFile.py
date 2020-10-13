import wikipedia
import random


# безопасное обращение к странице
def safe_page(page):
    try:
        pageAnswer = wikipedia.page(page)
    except wikipedia.DisambiguationError as e:
        pageAnswer = wikipedia.page(e.options[0])
    return pageAnswer.title


# существует ли такая страница
def is_page_valid(page):
    try:
        wikipedia.page(page)
    except Exception:
        return False
    return True


def find_good_links(arrayLinks, randLink):
    cnt = 0
    while not is_page_valid(arrayLinks[randLink]):
        randLink = random.randint(0, len(arrayLinks) - 1)
        if cnt == 1000:
            print("error")
            quit(-1)
        cnt += 1
    return randLink


size = random.randint(1, 7)
testCase = []
wikipedia.set_lang('ru')
maybeAnswer = []
page = wikipedia.random(1)
testCase.append(safe_page(page))
maybeAnswer.append(testCase[0])

for i in range(size):
    print(i, ") ready")
    choice = random.randint(0, 1)
    if choice % 2 == 0:
        arrayLinks = wikipedia.page(testCase[-1]).links
        randLink = random.randint(0, len(arrayLinks) - 1)
        randLink = find_good_links(arrayLinks, randLink)
        testCase.append(safe_page(arrayLinks[randLink]))
        maybeAnswer.append(testCase[-1])

    else:
        arraySuppLinks = wikipedia.page(testCase[-1]).links
        randLink = random.randint(0, len(arraySuppLinks) - 1)
        randLink = find_good_links(arraySuppLinks, randLink)
        maybeAnswer.append(safe_page(arraySuppLinks[randLink]))

        arrayLinks = wikipedia.page(safe_page(arraySuppLinks[randLink])).links
        randLink = random.randint(0, len(arrayLinks) - 1)
        randLink = find_good_links(arrayLinks, randLink)
        testCase.append(safe_page(arrayLinks[randLink]))
        maybeAnswer.append(testCase[-1])

testCase.append('ru')
print(*testCase, sep=', ')
print("Maybe answer: ", end='')
print(*maybeAnswer, sep=', ')
