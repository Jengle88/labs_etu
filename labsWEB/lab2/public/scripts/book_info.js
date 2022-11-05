import {
    toIndexPage,
    editBook,
    removeBook,
    takeBook,
    getBookById,
    returnBook,
    actionWithCheckCurrUser
} from "./client.js";
import {Preprocessor} from "./Preprocessor.js";
import {Book} from "./Book.js";

const mainTitle = document.getElementById("main_title")
let id = document.location.pathname.slice(document.location.pathname.lastIndexOf("/") + 1, document.location.pathname.length)

const takeBookButton = document.getElementById("book_info_take_book_button")
const returnBookButton = document.getElementById("book_info_return_book_button")
const editInfoButton = document.getElementById("book_info_edit_info_button")
const deleteBookButton = document.getElementById("book_info_delete_book_button")

const bookTitleInput = document.getElementById("book_info_item_book_title_input")
const bookAuthorInput = document.getElementById("book_info_item_book_author_input")
const bookStatusSelect = document.getElementById("book_info_item_book_status_select")
const bookReleaseDateInput = document.getElementById("book_info_item_book_release_date_input")
const bookWasTakenByInput = document.getElementById("book_info_item_book_was_taken_by_input")
const bookReturnDateInput = document.getElementById("book_info_item_book_return_date_input")

const bookTitleText = document.getElementById("book_info_item_book_title")
const bookAuthorText = document.getElementById("book_info_item_book_author")
const bookStatusText = document.getElementById("book_info_item_book_status")
const bookReleaseDateText = document.getElementById("book_info_item_book_release_date")
const bookWasTakenByText = document.getElementById("book_info_item_book_was_taken_by")
const bookReturnDateText = document.getElementById("book_info_item_book_return_date")

let isEditingMode = false

const takeBookEnterInfoDialog = document.getElementById("take_book_enter_info_dialog")
const takeBookEnterInfoInputReturnDate = document.getElementById("take_book_enter_info_input_return_date")
const takeBookEnterInfoButtonAccept = document.getElementById("take_book_enter_info_button_accept")
const takeBookEnterInfoButtonCancel = document.getElementById("take_book_enter_info_button_cancel")

takeBookEnterInfoDialog.style.display = "none"

mainTitle.addEventListener("click", toIndexPage)

function updateBookInfo(book) {
    bookTitleText.innerText = book.title
    bookAuthorText.innerText = book.author
    bookStatusText.innerText = Preprocessor.statusToLocaleLang(book.status, book.return_date)
    bookWasTakenByText.innerText = book.was_taken_by
    bookReturnDateText.innerText = book.return_date
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

takeBookButton.addEventListener("click", () => {
    actionWithCheckCurrUser(() => {
        if (takeBookButton.disable)
            return
        prepareTakeBookDialog(async (returnDate) => {
            if (Number(id)) {
                await takeBook(Number(id), localStorage["current_user"], returnDate)
                let book = await getBookById(id)
                updateBookInfo(book)
            }
        })
    })
})

returnBookButton.addEventListener("click", () => {
    actionWithCheckCurrUser(async () => {
        if (returnBookButton.disable)
            return
        if (Number(id)) {
            await returnBook(Number(id))
            let book = await getBookById(id)
            updateBookInfo(book)
        }
    })
})

function enableButtons() {
    takeBookButton.disable = false
    returnBookButton.disable = false
    deleteBookButton.disable = false
}

function disableButtons() {
    takeBookButton.disable = true
    returnBookButton.disable = true
    deleteBookButton.disable = true
}

editInfoButton.addEventListener("click", () => {
    actionWithCheckCurrUser(() => {
        if (isEditingMode) {
            enableButtons()
            extractInfoFromInputsToText();
            changeInputsDisplay("none");
            changeTextDisplay("flex");
            let book = new Book(
                Number(id),
                bookTitleText.innerText,
                bookAuthorText.innerText,
                Preprocessor.statusFromLocaleLang(bookStatusText.innerText),
                bookReleaseDateText.innerText,
                bookWasTakenByText.innerText,
                bookReturnDateText.innerText
            )
            editBook(book);
        } else {
            disableButtons()
            extractInfoFromTextToInput();
            changeInputsDisplay("flex");
            changeTextDisplay("none");
        }
        isEditingMode = !isEditingMode
    })
})

deleteBookButton.addEventListener("click", () => {
    actionWithCheckCurrUser(() => {
        if (deleteBookButton.disable)
            return
        let confirmDelete = confirm("Вы уверены, что хотите удалить книгу?")
        if (confirmDelete) {
            removeBook(Number(id))
        }
    })
})


function extractInfoFromInputsToText() {
    bookTitleText.innerText = bookTitleInput.value
    bookAuthorText.innerText = bookAuthorInput.value
    bookStatusText.innerText = Preprocessor.statusToLocaleLang(bookStatusSelect.value, bookReturnDateInput.value)
    bookReleaseDateText.innerText = bookReleaseDateInput.value
    bookWasTakenByText.innerText = _nullIfEmpty(bookWasTakenByInput.value)
    bookReturnDateText.innerText = _nullIfEmpty(bookReturnDateInput.value)
}

function extractInfoFromTextToInput() {
    bookTitleInput.value = bookTitleText.innerText
    bookAuthorInput.value = bookAuthorText.innerText
    bookStatusSelect.options.selectedIndex = Array.prototype.slice.call(bookStatusSelect.options).findIndex((status) => {
        return Preprocessor.statusFromLocaleLang(bookStatusText.innerText) === status.value
    })
    bookReleaseDateInput.value = bookReleaseDateText.innerText
    bookWasTakenByInput.value = _nullIfEmpty(bookWasTakenByText.innerText)
    bookReturnDateInput.value = _nullIfEmpty(bookReturnDateText.innerText)
}

function changeInputsDisplay(displayParams) {
    bookTitleInput.style.display = displayParams
    bookAuthorInput.style.display = displayParams
    bookStatusSelect.style.display = displayParams
    bookReleaseDateInput.style.display = displayParams
    bookWasTakenByInput.style.display = displayParams
    bookReturnDateInput.style.display = displayParams
}

function changeTextDisplay(displayParams) {
    bookTitleText.style.display = displayParams
    bookAuthorText.style.display = displayParams
    bookStatusText.style.display = displayParams
    bookReleaseDateText.style.display = displayParams
    bookWasTakenByText.style.display = displayParams
    bookReturnDateText.style.display = displayParams
}

function _nullIfEmpty(text) {
    if (text.length === 0)
        return null
    else
        return text
}
