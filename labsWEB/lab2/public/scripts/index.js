import {
    actionWithCheckCurrUser,
    getBookById,
    getBooksWithFilter,
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
let listOfBooksElem = document.getElementsByClassName("book-in-list-of-books")
let listOfBooks = Array.prototype.slice.call(listOfBooksElem)

const authorizationDialog = document.getElementById("authorization_dialog")
const authorizationDialogUserLogin = document.getElementById("authorization_dialog_user_login")
const authorizationDialogAccept = document.getElementById("authorization_dialog_accept")

const authorizationPanelCurrentUser = document.getElementById("authorization_panel_current_user")
const authorizationPanelUnauthorization = document.getElementById("authorization_panel_unauthorization")

const takeBookEnterInfoDialog = document.getElementById("take_book_enter_info_dialog")
const takeBookEnterInfoInputReturnDate = document.getElementById("take_book_enter_info_input_return_date")
const takeBookEnterInfoButtonAccept = document.getElementById("take_book_enter_info_button_accept")
const takeBookEnterInfoButtonCancel = document.getElementById("take_book_enter_info_button_cancel")

const filterInputTitle = document.getElementById("filter_input_title")
const filterInputAuthor = document.getElementById("filter_input_author")
const filterInputReturnDate = document.getElementById("filter_input_return_date")
const filterInputBookStatusInStock = document.getElementById("filter_input_book_status_in_stock")
const filterInputBookStatusUnavailable = document.getElementById("filter_input_book_status_unavailable")
const filterInputBookStatusOverdue = document.getElementById("filter_input_book_status_overdue")
const filterButtonCleanFilters = document.getElementById("filter_button_clean_filters")
const filterButtonAccept = document.getElementById("filter_button_accept")

authorizationDialog.style.display = "none"
takeBookEnterInfoDialog.style.display = "none"

checkPrevAuthorization()
// Установка слушателей на кнопки карточки с книгой (обновляют карточку при нажатии)
setListenerForBookCards();

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

filterButtonCleanFilters.addEventListener("click", () => {
    filterInputTitle.value = ""
    filterInputAuthor.value = ""
    filterInputReturnDate.value = ""
    filterInputBookStatusInStock.checked = false
    filterInputBookStatusUnavailable.checked = false
    filterInputBookStatusOverdue.checked = false
    resetBookList()
})

filterButtonAccept.addEventListener("click", () => {
    updateBookListWithFilters(
        filterInputTitle.value,
        filterInputAuthor.value,
        filterInputReturnDate.value,
        filterInputBookStatusInStock.checked ? true : null,
        filterInputBookStatusUnavailable.checked ? true : null,
        filterInputBookStatusOverdue.checked ? true : null
    )
})

function setListenerForBookCards() {
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
}

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

function createNewBookItem(book) {
    let rootElementOfBookItem = document.createElement("div")
    rootElementOfBookItem.className = "book-in-list-of-books"
    rootElementOfBookItem.id = `book_in_list_of_books#${book.id}`

    let titleAndAuthorPart = document.createElement("div")
    titleAndAuthorPart.className = "book-title-and-author"

    let bookTitle = document.createElement("p")
    bookTitle.id = `book_title#${book.id}`
    bookTitle.className = "book-title"
    bookTitle.innerText = book.title
    let bookAuthor = document.createElement("p")
    bookAuthor.id = "book_author"
    bookAuthor.className = "book-author"
    bookAuthor.innerText = book.author
    titleAndAuthorPart.appendChild(bookTitle)
    titleAndAuthorPart.appendChild(bookAuthor)

    let statusAndActionsPart = document.createElement("div")
    statusAndActionsPart.className = "book-status-and-actions"

    let bookStatus = document.createElement("p")
    bookStatus.className = "book-status"
    bookStatus.innerText = Preprocessor.statusToLocaleLang(book.status, book.return_date)
    let bookActions = document.createElement("div")
    bookActions.className = "book-actions"
    let bookActionTake = document.createElement("img")
    bookActionTake.id = `book_action_take#${book.id}`
    bookActionTake.className = "book-action-icon"
    bookActionTake.src = "../drawable/ic_take_book.png"
    let bookActionReturn = document.createElement("img")
    bookActionReturn.id = `book_action_return#${book.id}`
    bookActionReturn.className = "book-action-icon"
    bookActionReturn.src = "../drawable/ic_return_book.png"
    bookActions.appendChild(bookActionTake)
    bookActions.appendChild(bookActionReturn)
    statusAndActionsPart.appendChild(bookStatus)
    statusAndActionsPart.appendChild(bookActions)

    rootElementOfBookItem.appendChild(titleAndAuthorPart)
    rootElementOfBookItem.appendChild(statusAndActionsPart)

    return rootElementOfBookItem

}

function updateAllBooks(books) {
    while(listOfBooksElem.length > 0) {
        listOfBooksElem[0].remove()
    }
    let newListOfBooks = document.getElementById("list_of_books")
    for (let i = 0; i < books.length; i++) {
        let newBookItem = createNewBookItem(books[i])
        newListOfBooks.appendChild(newBookItem)
    }
    listOfBooksElem = document.getElementsByClassName("book-in-list-of-books")
    listOfBooks = Array.prototype.slice.call(listOfBooksElem)
    setListenerForBookCards()
}

function resetBookList() {
    getBooksWithFilter().then((value) => {
        updateAllBooks(value)
    })
}

function updateBookListWithFilters(
    title = null,
    author = null,
    returnDate = null,
    isInStock = null,
    isUnavailable = null,
    isOverdue = null
) {
    getBooksWithFilter(title, author, returnDate, isInStock, isUnavailable, isOverdue)
        .then((value) => {
            updateAllBooks(value)
        })
}
