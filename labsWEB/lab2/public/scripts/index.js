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

const authorizationDialog = document.getElementById("authorization_dialog")
const authorizationDialogUserLogin = document.getElementById("authorization_dialog_user_login")
const authorizationDialogAccept = document.getElementById("authorization_dialog_accept")

const authorizationPanelCurrentUser = document.getElementById("authorization_panel_current_user")
const authorizationPanelUnauthorization = document.getElementById("authorization_panel_unauthorization")

const takeBookEnterInfoDialog = document.getElementById("take_book_enter_info_dialog")
const takeBookEnterInfoInputReturnDate = document.getElementById("take_book_enter_info_input_return_date")
const takeBookEnterInfoButtonAccept = document.getElementById("take_book_enter_info_button_accept")
const takeBookEnterInfoButtonCancel = document.getElementById("take_book_enter_info_button_cancel")

authorizationDialog.style.display = "none"
takeBookEnterInfoDialog.style.display = "none"

checkPrevAuthorization()

function prepareAuthorizationForm() {
    authorizationDialog.style.display = "flex"
    authorizationDialogUserLogin.value = localStorage["current_user"]
    localStorage["current_user"] = ""
    authorizationPanelCurrentUser.innerText = ""
}

// Проверка наличия логина пользователя
function checkPrevAuthorization() {
    actionWithCheckCurrUser(() => {
        authorizationDialog.style.display = "none"
        authorizationDialogUserLogin.value = localStorage["current_user"]
        authorizationPanelCurrentUser.innerText = localStorage["current_user"]
    }, () => {
        prepareAuthorizationForm()
    })
}

// (Для авторизации) Сохранить введённый логин
authorizationDialogAccept.addEventListener("click", () => {
    localStorage["current_user"] = authorizationDialogUserLogin.value
    checkPrevAuthorization()
})

// (Для авторизации) Выйти из текущего профиля
authorizationPanelUnauthorization.addEventListener("click", () => {
    prepareAuthorizationForm()
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

function prepareTakeBookDialog(acceptWithoutHideDialog, cancelWithoutHideDialog = () => {}) {
    takeBookEnterInfoDialog.style.display = "flex"

    takeBookEnterInfoButtonAccept.addEventListener("click", () => {
        acceptWithoutHideDialog(takeBookEnterInfoInputReturnDate.value)
        takeBookEnterInfoDialog.style.display = "none"
    })
    takeBookEnterInfoButtonCancel.addEventListener("click", () => {
        cancelWithoutHideDialog()
        takeBookEnterInfoDialog.style.display = "none"
    })
}

// Установка слушателей на кнопки карточки с книгой (обновляют карточку при нажатии)
listOfBooks.forEach(htmlBookCard => {
    const id = htmlBookCard.id.split("book_in_list_of_books#")[1]
    document.getElementById(`book_action_take#${id}`)
        .addEventListener("click", () => {
            actionWithCheckCurrUser(() => {
                prepareTakeBookDialog(async (returnDate) => {
                    if (Number(id)) {
                        await takeBook(Number(id), localStorage["current_user"], returnDate)
                        let book = await getBookById(id)
                        updateBookCard(book, htmlBookCard)
                    }
                })
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

