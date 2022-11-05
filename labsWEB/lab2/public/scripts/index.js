import {
    actionWithCheckCurrUser,
    getBookById,
    returnBook,
    takeBook,
    toAddNewBookPage,
    toBookInfoPage,
    toIndexPage,
} from "./client.js";
import {Preprocessor} from "./Preprocessor.js";

// set id
const buttonAddNewBook = document.getElementById("start_add_new_book")
const mainTitle = document.getElementById("main_title")
const listOfBooksElem = document.getElementsByClassName("book-in-list-of-books")
const listOfBooks = Array.prototype.slice.call(listOfBooksElem)

const loggingDialog = document.getElementById("logging_dialog")
const loggingDialogUserLogin = document.getElementById("logging_dialog_user_login")
const loggingDialogAccept = document.getElementById("logging_dialog_accept")

const loggingPanelCurrentUser = document.getElementById("logging_panel_current_user")
const loggingPanelUnlogging = document.getElementById("logging_panel_unlogging")

checkPrevLogging()

function prepareLoggingForm() {
    loggingDialog.style.display = "flex"
    loggingDialogUserLogin.value = localStorage["current_user"]
    localStorage["current_user"] = ""
    loggingPanelCurrentUser.innerText = ""
}

// Проверка наличия логина пользователя
function checkPrevLogging() {
    actionWithCheckCurrUser(() => {
        loggingDialog.style.display = "none"
        loggingDialogUserLogin.value = localStorage["current_user"]
        loggingPanelCurrentUser.innerText = localStorage["current_user"]
    }, () => {
        prepareLoggingForm()
    })
}

// (Для авторизации) Сохранить введённый логин
loggingDialogAccept.addEventListener("click", () => {
    localStorage["current_user"] = loggingDialogUserLogin.value
    checkPrevLogging()
})

// (Для авторизации) Выйти из текущего профиля
loggingPanelUnlogging.addEventListener("click", () => {
    prepareLoggingForm()
})

document.getElementById("logging_dialog_cancel")
    .addEventListener("click", () => {
        loggingDialog.style.display = "none"
    })

// Переход на экран добавления книги
buttonAddNewBook.addEventListener("click", () => {
    actionWithCheckCurrUser(() => {
        toAddNewBookPage()
    })

})

// Переход на главную страницу
mainTitle.addEventListener("click", toIndexPage)

// Обновить карточку с книгой
function updateBookCard(book, htmlBookCard) {
    htmlBookCard.getElementsByClassName("book-title")[0]
        .innerText = book.title
    htmlBookCard.getElementsByClassName("book-author")[0]
        .innerText = book.author
    htmlBookCard.getElementsByClassName("book-status")[0]
        .innerText = Preprocessor.statusToLocaleLang(book.status)
}

// Установка слушателей на кнопки карточки с книгой (обновляют карточку при нажатии)
listOfBooks.forEach(htmlBookCard => {
    const id = htmlBookCard.id.split("book_in_list_of_books#")[1]
    document.getElementById(`book_action_take#${id}`)
        .addEventListener("click", () => {
            actionWithCheckCurrUser(async () => {
                if (Number(id)) {
                    // FIXME заменить на подстановку пользователя
                    await takeBook(Number(id), "Human1", "2022-12-3")
                    let book = await getBookById(id)
                    updateBookCard(book, htmlBookCard)
                }
            })
        })
    document.getElementById(`book_action_return#${id}`)
        .addEventListener("click", () => {
            actionWithCheckCurrUser(async () => {
                if (Number(id)) {
                    await returnBook(Number(id))
                    let book = await getBookById(id)
                    updateBookCard(book, htmlBookCard)
                }
            })
        })
    document.getElementById(`book_title#${id}`)
        .addEventListener("click", () => {
            actionWithCheckCurrUser(() => {
                toBookInfoPage(id)
            })
        })
})

